#ifndef BUTTON_H
#define BUTTON_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Table.h"
#include "AlgorithmSolver.h"
#include "TextRenderer.h"

#include <string>

enum class ButtonType
{
	Solve,
	Algorithm, BFS, DFS,
	ClearBoard, ClearSol
};


class Button
{
public:
	// constructor
	Button(glm::vec2 position, glm::vec2 size, glm::vec3 color, ButtonType type);

	void ProcessInput(double xpos, double ypos);
	void SetLeftMouse(bool press);

	void Render(TextRenderer* TextRender);

	bool IsClicked();

	void ToggleVisibility();

	std::string GetText();
	void SetText(std::string txt);

private:
	// button state
	ButtonType Type;

	glm::vec2 Size;
	glm::vec2 Position;
	glm::vec3 MainColor, SecondColor;
	std::string Text;

	bool Visible;

	bool MouseInButtonRange;
	bool LeftMousePressed;

	// render data
	GLuint SquareVAO;
	void InitRenderData();
};


class ButtonsManager
{
public:
	// constructor
	ButtonsManager(unsigned int width, unsigned int height);

	void Update(Table* table);
	void Render();

	void ProcessInput(double xpos, double ypos);
	void SetLeftMouse(bool press);

private:
	TextRenderer* TextRender;

	Button* SolveButton;
	Button* AlgorithmButton;
	Button* BFSButton;
	Button* DFSButton;
	Button* ClearBoardButton;
	Button* ClearSolButton;
};

#endif
