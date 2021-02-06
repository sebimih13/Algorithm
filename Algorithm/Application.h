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
	void ChangeResolution(unsigned int width, unsigned int height);

private:
	// state
	unsigned int Width, Height;

	// components
	Table* TableMatrix;

	// projection matrix
	glm::mat4 projection;

};

#endif
