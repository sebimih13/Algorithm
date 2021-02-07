#include "Table.h"
#include "ResourceManager.h"

#include <iostream>

Table::Table(unsigned int width, unsigned int height, float squareSize)
	: Width(width), Height(height), SquareSize(squareSize)
{
	Init();
}

void Table::Init()
{
	float vertices[] = {
		0.0f, 0.0f,			// row left
		1.0f, 0.0f,			// row right

		0.0f, 0.0f,			// column top
		0.0f, 1.0f			// column down
	};

	// initialize VAO, VBO
	GLuint VBO;

	glGenVertexArrays(1, &RowVAO);
	glGenVertexArrays(1, &ColumnVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(RowVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindVertexArray(ColumnVAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(4 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Table::Draw()
{
	ResourceManager::GetShader("line").Use();

	glLineWidth(2.0f);

	glm::mat4 model = glm::mat4(1.0f);

	// draw rows
	for (float y = 0.0f; y <= (float)Height; y += SquareSize)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, y, 0.0f));
		model = glm::scale(model, glm::vec3((float)Width, 0.0f, 0.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(RowVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	// draw columns
	for (float x = 0.0f; x <= (float)Width; x += SquareSize)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0f, float(Height), 0.0f));
		ResourceManager::GetShader("line").SetMatrix4f("model", model);

		glBindVertexArray(ColumnVAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	glBindVertexArray(0);
	glLineWidth(0.0f);
}

void Table::ChangeResolution(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
}
