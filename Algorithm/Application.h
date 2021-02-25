#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Table.h"
#include "Button.h"

class Application
{
public:
	// constructor/destructor
	Application(unsigned int width, unsigned int height);
	~Application();

	// game loop
	void Init();
	void Update(float deltaTime);
	void Draw(float deltaTime);
	void ProcessInput(float deltaTime);
	void SetMousePosition(double xpos, double ypos);
	void SetLeftMouse(bool press);
	void SetRightMouse(bool press);

private:
	// state
	unsigned int Width, Height;
	unsigned int TableWidth, TableHeight;
	float SquareSize;

	glm::mat4 ProjectionTable;
	glm::mat4 ProjectionWindow;

	// components
	Table* TableMatrix;
	ButtonsManager* Buttons;
};

#endif
