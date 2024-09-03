/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
const int initialSize = 10;
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	arrSize = 0;
	array = new string[initialSize];
	realSize = initialSize;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] array;
	arrSize = 0;
	realSize = 0;
}

int HeapPriorityQueue::size() {
	// TODO: Fill this in!
	
	return arrSize;
}

bool HeapPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return arrSize == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if (arrSize == realSize) {
		realSize *= 2;
		string* arr = new string[realSize];
		for (int i = 0; i < arrSize; i++) {
			arr[i] = array[i];
		}
		delete[] array;
		array = arr;
	}
	int n = arrSize;
    array[n] = value;
	arrSize++;
	while (array[n] < array[(n-1)/ 2] && n >= 0) {
		swap(array[n], array[(n-1) / 2]);
		n = (n-1)/2;
	}
}

string HeapPriorityQueue::peek() {

	if (isEmpty())
		error("Queue is empty");

	return array[0];
}

string HeapPriorityQueue::dequeueMin() {

	if (isEmpty())
		error("Queue is empty");

	string ans = array[0];
	
    int n = --arrSize;

	array[0] = array[arrSize];
	int m = 0;

	int index = (2 * m) + 1;

	while (index < n) {
		if (((2 * m) + 2 < n) && array[(2 * m) + 2] < array[index])
			index = (2 * m) + 2;
		if (array[m] > array[index]) {
			swap(array[m], array[index]);
			m = index;
			index = (2 * m) + 1;
		}
		else {
			break;
		}
	}
	return ans;
}

