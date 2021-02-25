#include "Button.h"
#include "ResourceManager.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///												BUTTON
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Button::Button(glm::vec2 position, glm::vec2 size, glm::vec3 color, ButtonType type)
	: Position(position), Size(size), Type(type),
	  MainColor(color), SecondColor(color),
	  MouseInButtonRange(false), LeftMousePressed(false)
{
	Visible = true;
	if (type == ButtonType::BFS)
		Visible = false;
	else if (type == ButtonType::DFS)
		Visible = false;

	switch (type)
	{
	case ButtonType::Solve: Text = "Solve"; break;
	case ButtonType::Algorithm: Text = "Select Algorithm"; break;
	case ButtonType::BFS: Text = "BFS"; break;
	case ButtonType::DFS: Text = "DFS"; break;
	case ButtonType::ClearBoard: Text = "Clear Board"; break;
	case ButtonType::ClearSol: Text = "Clear Solution"; break;
	}

	InitRenderData();
}

void Button::ProcessInput(double xpos, double ypos)
{
	if (xpos >= Position.x && xpos <= Position.x + Size.x && ypos >= Position.y && ypos <= Position.y + Size.y)
	{
		MouseInButtonRange = true;
		MainColor = glm::vec3(SecondColor.x - 0.2f, SecondColor.y, SecondColor.z);
	}
	else
	{
		MouseInButtonRange = false;
		MainColor = SecondColor;
	}
}

bool Button::IsClicked()
{
	if (Visible && MouseInButtonRange && LeftMousePressed)
	{
		LeftMousePressed = false;
		return true;
	}
	return false;
}

void Button::ToggleVisibility()
{
	Visible = !Visible;
}

void Button::Render(TextRenderer* TextRender)
{
	if (Visible)
	{
		ResourceManager::GetShader("line").Use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(Position, 1.0f));
		model = glm::scale(model, glm::vec3(Size, 1.0f));

		ResourceManager::GetShader("line").SetMatrix4f("model", model);
		ResourceManager::GetShader("line").SetVector3f("color", MainColor);

		glBindVertexArray(SquareVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		TextRender->RenderText(Text, Position.x, Position.y, 1.0f);
	}
}

void Button::SetLeftMouse(bool press)
{
	if (press && MouseInButtonRange)
		LeftMousePressed = true;
	else
		LeftMousePressed = false;
}

void Button::InitRenderData()
{
	GLuint SquareVBO;
	glGenVertexArrays(1, &SquareVAO);
	glGenBuffers(1, &SquareVBO);

	float vertices[] = {
		// pos
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, SquareVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(SquareVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///												MANAGER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonsManager::ButtonsManager(unsigned int width, unsigned int height)
{
	TextRender = new TextRenderer(width, height);
	TextRender->Load("fonts/OCRAEXT.TTF", 24);

	// configure buttons
	SolveButton = new Button(glm::vec2(width / 2 - 75.0f, 10.0f), glm::vec2(150.0f, 50.0f), glm::vec3(1.0f, 0.5f, 0.5f), ButtonType::Solve);
	AlgorithmButton = new Button(glm::vec2(50.0f, 10.0f), glm::vec2(150.0f, 50.0f), glm::vec3(1.0f, 0.5f, 0.5f), ButtonType::Algorithm);
	BFSButton = new Button(glm::vec2(205.0f, 10.0f), glm::vec2(150.0f, 50.0f), glm::vec3(1.0f, 0.5f, 0.5f), ButtonType::BFS);
	DFSButton = new Button(glm::vec2(205.0f, 65.0f), glm::vec2(150.0f, 50.0f), glm::vec3(1.0f, 0.5f, 0.5f), ButtonType::DFS);
	ClearBoardButton = new Button(glm::vec2(width - 520.0f, 10.0f), glm::vec2(150.0f, 50.0f), glm::vec3(1.0f, 0.5f, 0.5f), ButtonType::ClearBoard);
	ClearSolButton = new Button(glm::vec2(width - 360.0f, 10.0f), glm::vec2(150.0f, 50.0f), glm::vec3(1.0f, 0.5f, 0.5f), ButtonType::ClearSol);
}

void ButtonsManager::Update(Table* table)
{
	if (SolveButton->IsClicked())
	{
		table->StartAlgorithm();
	}
	else if (AlgorithmButton->IsClicked())
	{
		BFSButton->ToggleVisibility();
		DFSButton->ToggleVisibility();
	}
	else if (BFSButton->IsClicked())
	{
		table->Solver->SetAlgorithm(Algorithm::BFS);
		BFSButton->ToggleVisibility();
		DFSButton->ToggleVisibility();
	}
	else if (DFSButton->IsClicked())
	{
		table->Solver->SetAlgorithm(Algorithm::DFS);
		DFSButton->ToggleVisibility();
		BFSButton->ToggleVisibility();
	}
	else if (ClearBoardButton->IsClicked())
	{
		table->ClearBoard(false);
	}
	else if (ClearSolButton->IsClicked())
	{
		table->ClearBoard(true);
	}
}

void ButtonsManager::Render()
{
	SolveButton->Render(TextRender);

	AlgorithmButton->Render(TextRender);
	BFSButton->Render(TextRender);
	DFSButton->Render(TextRender);

	ClearBoardButton->Render(TextRender);
	ClearSolButton->Render(TextRender);
}

void ButtonsManager::ProcessInput(double xpos, double ypos)
{
	SolveButton->ProcessInput(xpos, ypos);

	AlgorithmButton->ProcessInput(xpos, ypos);
	BFSButton->ProcessInput(xpos, ypos);
	DFSButton->ProcessInput(xpos, ypos);

	ClearBoardButton->ProcessInput(xpos, ypos);
	ClearSolButton->ProcessInput(xpos, ypos);
}

void ButtonsManager::SetLeftMouse(bool press)
{
	SolveButton->SetLeftMouse(press);

	AlgorithmButton->SetLeftMouse(press);
	BFSButton->SetLeftMouse(press);
	DFSButton->SetLeftMouse(press);

	ClearBoardButton->SetLeftMouse(press);
	ClearSolButton->SetLeftMouse(press);
}

