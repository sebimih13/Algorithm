#include "Application.h"

#include "ResourceManager.h"
#include "shader.h"

#include <iostream>
#include <string>

Application::Application(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
	projection = glm::ortho(0.0f, (float)Width, (float)Height, 0.0f, -1.0f, 1.0f);
}

Application::~Application()
{
	delete TableMatrix;
}

void Application::Init()
{
	// load shaders
	ResourceManager::LoadShader("shaders/line.vert", "shaders/line.frag", nullptr, "line");

	// configure shader
	ResourceManager::GetShader("line").Use();
	ResourceManager::GetShader("line").SetMatrix4f("projection", projection);

	// configure table
	TableMatrix = new Table(Width, Height, 25.0f);
}

void Application::Update(float deltaTime)
{

}

void Application::Draw()
{
	TableMatrix->Draw();
}

void Application::ProcessInput(float deltaTime)
{

}

void Application::ChangeResolution(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
	projection = glm::ortho(0.0f, (float)Width, (float)Height, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("line").SetMatrix4f("projection", projection);
	TableMatrix->ChangeResolution(Width, Height);
}
