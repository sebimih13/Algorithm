#ifndef TABLE_H
#define TABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"

class Table
{
public:
	// constructor
	Table(unsigned int width, unsigned int height, float squareSize);

	// Draw table as a texture
	void DrawSprite(glm::vec2 position, unsigned int width, unsigned int height);

	// process mouse input
	void ProcessInput(double xpos, double ypos);

private:
	// size of table
	unsigned int Width, Height;
	
	// square side size
	float SquareSize;

	// number of rows and colums of our table
	int NrRows;
	int NrColumns;

	// selected square : begin from 0, 0 -> NrRows - 1, NrColumns - 1
	int SquareY;
	int SquareX;

	// render data
	GLuint RowVAO, ColumnVAO, QuadVAO;

	// Draw table to Texture
	void Draw();
	Texture2D Texture;

	void DrawOutline();

	// Framebuffer and quad VAO
	GLuint FBO, VAO;

	// initialize render data
	void InitRenderData();

	// colors
	glm::vec3 White;
	glm::vec3 Blue;
};

#endif
