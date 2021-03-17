#include "pathFinding.h"

bool pathFinding::canMove(const int& y_1_, const int& x_1_, const int& y_2_, const int& x_2_)
{
	if (y_1_ >= 0 && y_1_ < graphRows && y_2_ >= 0 && y_2_ < graphRows &&
		x_1_ >= 0 && x_1_ < graphRows && x_2_ >= 0 && x_2_ < graphCols)
	{
		//if neither nodes are walls
		if (!graph[y_1_][x_1_].isNodeWall && !graph[y_2_][x_2_].isNodeWall)
			return true;
		if (!graph[y_1_][x_1_].isNodeWall && graph[y_2_][x_2_].isNodeWall)
			return true;
		if (graph[y_1_][x_1_].isNodeWall && !graph[y_2_][x_2_].isNodeWall)
			return true;
	}
	return false;

}

bool pathFinding::canMoveOnDiagonal(const std::pair<int, int>& currentNodePosInGraph, const int& i, const int& j)
{
	int y_1_, x_1_, y_2_, x_2_;

	if (currentNodePosInGraph.first - 1 == i && currentNodePosInGraph.second + 1 == j)
	{
		y_1_ = currentNodePosInGraph.first - 1;
		x_1_ = currentNodePosInGraph.second;

		y_2_ = currentNodePosInGraph.first;
		x_2_ = currentNodePosInGraph.second + 1;

		if (!canMove(y_1_, x_1_, y_2_, x_2_))
			return false;
	}
	//south east
	if (currentNodePosInGraph.first + 1 == i && currentNodePosInGraph.second + 1 == j)
	{
		y_1_ = currentNodePosInGraph.first;
		x_1_ = currentNodePosInGraph.second + 1;

		y_2_ = currentNodePosInGraph.first + 1;
		x_2_ = currentNodePosInGraph.second;

		if (!canMove(y_1_, x_1_, y_2_, x_2_))
			return false;
	}
	//south west
	if (currentNodePosInGraph.first + 1 == i && currentNodePosInGraph.second - 1 == j)
	{
		y_1_ = currentNodePosInGraph.first;
		x_1_ = currentNodePosInGraph.second - 1;

		y_2_ = currentNodePosInGraph.first + 1;
		x_2_ = currentNodePosInGraph.second;

		if (!canMove(y_1_, x_1_, y_2_, x_2_))
			return false;
	}

	//north west
	if (currentNodePosInGraph.first - 1 == i && currentNodePosInGraph.second - 1 == j)
	{
		y_1_ = currentNodePosInGraph.first - 1;
		x_1_ = currentNodePosInGraph.second;

		y_2_ = currentNodePosInGraph.first;
		x_2_ = currentNodePosInGraph.second - 1;

		if (!canMove(y_1_, x_1_, y_2_, x_2_))
			return false;
	}

	return true;
}

void pathFinding::AstartAlg(std::vector<std::pair<int, int>>& visual_overlay_discovered_nodes_, std::vector<std::pair<int, int>>& visual_overlay_locked_nodes_)
{
	std::pair<int, int> currentNodePosInGraph;//Variable to keep track of most optimal node

	if (getNextFree() == 1)//if there is no path
	{
		isDone = true;
		return;
	}

	currentNodePosInGraph = deleteMin();//delete optimal node

	if (currentNodePosInGraph.first == endNodePosY && currentNodePosInGraph.second == endNodePosX)//if optimal path to node found then stop
	{//if a path has been found
		isDone = true;
		return;
	}


	//lock node
	graph[currentNodePosInGraph.first][currentNodePosInGraph.second].isLocked = true;//lock current node
	visual_overlay_locked_nodes_.emplace_back(currentNodePosInGraph);

	//look at adjacent vertices
	for (int i = currentNodePosInGraph.first - 1; i < currentNodePosInGraph.first + 2; i++)
	{
		for (int j = currentNodePosInGraph.second - 1; j < currentNodePosInGraph.second + 2; j++)
		{
			if (i >= 0 && i < graphRows && j >= 0 && j < graphCols)
			{
				if (i == currentNodePosInGraph.first && j == currentNodePosInGraph.second)
					continue;

				else if (graph[i][j].isNodeWall)
				{
					continue;
				}

				else if (graph[i][j].isLocked == false)
				{
					long double adjDistanceToMove = 0;
					if (i - 1 == currentNodePosInGraph.first && j == currentNodePosInGraph.second)
						adjDistanceToMove = 1.f;
					else if (i + 1 == currentNodePosInGraph.first && j == currentNodePosInGraph.second)
						adjDistanceToMove = 1.f;
					else if (i == currentNodePosInGraph.first && j - 1 == currentNodePosInGraph.second)
						adjDistanceToMove = 1.f;
					else if (i == currentNodePosInGraph.first && j + 1 == currentNodePosInGraph.second)
						adjDistanceToMove = 1.f;
					else
						adjDistanceToMove = 1.41421356237;

					if (!canMoveOnDiagonal(currentNodePosInGraph, i, j))
						continue;


					if (graph[currentNodePosInGraph.first][currentNodePosInGraph.second].gCost +
						adjDistanceToMove <
						graph[i][j].gCost)
					{
						graph[i][j].gCost = graph[currentNodePosInGraph.first]
							[currentNodePosInGraph.second].gCost +
							adjDistanceToMove;

						graph[i][j].parentPos = currentNodePosInGraph;

						if (graph[i][j].isDiscovered == false)
						{
							addToHeap({i, j});
							graph[i][j].hCost = long double (abs(endNodePosX-j) + abs(endNodePosY-i));
							graph[i][j].isDiscovered = true;
							visual_overlay_discovered_nodes_.emplace_back(std::make_pair(i, j));

						}

						graph[i][j].fCost = graph[i][j].gCost + graph[i][j].hCost;
						siftUp(graph[i][j].pos_in_PQ);
					}

				}
			}

		}

	}
}