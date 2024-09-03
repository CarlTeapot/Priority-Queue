/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	listSize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != nullptr) {
		Cell* temp = head;
		head = head->next;
		delete temp;
	}
}

int LinkedListPriorityQueue::size() {
	return listSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return listSize == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	listSize++;
	Cell* newCell = new Cell;
	newCell->value = value;
	newCell->next = nullptr;

	if (head == nullptr || head->value > value) {
		newCell->next = head;
		head = newCell;
		return;
	}
	Cell* temp = head;
	while (temp->next != nullptr && temp->next->value <= value) {
		temp = temp->next;
	}
	newCell->next = temp->next;
	temp->next = newCell;
}

string LinkedListPriorityQueue::peek() {
	if (listSize == 0)
		error("Queue is Empty");

	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (listSize == 0)
		error("Queue is Empty");
	listSize--;
	string str = head->value;
	Cell* toBeRemoved = head;
	head = head->next;
	delete toBeRemoved;
	return str;
}

