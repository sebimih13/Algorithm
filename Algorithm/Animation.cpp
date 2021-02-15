#include "Animation.h"
#include "ResourceManager.h"

#include <algorithm>

#define X first
#define Y second

AnimationManager::AnimationManager(float squareSize)
	: SquareSize(squareSize), Speed(50.0f)
{
	InitRenderData();
}

void AnimationManager::InitRenderData()
{
	float SquareVertices[] = {
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	GLuint SquareVBO;
	glGenVertexArrays(1, &SquareVAO);
	glGenBuffers(1, &SquareVBO);

	glBindBuffer(GL_ARRAY_BUFFER, SquareVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareVertices), SquareVertices, GL_STATIC_DRAW);

	glBindVertexArray(SquareVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AnimationManager::Draw(float deltaTime)
{
	for (Animation& sq : Anims)
	{
		sq.scale = std::min(SquareSize - 5.0f, sq.scale + Speed * deltaTime);

		float StartX = (float)sq.position.Y * SquareSize;
		float StartY = (float)sq.position.X * SquareSize;

		// todo : calculate color based on scale
		glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

		ResourceManager::GetShader("line").Use();
		ResourceManager::GetShader("line").SetVector3f("color", color);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(StartX + (SquareSize - sq.scale) / 2, StartY + (SquareSize - sq.scale) / 2, 0.0f));
		model = glm::scale(model, glm::vec3(sq.scale, sq.scale, 0.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(SquareVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}

void AnimationManager::AddSquare(coordinates sq)
{
	Anims.push_back(Animation(sq));
}

void AnimationManager::SetSpeed(float val)
{
	Speed = val;
}

void AnimationManager::Reset()
{
	Anims.clear();
}

