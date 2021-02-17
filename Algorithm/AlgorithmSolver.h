#ifndef ALGORITHM_SOLVER_H
#define ALGORITHM_SOLVER_H

#include <glad/glad.h>

#include <iostream>
#include <vector>

typedef std::pair<unsigned int, unsigned int> coordinates;

enum class Algorithm
{
	BFS,
	DFS
};

class AlgorithmSolver
{
public:
	// constructor
	AlgorithmSolver(unsigned int nrRow, unsigned int nrColumns, coordinates Start, coordinates Finish);

	void Reset();
	
	void SetStartingPosition(coordinates pos);
	void SetFinishingPosition(coordinates pos);

	void DeleteBlock(coordinates pos);
	void AddBlock(coordinates pos);

	// path
	std::vector<coordinates> Path;

	void FindPath(Algorithm algo);

	// return true if the pos is a block
	bool IsBlock(coordinates pos);

private:
	// algorithm data
	unsigned int nrRows, nrColumns;
	coordinates Start, Finish;
	std::vector<std::vector<bool>> Visited, Block;

	// directions
	const int DirX[4] = { 0, 1, 0, -1 };
	const int DirY[4] = { 1, 0, -1, 0 };

	// the algorithms
	void BFS();
	void DFS();		// todo

	// utility
	bool IsInMatrix(coordinates p);
};

#endif
