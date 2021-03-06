#include "Table.h"
#include "ResourceManager.h"

#include <iostream>
#include <vector>

Table::Table(unsigned int width, unsigned int height, float squareSize, unsigned int windowWidth, unsigned int windowHeight)
	: Width(width), Height(height), SquareSize(squareSize), SquareY(-1), SquareX(-1), NrRows(-1), NrColumns(-1), 
	  White(1.0f, 1.0f, 1.0f), Blue(0.0f, 0.0f, 1.0f), Yellow(1.0f, 1.0f, 0.0f), Red(1.0f, 0.0f, 0.0f), Purple(0.5f, 0.1f, 0.8f),
	  StartPointX(0), StartPointY(0), LastStartPointX(0), LastStartPointY(0), MoveStartPoint(false),
	  FinishPointX(0), FinishPointY(1), LastFinishPointX(0), LastFinishPointY(1), MoveFinishPoint(false),
	  WindowWidth(windowWidth), WindowHeight(windowHeight),
	  LeftMousePressed(false), RightMousePressed(false), BlockLastFrame(false),
	  TriangleAmount(100), AnimationCooldown(0.2f), LastAnimation(AnimationCooldown)
{
	State = TableState::TABLE_DRAW;

	// nrRows and nrColumns
	for (float y = 0.0f; y <= (float)Height; y += SquareSize)
		NrRows++;

	for (float x = 0.0f; x <= (float)Width; x += SquareSize)
		NrColumns++;

	// initialize algorithm solver
	Solver = new AlgorithmSolver(NrRows, NrColumns, { StartPointX, StartPointY }, { FinishPointX, FinishPointY });

	// initialize animation manager
	Animation = new AnimationManager(SquareSize);

	// initialize FBO
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	Texture.Generate(width, height, NULL);
	Texture.Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture.ID, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::TABLE:: Failed to initialize FBO" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	InitRenderData();
}

Table::~Table()
{
	delete Solver;
	delete Animation;
}

void Table::InitRenderData()
{
	// initialize row and column VAO
	float LineVertices[] = {
		0.0f, 0.0f,			// row left
		1.0f, 0.0f,			// row right
	};

	GLuint LineVBO;
	glGenVertexArrays(1, &RowVAO);
	glGenBuffers(1, &LineVBO);

	glBindBuffer(GL_ARRAY_BUFFER, LineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertices), LineVertices, GL_STATIC_DRAW);

	glBindVertexArray(RowVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	// initialize quad texture VAO
	float QuadVertices[] = {
		// pos		 // tex
		0.0f, 0.0f,  0.0f, 1.0f,
		1.0f, 1.0f,  1.0f, 0.0f,
		0.0f, 1.0f,  0.0f, 0.0f,

		0.0f, 0.0f,  0.0f, 1.0f,
		1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, 1.0f,  1.0f, 0.0f
	};

	GLuint QuadVBO;
	glGenVertexArrays(1, &QuadVAO);
	glGenBuffers(1, &QuadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);

	glBindVertexArray(QuadVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	// initialize start point VAO
	float StartPointVertices[] = {
		0.0f, 0.0f,
		1.0f, 0.5f,

		1.0f, 0.5f,
		0.0f, 1.0f
	};

	GLuint StartPointVBO;
	glGenVertexArrays(1, &StartVAO);
	glGenBuffers(1, &StartPointVBO);

	glBindBuffer(GL_ARRAY_BUFFER, StartPointVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(StartPointVertices), StartPointVertices, GL_STATIC_DRAW);

	glBindVertexArray(StartVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// initialize circle VAO
	float x, y, radius;
	y = x = radius = 1.0f;

	const float PI = 3.14159265358979323846f;
	float twicePi = 2.0f * PI;

	std::vector<float> CircleVertices;
	CircleVertices.push_back(x);
	CircleVertices.push_back(y);

	for (int i = 0; i <= TriangleAmount; i++)
	{
		CircleVertices.push_back(x + (radius * cos(i * twicePi / TriangleAmount)));
		CircleVertices.push_back(y + (radius * sin(i * twicePi / TriangleAmount)));
	}

	GLuint CircleVBO;
	glGenVertexArrays(1, &CircleVAO);
	glGenBuffers(1, &CircleVBO);

	glBindBuffer(GL_ARRAY_BUFFER, CircleVBO);
	glBufferData(GL_ARRAY_BUFFER, CircleVertices.size() * sizeof(float), &CircleVertices[0], GL_STATIC_DRAW);

	glBindVertexArray(CircleVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 
}

void Table::DrawSprite(float deltaTime)
{
	glViewport(0, 0, Width, Height);
	Draw(deltaTime);
	glViewport(0, 0, WindowWidth, WindowHeight);

	ResourceManager::GetShader("sprite").Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3((float)Width, (float)Height, 1.0f));

	ResourceManager::GetShader("sprite").SetMatrix4f("model", model);

	glActiveTexture(GL_TEXTURE0);
	Texture.Bind();

	glBindVertexArray(QuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Table::Update(float deltaTime)
{
	LastAnimation = std::min(AnimationCooldown, LastAnimation + deltaTime);
	if (LastAnimation >= AnimationCooldown)
	{
		LastAnimation = 0.0f;
		if (!Solver->Path.empty())
		{
			Animation->AddSquare(Solver->Path.back());
			Solver->Path.pop_back();
		}
		else if (!Solver->Route.empty())
		{
			Animation->AddSquareFinalRoute(Solver->Route.back());
			Solver->Route.pop_back();
		}
	}
}

void Table::Draw(float deltaTime)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetVector3f("color", White);
	glLineWidth(2.0f);

	glm::mat4 model = glm::mat4(1.0f);

	// draw rows
	for (float y = 0.0f; y <= (float)Height; y += SquareSize)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, y, 0.0f));
		model = glm::scale(model, glm::vec3((float)Width, 0.0f, 1.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(RowVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	// draw columns
	for (float x = 0.0f; x <= (float)Width; x += SquareSize)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3((float)Height, 0.0f, 1.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(RowVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	Animation->Draw(deltaTime);

	if (IsMouseInTable())
		DrawOutline();

	glBindVertexArray(0);
	glLineWidth(1.0f);

	DrawStart();

	DrawFinish();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Table::ProcessInput(double xpos, double ypos)
{
	// transform mouse position to texture coordinates
	xpos -= position.x;
	ypos -= position.y;

	SquareX = ypos / SquareSize;
	SquareY = xpos / SquareSize;

	// outside of table
	if (xpos < 0 || ypos < 0 || SquareX >= NrRows || SquareY >= NrColumns)
	{
		SquareX = -1;
		SquareY = -1;
	}

	if (State == TableState::TABLE_DRAW)
	{
		if (MoveStartPoint)	// move starting point
		{
			StartPointX = SquareX;
			StartPointY = SquareY;
		}
		else if (MoveFinishPoint)	// move finishing point
		{
			FinishPointX = SquareX;
			FinishPointY = SquareY;
		}

		// check mouse right button
		if (RightMousePressed && IsMouseInTable() && Solver->IsBlock({ SquareX, SquareY }))
		{
			Solver->DeleteBlock({ SquareX, SquareY });
			Animation->DeleteBlock({ SquareX, SquareY });
		}
		else if (LeftMousePressed) // check mouse left button
		{
			// if the selected block is not the starting/finishing point or already a block, make one
			if (StartPointX == SquareX && StartPointY == SquareY && !MoveFinishPoint)	// check if starting point is selected
			{
				if (BlockLastFrame)
				{
					LeftMousePressed = false;
					BlockLastFrame = false;
				}
				else
				{
					MoveStartPoint = true;
				}
			}
			else if (FinishPointX == SquareX && FinishPointY == SquareY && !MoveStartPoint)	// check if finishing point is selected
			{
				if (BlockLastFrame)
				{
					LeftMousePressed = false;
					BlockLastFrame = false;
				}
				else
				{
					MoveFinishPoint = true;
				}
			}
			else if (IsMouseInTable() && !Solver->IsBlock({ SquareX, SquareY }))
			{
				Solver->AddBlock({ SquareX, SquareY });
				Animation->AddBlock({ SquareX, SquareY });
				BlockLastFrame = true;
			}
		}
		else // not pressing
		{
			if (MoveStartPoint)
			{
				// if it is inside in table and it is not overlapping with starting point or a block
				if (IsMouseInTable() && (SquareX != FinishPointX || SquareY != FinishPointY) && !Solver->IsBlock({ SquareX, SquareY }))
				{
					LastStartPointX = StartPointX = SquareX;
					LastStartPointY = StartPointY = SquareY;
				}
				else
				{
					StartPointX = LastStartPointX;
					StartPointY = LastStartPointY;
				}
			}
			if (MoveFinishPoint)
			{
				// if it is inside in table and it is not overlapping with starting point or a block
				if (IsMouseInTable() && (SquareX != StartPointX || SquareY != StartPointY) && !Solver->IsBlock({ SquareX, SquareY }))
				{
					LastFinishPointX = FinishPointX = SquareX;
					LastFinishPointY = FinishPointY = SquareY;
				}
				else
				{
					FinishPointX = LastFinishPointX;
					FinishPointY = LastFinishPointY;
				}
			}

			BlockLastFrame = false;
			MoveStartPoint = false;
			MoveFinishPoint = false;
		}
	}
}

void Table::DrawOutline()
{
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetVector3f("color", Blue);

	glm::mat4 model = glm::mat4(1.0f);

	float StartX = (float)SquareY * SquareSize;
	float StartY = (float)SquareX * SquareSize;

	// draw rows
	for (float y = StartY; y <= StartY + SquareSize; y += SquareSize)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(StartX, y, 0.0f));
		model = glm::scale(model, glm::vec3((float)SquareSize, 0.0f, 1.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(RowVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	// draw columns
	for (float x = StartX; x <= StartX + SquareSize; x += SquareSize)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, StartY, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3((float)SquareSize, 0.0f, 1.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(RowVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

void Table::DrawStart()
{
	glLineWidth(5.0f);

	float StartX = (float)StartPointY * SquareSize + 2.0f;
	float StartY = (float)StartPointX * SquareSize + 2.0f;

	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetVector3f("color", Yellow);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(StartX, StartY, 0.0f));
	model = glm::scale(model, glm::vec3(25.0f, 25.0f, 0.0f));
	ResourceManager::GetShader("line").SetMatrix4f("model", model);

	glBindVertexArray(StartVAO);
	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);

	glLineWidth(1.0f);
}

void Table::DrawFinish()
{
	float StartX = (float)FinishPointY * SquareSize;
	float StartY = (float)FinishPointX * SquareSize;
	glm::vec2 scale = glm::vec2(15.0f, 15.0f);
	float offset = 4.0f;
	for (int i = 0; i < 3; i++)
	{
		StartX += offset;
		StartY += offset;
		scale.x -= offset;
		scale.y -= offset;
		DrawCircle(StartX, StartY, scale, i == 1 ? White : Purple);
	}
}

void Table::DrawCircle(float StartX, float StartY, glm::vec2 scale, glm::vec3 color)
{
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetVector3f("color", color);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(StartX, StartY, 0.0f));
	model = glm::scale(model, glm::vec3(scale, 0.0f));
	ResourceManager::GetShader("line").SetMatrix4f("model", model);

	glBindVertexArray(CircleVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, TriangleAmount + 2);
	glBindVertexArray(0);
}

void Table::StartAlgorithm()
{
	if (State == TableState::TABLE_DRAW)
	{
		State = TableState::TABLE_VISUALIZE;
		Solver->SetStartingPosition({ StartPointX, StartPointY });
		Solver->SetFinishingPosition({ FinishPointX, FinishPointY });
		Solver->FindPath();
	}
}

void Table::ClearBoard(bool solution)
{
	State = TableState::TABLE_DRAW;
	Animation->Reset(solution);
	Solver->Reset(solution);
}

bool Table::IsMouseInTable()
{
	return SquareX != -1;
}

void Table::SetSpritePosition(glm::vec2 pos)
{
	position = pos;
}

void Table::SetLeftMouse(bool press)
{
	LeftMousePressed = press;
}

void Table::SetRightMouse(bool press)
{
	RightMousePressed = press;
}

