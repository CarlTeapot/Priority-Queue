/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"
#include <unordered_map>
// constructor
ExtraPriorityQueue::ExtraPriorityQueue() {
	hasDegree0 = false;
	queueSize = 0;
}
// deletes all of the root trees recursively
ExtraPriorityQueue::~ExtraPriorityQueue() {
	for (Node* node : roots) {
		deleteTree(node);
	}
	queueSize = 0;
}
// Binomial trees have a cool property: if their degree is K, their size is 2^K
// so instead of using the global variable,
//  i could have iterated over the trees and summed up their sizes 
// (which would be 2^(roots[0].degree + 2^(roots[1].degree) and so on)
// but i thought that using a global variable would be faster
int ExtraPriorityQueue::size() {
	
	return queueSize;
}
// 
bool ExtraPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return roots.isEmpty() || queueSize == 0;
}

// recursive function that deletes a single binomial tree
void ExtraPriorityQueue::deleteTree(Node* node) {
	if (node == nullptr) return;
	deleteTree(node->leftChild);
	deleteTree(node->rightSibling);
	delete node;
}

// adds a single node of degree 0 in the roots. 
// if the roots list doesnt contain a tree of degree 0, we just insert it without calling the merge function)
// otherwise, we merge the trees

void ExtraPriorityQueue::enqueue(string value) {
	queueSize++;
	Node* node = new Node;
	node->value = value;
	node->degree = 0;
	node->leftChild = NULL;
	node->rightSibling = NULL;
	node->parent = NULL;
	if (!hasDegree0) {
		roots.add(node);
		hasDegree0 = true;
		return;
	}
	else {
		roots.add(node);
		merge();
	}
}
// combines the two binomial trees by making the lexicographically larger node a child of an another node
ExtraPriorityQueue::Node* ExtraPriorityQueue::combineTrees(Node* tree1, Node* tree2) {
	if (tree1->value < tree2->value) {
		tree2->parent = tree1;
		tree2->rightSibling = tree1->leftChild;
		tree1->leftChild = tree2;
		tree1->degree++;
		return tree1;
	}
	else {
		tree1->parent = tree2;
		tree1->rightSibling = tree2->leftChild;
		tree2->leftChild = tree1;
		tree2->degree++;
		return tree2;
	}
}
 // this function merges the binomial trees until it satisfies the binomial heap rule
// (any degree of a binomial tree has to occur at most once in a binomial heap) 
void ExtraPriorityQueue::merge() {

	Map<int, Node*> degrees;
	Vector<Node*> newRoots;

	for (Node* node : roots) {
		while (degrees.containsKey(node->degree)) {
			node = combineTrees(node, degrees.get(node->degree));
			degrees.remove(node->degree-1);
		}
		degrees[node->degree] =  node;
	}
	for (int degree : degrees) {
		newRoots.add(degrees.get(degree));
	}
	roots = newRoots;
	hasDegree0 = degrees.containsKey(0);
}



string ExtraPriorityQueue::peek() {
	if (isEmpty())
		error("Queue is empty");
	// TODO: Fill this in!
	string min = roots[0]->value;
	for (Node* node : roots) {
		if (node->value < min)
			min = node->value;
	}
	return min;
}
// returns the lexicographically smallest string by iterating over the roots 
// after finding the smallest string, we remove it from the roots list and put its children in the list
// then we delete the min node from the memory and call the merge function 
string ExtraPriorityQueue::dequeueMin() {
	if (isEmpty())
		error("Queue is empty");
	queueSize--;
	int min = 0;
	for (int i = 0; i < roots.size(); i++) {
		if (roots[i]->value < roots[min]->value)
			min = i;
	}
	
	string answ = roots[min]->value;
	Vector<Node*> children;

	Node* temp = roots[min]->leftChild;
	while (temp != NULL) {
		temp->parent = NULL;
		children.add(temp);
		temp = temp->rightSibling;
	}
	delete roots[min];
	roots.remove(min);
	roots += children;
	if (roots.size() > 1)
		merge();
	return answ;
	
}

