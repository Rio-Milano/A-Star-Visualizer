#include "PriorityQueue.h"

void PriorityQueue::siftUp(int given_PriorityQueuePosition)
{
	//Calculate where the parent of the given node is
	int parent_ofVertex = int(floor(given_PriorityQueuePosition / 2));

	//While the parent points to a valid node and the parent is greater than the given node
	while (parent_ofVertex != 0 &&
		graph[(heap[parent_ofVertex].first)][heap[parent_ofVertex].second].fCost >
		graph[heap[given_PriorityQueuePosition].first][heap[given_PriorityQueuePosition].second].fCost)
	{
		//swap the parent and the given node
		swapNodes(parent_ofVertex, given_PriorityQueuePosition);

		//Update new position of given node and calculate new position of parent
		given_PriorityQueuePosition = parent_ofVertex;
		parent_ofVertex = int(floor(given_PriorityQueuePosition / 2));
	}
}

void PriorityQueue::Siftdown(int given_PriorityQueuePosition)
{
	int leftChildPos;
	int rightChildPos;
	int currentNodePos;


	//While the node is not in the correct position in heap
	while (1)
	{
		leftChildPos = given_PriorityQueuePosition * 2;//get children positions
		rightChildPos = given_PriorityQueuePosition * 2 + 1;
		currentNodePos = given_PriorityQueuePosition;
		//If the node has no childen then it is in the correct place
		if (leftChildPos >= nextFreePosInPrioityQueue && rightChildPos >= nextFreePosInPrioityQueue)
			return;

		//If the node only has 1 left child
		else if (rightChildPos >= nextFreePosInPrioityQueue)
		{
			//Check if that left child is smaller in priority than the current node, if so swap it
			if (graph[heap[leftChildPos].first][heap[leftChildPos].second].fCost < graph[heap[currentNodePos].first][heap[currentNodePos].second].fCost)
			{
				swapNodes(graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ, given_PriorityQueuePosition);//swap the left child and the given node

				given_PriorityQueuePosition = graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ;
			}

			else   //If the left node was not smaller then return as node is in correct place
				return;
		}

		//if the node has 2 children then check if either one of them is smaller than the current node
		else
		{
			if (graph[heap[currentNodePos].first][heap[currentNodePos].second].fCost > graph[heap[leftChildPos].first][heap[leftChildPos].second].fCost ||
				graph[heap[currentNodePos].first][heap[currentNodePos].second].fCost > graph[heap[rightChildPos].first][heap[rightChildPos].second].fCost)
			{

				//if the left child is smaller
				if (graph[heap[leftChildPos].first][heap[leftChildPos].second].fCost <
					graph[heap[rightChildPos].first][heap[rightChildPos].second].fCost)
				{
					//swap the left child with the given node
					swapNodes(graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ, given_PriorityQueuePosition);

					//Update new positions in priority queue
					given_PriorityQueuePosition = graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ;
				}
				else//if the right child is smaller
				{
					//Swap current node with the right child
					swapNodes(graph[heap[rightChildPos].first][heap[rightChildPos].second].pos_in_PQ, given_PriorityQueuePosition);

					//Update new positions in priority queue
					given_PriorityQueuePosition = graph[heap[rightChildPos].first][heap[rightChildPos].second].pos_in_PQ;

				}
			}
			else
				//if the left and right child are greater then the current node then return as node is in correct place
				return;
		}
	}
}

void PriorityQueue::addToHeap(std::pair<int, int> given_priority)
{
	if (nextFreePosInPrioityQueue == maxPosInPriorityQueue)
		std::cout << "Error: Heap is full" << std::endl;
	else
	{
		//Add the entry into the next free position in the heap
		heap[nextFreePosInPrioityQueue] = given_priority;
		graph[given_priority.first][given_priority.second].pos_in_PQ = nextFreePosInPrioityQueue;
		nextFreePosInPrioityQueue++;

		//Heapify the node
		siftUp(nextFreePosInPrioityQueue - 1);
	}
}

std::pair<int, int> PriorityQueue::deleteMin()
{
	if (nextFreePosInPrioityQueue == 1)
	{
		std::cout << "Error: Heap is empty" << std::endl;
		return{ -1, -1 };
	}
	else
	{
		std::pair<int, int> temp = heap[1];//Take the node from the top
		heap[1] = heap[nextFreePosInPrioityQueue - 1];//set root node = to farthest node
		graph[heap[1].first][heap[1].second].pos_in_PQ = 1;//update the nodes position in the priority queue
		nextFreePosInPrioityQueue--;//make farthest most node as an avaliable spot

		//If there is still nodes in the Priority Queue then heapify the current node
		if (!(nextFreePosInPrioityQueue == 1))
			Siftdown(1);

		//Return the min node
		return temp;
	}
};

int PriorityQueue::getNextFree()//getter function to get next free from outside the object
{
	return nextFreePosInPrioityQueue;
}

std::pair<int, int> PriorityQueue::peakNextMin()
{
	if (nextFreePosInPrioityQueue == 1)
	{
		std::cout << "Error: Heap is empty" << std::endl;
		return { -1, -1 };
	}
	return { heap[1].first, heap[1].second };
}

void PriorityQueue::swapNodes(int given_PriorityQueuePosition_A, int given_PriorityQueuePosition_B)//helper function for sift up and down. Used to avoid redundant code when needing swapping
{
	//Swap the Vertices at the 2 given positions
	std::pair<int, int> temp = heap[given_PriorityQueuePosition_A];
	heap[given_PriorityQueuePosition_A] = heap[given_PriorityQueuePosition_B];
	heap[given_PriorityQueuePosition_B] = temp;

	//Update positions of the swapped vertices in priority queue

	graph[heap[given_PriorityQueuePosition_B].first][heap[given_PriorityQueuePosition_B].second].pos_in_PQ = given_PriorityQueuePosition_B; //>posInPQ = given_PriorityQueuePosition_B;
	graph[heap[given_PriorityQueuePosition_A].first][heap[given_PriorityQueuePosition_A].second].pos_in_PQ = given_PriorityQueuePosition_A; //>posInPQ = given_PriorityQueuePosition_B;
}

void PriorityQueue::clearHeap()
{
	nextFreePosInPrioityQueue = 1;
}