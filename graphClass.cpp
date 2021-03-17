#include "graphClass.h"

void graphClass::resetGraph()
{
	for (int i = 0; i < graphRows; i++)
	{
		for (int j = 0; j < graphCols; j++)
		{
			graph[i][j].fCost = INF;
			graph[i][j].hCost = INF;
			graph[i][j].gCost = INF;
			graph[i][j].parentPos = {999, 999};
			graph[i][j].pos_in_PQ = 0;

			graph[i][j].isDiscovered = false;
			graph[i][j].isLocked = false;
			graph[i][j].isNodeWall = false;

		}
	}
}

void graphClass::clearClickedStatus()
{
	for (int i = 0; i < graphRows; i++)
	{
		for (int j = 0; j < graphCols; j++)
		{
			graph[i][j].has_been_clicked_on_ = false;

		}
	}
}