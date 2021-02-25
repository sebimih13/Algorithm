#ifndef TABLE_H
#define TABLE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "AlgorithmSolver.h"
#include "Animation.h"

enum class TableState
{
	TABLE_DRAW,
	TABLE_VISUALIZE
};

class Table
{
public:
	// constructor
	Table(unsigned int width, unsigned int height, float squareSize, unsigned int windowWidth, unsigned int windowHeight);

	// table state
	TableState State;

	// draw table as a texture
	void DrawSprite(float deltaTime);

	// process mouse input
	void ProcessInput(double xpos, double ypos);
	void SetLeftMouse(bool press);
	void SetRightMouse(bool press);

	// set the position of the textures top-right corner
	void SetSpritePosition(glm::vec2 pos);

	// solve
	void StartAlgorithm();

	// update animations
	void Update(float deltaTime);
	float AnimationCooldown, LastAnimation;

	// clear table
	void ClearBoard(bool solution);

	// algorithm solver
	AlgorithmSolver* Solver;

	// animation manager
	AnimationManager* Animation;

private:
	// data
	unsigned int Width, Height;					// size of table
	unsigned int WindowWidth, WindowHeight;		// size of window
	float SquareSize;							// square side size
	int NrRows, NrColumns;						// number of rows and colums of our table
	Texture2D Texture;							// table texture 
	glm::vec2 position;							// where to draw the texture of the table (top-right coordonates)
	bool LeftMousePressed;						// if the left mouse button is pressed
	bool RightMousePressed;						// if the right mouse button is pressed

	// selected square : begins from 0, 0 -> NrRows - 1, NrColumns - 1
	int SquareX, SquareY;

	bool IsMouseInTable();

	// data for the starting point
	int StartPointX, StartPointY;
	int LastStartPointX, LastStartPointY;
	bool MoveStartPoint;

	// data for the finishing point
	int FinishPointX, FinishPointY;
	int LastFinishPointX, LastFinishPointY;
	bool MoveFinishPoint;

	// if a block was added last time
	bool BlockLastFrame;

	// render data
	GLuint RowVAO, ColumnVAO, QuadVAO, CircleVAO;		// Vertex Array Objects
	GLuint StartVAO;
	GLuint FBO;											// Framebuffer

	// draw functions
	void Draw(float deltaTime);				// draw table to FBO/Texture
	void DrawOutline();						// draw outline for the selected square
	void DrawStart();						// draw start point
	void DrawFinish();						// draw finish point

	const int TriangleAmount;														// nr of triangles used to draw circle
	void DrawCircle(float StartX, float StartY, glm::vec2 scale, glm::vec3 color);	// draw a circle with top-left corner (x, y)

	// initialize render data
	void InitRenderData();

	// colors
	glm::vec3 White;
	glm::vec3 Blue;
	glm::vec3 Yellow;
	glm::vec3 Red;
	glm::vec3 Purple;
};

#endif
