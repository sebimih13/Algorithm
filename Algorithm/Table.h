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
	Table(unsigned int width, unsigned int height, float squareSize, unsigned int windowWidth, unsigned int windowHeight);

	// draw table as a texture
	void DrawSprite();

	// process mouse input
	void ProcessInput(double xpos, double ypos);

	// set the position of the textures top-right corner
	void SetSpritePosition(glm::vec2 pos);

private:
	// data
	unsigned int Width, Height;					// size of table
	unsigned int WindowWidth, WindowHeight;		// size of window
	float SquareSize;							// square side size
	int NrRows, NrColumns;						// number of rows and colums of our table
	Texture2D Texture;							// table texture 
	glm::vec2 position;							// where to draw the texture of the table (top-right coordonates)

	// selected square : begins from 0, 0 -> NrRows - 1, NrColumns - 1
	int SquareX, SquareY;

	// render data
	GLuint RowVAO, ColumnVAO, QuadVAO;		// Vertex Array Objects
	GLuint FBO;								// Framebuffer

	// draw functions
	void Draw();			// draw table to FBO/Texture
	void DrawOutline();		// draw outline for the selected square
	void DrawStart();		// draw start point
	void DrawFinish();		// draw finish point

	// initialize render data
	void InitRenderData();

	// colors
	glm::vec3 White;
	glm::vec3 Blue;
};

#endif
