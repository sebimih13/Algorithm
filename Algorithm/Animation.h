#ifndef ANIMATION_H
#define ANIMATION_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

typedef std::pair<unsigned int, unsigned int> coordinates;

struct Animation
{
	Animation(coordinates pos)
	{
		position = pos;
	}

	coordinates position;
	float scale = 1.0f;
};

class AnimationManager
{
public:
	// constructor
	AnimationManager(float squareSize);

	// add a new square to the list of animated squares
	void AddSquare(coordinates sq);

	// add a new square to the route list
	void AddSquareFinalRoute(coordinates sq);

	// blocking squares
	void AddBlock(coordinates sq);
	int FindBlock(coordinates& sq);
	void DeleteBlock(coordinates sq);

	// draw
	void Draw(float deltaTime);

	void Reset(bool solution);

private:
	// store all squares that must be animated
	std::vector<Animation> PathAnims, BlockAnims, RouteAnims;
	float SquareSize;
	float Speed;

	// initialize render data
	void InitRenderData();

	// render data
	GLuint SquareVAO;

	// draw
	void DrawSquare(Animation& sq, glm::vec3 color);
};

#endif
