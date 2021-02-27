#include "AlgorithmSolver.h"

#include <algorithm>
#include <queue>

#define X first
#define Y second

AlgorithmSolver::AlgorithmSolver(unsigned int nrRow, unsigned int nrColumns, coordinates Start, coordinates Finish)
{
	algorithm = Algorithm::BFS;

	FoundFinish = false;

	this->nrRows = nrRow;
	this->nrColumns = nrColumns;
	this->Start = Start;
	this->Finish = Finish;

	Visited.resize(nrRow, std::vector<bool>(nrColumns, false));
	Block.resize(nrRow, std::vector<bool>(nrColumns, false));
}

bool AlgorithmSolver::IsInMatrix(coordinates p)
{
	return p.X >= 0 && p.X < nrRows && p.Y >= 0 && p.Y < nrColumns;
}

void AlgorithmSolver::Reset(bool solution)
{
	Path.clear();
	Tree.clear();
	Route.clear();

	for (unsigned int i = 0; i < nrRows; i++)
		for (unsigned int j = 0; j < nrColumns; j++)
		{
			Visited[i][j] = false;

			if (!solution)
				Block[i][j] = false;
		}
}

void AlgorithmSolver::SetStartingPosition(coordinates pos)
{
	Start = pos;
}

void AlgorithmSolver::SetFinishingPosition(coordinates pos)
{
	Finish = pos;
}

void AlgorithmSolver::AddBlock(coordinates pos)
{
	Block[pos.X][pos.Y] = true;
}

void AlgorithmSolver::DeleteBlock(coordinates pos)
{
	Block[pos.X][pos.Y] = false;
}

bool AlgorithmSolver::IsBlock(coordinates pos)
{
	return Block[pos.X][pos.Y];
}

void AlgorithmSolver::SetAlgorithm(Algorithm algo)
{
	// todo
	std::cout << "Algorithm set to : ";
	if (algo == Algorithm::BFS)
		std::cout << "BFS\n";
	else
		std::cout << "DFS\n";
	
	algorithm = algo;
}

void AlgorithmSolver::FindPath()
{
	Tree[Start] = { -1, -1 };		// the root of the tree
	FoundFinish = false;

	switch (algorithm)
	{
		case Algorithm::BFS: BFS(); break;
		case Algorithm::DFS: DFS(Start); break;
	}

	std::reverse(Path.begin(), Path.end());
	std::reverse(Route.begin(), Route.end());
}

void AlgorithmSolver::BFS()
{
	std::queue<coordinates> list;
	list.push(Start);
	Visited[Start.X][Start.Y] = true;

	while (!list.empty())
	{
		coordinates p = list.front();
		list.pop();
		Path.push_back(p);

		if (p == Finish)
		{
			while (Tree[Finish] != coordinates(-1, -1))
			{
				Route.push_back(Finish);
				Finish = Tree[Finish];
			}
			Route.push_back(Finish);

			return;
		}

		for (int i = 0; i < 4; i++)
		{
			coordinates next = { p.X + DirX[i], p.Y + DirY[i] };

			if (IsInMatrix(next) && !Visited[next.X][next.Y] && !Block[next.X][next.Y])
			{
				Tree[next] = p;
				Visited[next.X][next.Y] = true;
				list.push(next);
			}
		}
	}
}

void AlgorithmSolver::DFS(coordinates p)
{
	if (FoundFinish)
		return;

	Visited[p.X][p.Y] = true;
	Path.push_back(p);

	if (p == Finish)
	{
		while (Tree[Finish] != coordinates(-1, -1))
		{
			Route.push_back(Finish);
			Finish = Tree[Finish];
		}
		Route.push_back(Finish);

		FoundFinish = true;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		coordinates next = { p.X + DirX[i], p.Y + DirY[i] };

		if (IsInMatrix(next) && !Visited[next.X][next.Y] && !Block[next.X][next.Y])
		{
			Tree[next] = p;
			DFS(next);
		}
	}
}

