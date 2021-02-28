#include "Application.h"

#include "ResourceManager.h"
#include "shader.h"

#include <iostream>
#include <string>

Application::Application(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;

	TableWidth = width - 40;
	TableHeight = height - 140;		
	SquareSize = 30.0f;
}

Application::~Application()
{
	delete TableMatrix;
	delete Buttons;
}

void Application::Init()
{
	// load shaders
	ResourceManager::LoadShader("shaders/line.vert", "shaders/line.frag", nullptr, "line");
	ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");

	// configure shader
	ProjectionTable = glm::ortho(0.0f, (float)TableWidth, (float)TableHeight, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetMatrix4f("projection", ProjectionTable);

	ProjectionWindow = glm::ortho(0.0f, (float)Width, (float)Height, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use();
	ResourceManager::GetShader("sprite").SetMatrix4f("projection", ProjectionWindow);
	ResourceManager::GetShader("sprite").SetInteger("sprite", 0);


	// configure table
	TableMatrix = new Table(TableWidth, TableHeight, SquareSize, Width, Height);

	unsigned int diff = (Width - TableWidth) / 2;
	TableMatrix->SetSpritePosition(glm::vec3(diff, Height - TableHeight - diff, 0.0f));

	// butons manager
	Buttons = new ButtonsManager(Width, Height);
}

void Application::Update(float deltaTime)
{
	TableMatrix->Update(deltaTime);
	Buttons->Update(TableMatrix);
}

void Application::Draw(float deltaTime)
{
	// table projection
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetMatrix4f("projection", ProjectionTable);
	TableMatrix->DrawSprite(deltaTime);

	// window projection
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetMatrix4f("projection", ProjectionWindow);
	Buttons->Render();
}

void Application::SetMousePosition(double xpos, double ypos)
{
	TableMatrix->ProcessInput(xpos, ypos);
	Buttons->ProcessInput(xpos, ypos);
}

void Application::SetLeftMouse(bool press)
{
	TableMatrix->SetLeftMouse(press);
	Buttons->SetLeftMouse(press);
}

void Application::SetRightMouse(bool press)
{
	TableMatrix->SetRightMouse(press);
}

