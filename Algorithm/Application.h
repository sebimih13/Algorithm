#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Table.h"

class Application
{
public:
	// constructor/destructor
	Application(unsigned int width, unsigned int height);
	~Application();

	// game loop
	void Init();
	void Update(float deltaTime);
	void Draw();
	void ProcessInput(float deltaTime);

	// todo : test
	// components
	Table* TableMatrix;

private:
	// state
	unsigned int Width, Height;
	unsigned int TableWidth, TableHeight;
	float SquareSize;

};

#endif
