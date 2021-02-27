#ifndef ALGORITHM_SOLVER_H
#define ALGORITHM_SOLVER_H

#include <glad/glad.h>

#include <iostream>
#include <vector>
#include <map>

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

	void Reset(bool solution);
	
	void SetStartingPosition(coordinates pos);
	void SetFinishingPosition(coordinates pos);

	void SetAlgorithm(Algorithm algo);

	void DeleteBlock(coordinates pos);
	void AddBlock(coordinates pos);

	// the path the algorithm follows
	std::vector<coordinates> Path;

	// the fastest route to finish
	std::vector<coordinates> Route;

	void FindPath();

	// return true if the pos is a block
	bool IsBlock(coordinates pos);

private:
	// algorithm data
	Algorithm algorithm;
	unsigned int nrRows, nrColumns;
	coordinates Start, Finish;
	std::vector<std::vector<bool>> Visited, Block;

	// directions
	const int DirX[4] = { 0, 1, 0, -1 };
	const int DirY[4] = { 1, 0, -1, 0 };

	// the algorithms
	void BFS();
	void DFS(coordinates p);		
	bool FoundFinish;

	// utility
	bool IsInMatrix(coordinates p);

	// the fastest route to finish represented as a tree
	std::map<coordinates, coordinates> Tree;
};

#endif
