/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include <vector.h>

VectorPriorityQueue::VectorPriorityQueue() {
	minIndex = 0;
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {
	
	return queue.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return  queue.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!

	queue.push_back(value);
	if (value <= queue[minIndex])
		minIndex = queue.size() - 1;
		
}


string VectorPriorityQueue::peek() {
	if (isEmpty()) {
		error("Queue is empty");
	}
	return queue[minIndex];
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (isEmpty()) {
		error("Queue is empty");
	}
	string str = queue[minIndex];
	queue.remove(minIndex);
	if (!isEmpty()) {
		int min = 0;
		int n = queue.size();
		for (int i = 0; i <= n / 2; i++) {
			if (queue[i] < queue[min])
				min = i;
			if (queue[n - i - 1] < queue[min])
				min = n - i - 1;
		}
		minIndex = min;
	}
	else {
		minIndex = 0;
	}
	
	return str;
}

