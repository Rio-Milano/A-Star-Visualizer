#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "PriorityQueue.h"
#include<utility>
#include<vector>

class pathFinding : public PriorityQueue
{
public:
	void AstartAlg(std::vector<std::pair<int, int>>& , std::vector<std::pair<int, int>>& );
	

	int startNodePosX = 0;
	int startNodePosY = 0;
	int endNodePosX = 45;
	int endNodePosY = 45;
	bool isDone = false;
private:
	bool canMove(const int& y_1_, const int& x_1, const int& y_2_, const int& x_2_);
	bool canMoveOnDiagonal(const std::pair<int, int>&, const int&, const int&);
};

#endif