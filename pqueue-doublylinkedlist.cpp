/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */

#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	listSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	while (head != NULL) {
		Cell* temp = head;
		head = head->next;
		delete temp;
	}
	listSize = 0;
}

int DoublyLinkedListPriorityQueue::size() {
	// TODO: Fill this in!

	return listSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!

	return listSize == 0 || head == NULL;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	listSize++;
	if (head == NULL) {
		head = new Cell;
		head->value = value;
		head->next = NULL;
		head->previous = NULL;
	}

	Cell* cell = new Cell;
	cell->value = value;
	head->previous = cell;
	cell->next = head;
	cell->previous = NULL;
	head = cell;

}
string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("Queue is empty");
	}
	Cell* temp = head;
	Cell* minimal = head;
	while (temp->next != NULL) {
		if (temp->value < minimal->value) {
			minimal = temp;
		}
		temp = temp->next;
	}
	
	return minimal->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("Queue is empty");
	}
	listSize--;
	Cell* temp = head;
	Cell* minimal = head;
	string str = "";
	if (head->next == NULL) {
		str = head->value;
		head = NULL;
		return str;
	}
	while (temp->next != NULL) {
		if (temp->value < minimal->value) {
			minimal = temp;
		}
		temp = temp->next;
	}
	if (head == minimal) {
		string s = head->value;
		head = head->next;
		if (head != NULL) {
			head->previous = NULL;
		}
		return s;
	}

	if (minimal->next == NULL) {
		minimal->previous->next = NULL;
	}
	else {
		minimal->previous->next = minimal->next;
		minimal->next->previous = minimal->previous;
	}
	str = minimal->value;
	delete minimal;
	return str;
}