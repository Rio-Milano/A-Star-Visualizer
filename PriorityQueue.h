#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "graphClass.h"
#include<iostream>

class PriorityQueue : public graphClass
{
public://make proteftyed
	void siftUp(int);

	void Siftdown(int);
	
	void addToHeap(std::pair<int, int>);

	std::pair<int, int> deleteMin();

	int getNextFree();

	std::pair<int, int> peakNextMin();

	void clearHeap();


private:
	void swapNodes(int , int );

	std::pair<int, int> heap[1000];//giving 1000 elements for the heap
	int maxPosInPriorityQueue = 1000;//needed to know when heep is full
	int nextFreePosInPrioityQueue = 1;//heap is 1 bassed
};

#endif
