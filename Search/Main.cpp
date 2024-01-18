#include "Node.h"
#include <iostream>
#include <list>

using char_node_t = node<char>;
using namespace std;

vector<char_node_t*> getDFS(char_node_t* root, char target)
{
	// check for valid root node
	if (root == nullptr) return vector<char_node_t*>();

	// create nodes stack and push root onto stack
	vector<char_node_t*> node_stack;
	//<set root visited to true>
	root->visited = true;
	//<push root onto node_stack>
	node_stack.push_back(root);

	while (!node_stack.empty())
	{
		// get current node from the top of stack
		char_node_t* current = node_stack.back();
		// check if the current node data is target value
		if (current->data == target)
		{
			cout << "found: " << current->data << endl;
			break;
		}
		else
		{
			cout << "visited: " << current->data << endl;
		}

		// if target not found then go down tree (child of current node)
		// push unvisited child node onto stack
		// pop node if there are no unvisited children
		bool popNode = true;
		for (auto& child : current->children)
		{
			// if child node is unvisited then mark visited and push onto stack
			if (!child->visited)
			{
				child->visited = true;
				node_stack.push_back(child);
				popNode = false;
				break;
			}
		}
		// if no unvisited children of the current node then pop the stack to go back up the tree
		if (popNode)
		{
			node_stack.pop_back();
		}
	}

	// convert stack nodes to vector of nodes (path)
	// stack nodes are in reverse order with the target at the top
	// add stack nodes to front of path vector
	vector<char_node_t*> path;
	while (!node_stack.empty())
	{
		// add top node and then pop node off of stack
		path.insert(path.begin(), node_stack.back());
		node_stack.pop_back();
	}

	return path;
}

vector<char_node_t*> getBFS(char_node_t* root, char target)
{
	// check for valid root node
	if (root == nullptr) return vector<char_node_t*>();

	// create nodes queue and queue root onto stack
	list<char_node_t*> node_queue;
	root->visited = true;
	node_queue.push_back(root);

	while (!node_queue.empty())
	{
		// get current node from the front of the queue
		char_node_t* current = node_queue.front();
		// check if the current node data is target value
		if (current->data == target)
		{
			cout << "found: " << current->data << endl;
			break;
		}
		else
		{
			cout << "visit: " << current->data << endl;
		}

		// if target not found then push all the children of the current node into the queue
		for (auto& child : current->children)
		{
			if (!child->visited)
			{
				child->visited = true;
				child->parent = current;
				node_queue.push_back(child);
			}
		}

		// pop the front of the queue
		node_queue.pop_front();
	}

	// convert nodes to vector of nodes (path)
	// nodes are in reverse order with the parent used to move through the nodes
	// add nodes to front of path vector
	vector<char_node_t*> path;
	char_node_t* node = (node_queue.empty()) ? nullptr : node_queue.front();
	while (node)
	{
		// add node and then set node to node parent
		path.insert(path.begin(), node);
		node = node->parent;
	}

	return path;
}

int main()
{
	//      A
	//    B   C
	//  D   E   F
	// create nodes with char data
	char_node_t* nodeA = new char_node_t{ 'A' };
	char_node_t* nodeB = new char_node_t{ 'B' };
	char_node_t* nodeC = new char_node_t{ 'C' };
	char_node_t* nodeD = new char_node_t{ 'D' };
	char_node_t* nodeE = new char_node_t{ 'E' };
	char_node_t* nodeF = new char_node_t{ 'F' };
	// create tree from nodes (children)
	nodeA->children.push_back(nodeB); // A->B
	// create the other connections as shown in the tree at the top (A->C, B->D, ...)
	nodeB->children.push_back(nodeD); // B->D
	nodeB->children.push_back(nodeE); // B->E
	nodeA->children.push_back(nodeC); // A->C
	nodeC->children.push_back(nodeE); // C->E
	nodeC->children.push_back(nodeF); // C->F

	// get search path to 'F' from node 'A'
	//auto path = getDFS(nodeA, 'F');
	auto path = getBFS(nodeA, 'F');
	// display path result
	cout << "path: ";
	for (auto& node : path)
	{
		cout << "->" << node->data;
	}
	cout << endl;
}