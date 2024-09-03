/**********************************************
 * File: pqueue-extra.h
 *
 * Your own custom priority queue class, if you
 * want to build one for extra credit.
 *
 * Please replace these file comments with a
 * description of how your priority queue works.
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>
#include <set.h>
#include <unordered_map>
using namespace std;

/*
 * This is a priority queue using binomial heap
 */
class ExtraPriorityQueue {
public:
	
	/* Constructs a new, empty priority queue. */
	ExtraPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~ExtraPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
	
	struct Node {
		string value;
		Node* leftChild;
		Node* parent;
		Node* rightSibling;
		int degree;

	};
	Vector<Node*> roots;
	int queueSize;
	bool hasDegree0;
	void deleteTree(Node* node);
	void merge();
	Node* combineTrees(Node* tree1, Node* tree2);
};

#endif
