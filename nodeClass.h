#ifndef NODECLASS_H
#define NODECLASS_H


#define INF 10000
#include<utility>

class nodeClass
{
public:
	long double gCost = INF;
	long double hCost = INF;
	long double fCost = INF;

	bool has_been_clicked_on_ = false;

	std::pair<int, int> parentPos = { 999, 999 };

	int pos_in_PQ = 0;

	bool isNodeWall = false;//is obsticle
	bool isLocked = false;//has been removed from the PQ
	bool isDiscovered = false;//has had its hcost set
};
#endif

