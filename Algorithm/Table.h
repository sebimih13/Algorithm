#ifndef TABLE_H
#define TABLE_H

#include <glad/glad.h>

class Table
{
public:
	// constructor
	Table(unsigned int width, unsigned int height, float squareSize);

	// TODO: draw a texture of the table
	void Draw();
	void ChangeResolution(unsigned int width, unsigned int height);

private:
	// size of table
	unsigned int Width, Height;
	
	// square side size
	float SquareSize;

	// render data
	GLuint RowVAO, ColumnVAO;

	// initialize render data
	void Init();
};

#endif
