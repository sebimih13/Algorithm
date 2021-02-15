#include "AlgorithmSolver.h"

#include <algorithm>
#include <queue>

#define X first
#define Y second

AlgorithmSolver::AlgorithmSolver(unsigned int nrRow, unsigned int nrColumns, coordinates Start, coordinates Finish)
{
	this->nrRows = nrRow;
	this->nrColumns = nrColumns;
	this->Start = Start;
	this->Finish = Finish;

	Visited.resize(nrRow, std::vector<bool>(nrColumns, false));
}

bool AlgorithmSolver::IsInMatrix(coordinates p)
{
	return p.X >= 0 && p.X < nrRows && p.Y >= 0 && p.Y < nrColumns;
}

void AlgorithmSolver::Reset()
{
	Path.clear();

	for (unsigned int i = 0; i < nrRows; i++)
		for (unsigned int j = 0; j < nrColumns; j++)
			Visited[i][j] = false;
}

void AlgorithmSolver::SetStartingPosition(coordinates pos)
{
	Start = pos;
}

void AlgorithmSolver::SetFinishingPosition(coordinates pos)
{
	Finish = pos;
}

void AlgorithmSolver::FindPath(Algorithm algo)
{
	// todo
	std::cout << "ROWS : " << nrRows << '\n';
	std::cout << "COLUMNS : " << nrColumns << '\n';
	std::cout << "START : " << Start.X << ' ' << Start.Y << '\n';
	std::cout << "FINISH : " << Finish.X << ' ' << Finish.Y << '\n';

	switch (algo)
	{
		case Algorithm::BFS: BFS(); break;
		case Algorithm::DFS: DFS(); break;
	}

	std::reverse(Path.begin(), Path.end());
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
			return;

		for (int i = 0; i < 4; i++)
		{
			coordinates next = { p.X + DirX[i], p.Y + DirY[i] };

			if (IsInMatrix(next) && !Visited[next.X][next.Y])
			{
				Visited[next.X][next.Y] = true;
				list.push(next);
			}
		}
	}
}

void AlgorithmSolver::DFS()
{
	// todo
}

