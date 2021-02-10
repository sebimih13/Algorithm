#include "Application.h"

#include "ResourceManager.h"
#include "shader.h"

#include <iostream>
#include <string>

Application::Application(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;

	// todo : calibrate values
	TableWidth = width - 40;
	TableHeight = height - 140;		
	SquareSize = 30.0f;
}

Application::~Application()
{
	delete TableMatrix;
}

void Application::Init()
{
	// configure table
	TableMatrix = new Table(TableWidth, TableHeight, SquareSize);

	// load shaders
	ResourceManager::LoadShader("shaders/line.vert", "shaders/line.frag", nullptr, "line");
	ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");

	// configure shader
	glm::mat4 projection = glm::ortho(0.0f, (float)TableWidth, (float)TableHeight, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetMatrix4f("projection", projection);

	projection = glm::ortho(0.0f, (float)Width, (float)Height, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use();
	ResourceManager::GetShader("sprite").SetMatrix4f("projection", projection);
	ResourceManager::GetShader("sprite").SetInteger("sprite", 0);
}

void Application::Update(float deltaTime)
{

}

void Application::Draw()
{
	unsigned int diff = (Width - TableWidth) / 2;
	TableMatrix->DrawSprite(glm::vec3(diff, Height - TableHeight - diff, 0.0f), Width, Height);
}

void Application::ProcessInput(float deltaTime)
{
	
}

