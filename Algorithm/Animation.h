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
	void AddBlock(coordinates sq);

	// draw
	void Draw(float deltaTime);

	void SetSpeed(float val);

	void Reset();

private:
	// store all squares that must be animated
	std::vector<Animation> PathAnims, BlockAnims;
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
