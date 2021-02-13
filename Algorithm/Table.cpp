#include "Table.h"
#include "ResourceManager.h"

#include <iostream>

Table::Table(unsigned int width, unsigned int height, float squareSize, unsigned int windowWidth, unsigned int windowHeight)
	: Width(width), Height(height), SquareSize(squareSize), SquareY(-1), SquareX(-1), NrRows(-1), NrColumns(-1), 
	  White(1.0f, 1.0f, 1.0f), Blue(0.0f, 0.0f, 1.0f), Yellow(1.0f, 1.0f, 0.0f),
	  StartPointX(0), StartPointY(0),
	  WindowWidth(windowWidth), WindowHeight(windowHeight),
	  LeftMousePressed(false), MoveStartPoint(false)
{
	for (float y = 0.0f; y <= (float)Height; y += SquareSize)
		NrRows++;

	for (float x = 0.0f; x <= (float)Width; x += SquareSize)
		NrColumns++;

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

void Table::InitRenderData()
{
	// initialize row and column VAO
	float LineVertices[] = {
		0.0f, 0.0f,			// row left
		1.0f, 0.0f,			// row right

		0.0f, 0.0f,			// column top
		0.0f, 1.0f			// column down
	};

	GLuint LineVBO;
	glGenVertexArrays(1, &RowVAO);
	glGenVertexArrays(1, &ColumnVAO);
	glGenBuffers(1, &LineVBO);

	glBindBuffer(GL_ARRAY_BUFFER, LineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertices), LineVertices, GL_STATIC_DRAW);

	glBindVertexArray(RowVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(ColumnVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(4 * sizeof(float)));

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Table::DrawSprite()
{
	glViewport(0, 0, Width, Height);
	Draw();
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

void Table::Draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		// todo : change background color
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
		model = glm::scale(model, glm::vec3(0.0f, (float)Height, 1.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		// todo : use the same VAO and rotate the model

		glBindVertexArray(ColumnVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	if (SquareX != -1 && SquareY != -1)
		DrawOutline();

	glBindVertexArray(0);
	glLineWidth(1.0f);

	DrawStart();

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
	 
	// todo
	std::cout << "Square : " << SquareX << ' ' << SquareY << '\n';
	std::cout << "StartPoint : " << StartPointX << ' ' << StartPointY << '\n';

	if (MoveStartPoint)
	{
		if (SquareX != -1)	// if it is inside in table
		{
			StartPointX = SquareX;
			StartPointY = SquareY;
		}
		else
		{
			MoveStartPoint = false;
		}
	}

	if (StartPointX == SquareX && StartPointY == SquareY && LeftMousePressed) 
	{
		MoveStartPoint = true;
	}
	else // not holding anymore
	{
		MoveStartPoint = false;
	}
}

void Table::DrawOutline()
{
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
		model = glm::scale(model, glm::vec3(0.0f, (float)SquareSize, 1.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		// todo : use the same VAO and rotate the model

		glBindVertexArray(ColumnVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

void Table::DrawStart()
{
	glLineWidth(5.0f);

	float StartX = (float)StartPointY * SquareSize + 2.0f;
	float StartY = (float)StartPointX * SquareSize + 2.0f;

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

}

void Table::SetSpritePosition(glm::vec2 pos)
{
	position = pos;
}

void Table::SetLeftMouse(bool press)
{
	LeftMousePressed = press;

	if (LeftMousePressed)
		std::cout << "LEFT CLICK\n";
	else
		std::cout << "LEFT RELEASED\n";
}

