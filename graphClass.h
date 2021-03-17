#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H

#include "nodeClass.h"

class graphClass
{
public:
	void resetGraph();
	void clearClickedStatus();

	static const int graphRows = 46;
	static const int graphCols = 46;
	nodeClass graph[graphRows][graphCols];
};

#endif