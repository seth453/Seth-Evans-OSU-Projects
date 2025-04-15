/******************************************************
** Program: node.h
** Author: Seth Evans
** Date: 6/10/2023
** Description: Home of the node class that stores into linked list, connecting each node.
** Input: Integers
** Output: Resulting integers
******************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
public:
	int val; // the value that this node stores
	Node *next; // a pointer to the next node in the list
/*********************************************************************
** Function: Node
** Description: Connects nodes through memory.
** Parameters: Value
** Pre-Conditions: Any data type to val
** Post-Conditions: Link result
*********************************************************************/	
	Node(int value) { 
		val = value; 
		next = NULL;
	}
	
};

#endif