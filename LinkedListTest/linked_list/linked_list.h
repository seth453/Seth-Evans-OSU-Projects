/******************************************************
** Program: linked_list.h
** Author: Seth Evans
** Date: 6/10/2023
** Description: Home of the singly-linked list class provides the functionality
** Input: Integers
** Output: Resulting integers
******************************************************/


#ifndef LINKED_LIST
#define LINKED_LIST

#include "node.h"
#include <iostream>

using namespace std;

class Linked_List {
private:
	int length; // the number of nodes contained in the list
	Node* head; // a pointer to the first node in the list
	// anything else you need...
public:
/*********************************************************************
** Function: Linked_List()
** Description: Recursive call to class, refreshes list
** Parameters: none
** Pre-Conditions: int
** Post-Conditions: int
*********************************************************************/
	Linked_List() { 
		length = 0; 
		head = NULL;
	}

	// note: there is no set_length(unsigned int) (the reasoning should be intuitive)
	/*********************************************************************
** Function: get_length()
** Description: Accesses private member variable length
** Parameters: None
** Pre-Conditions: List
** Post-Conditions: Size of nodes in list
*********************************************************************/
	int get_length() { 
		return length;
	}

/*********************************************************************
** Function: print()
** Description: prints integer nodes within the list
** Parameters: None
** Pre-Conditions: List
** Post-Conditions: Value of nodes in list
*********************************************************************/
	void print() { 
		Node* current = head; 
		while (current != NULL) { 
			cout << current->val << " "; 
			current = current->next;
		} 
		cout << endl;
	}
	/*********************************************************************
** Function: clear()
** Description: delete the entire list (remove all nodes and reset length to 0
** Parameters: None
** Pre-Conditions: List
** Post-Conditions: Empty list
*********************************************************************/
	void clear() { 
		while (head != NULL) { 
			Node* temp = head; 
			head = head->next; 
			delete temp;
		}
		length = 0;
	}
		/*********************************************************************
** Function: push_front()
** Description: insert a new value at the front of the list 
** Parameters: a node address
** Pre-Conditions: List
** Post-Conditions: Updated list re-arranged
*********************************************************************/
	void push_front(int value) { 
		Node* new_node = new Node(value); 
		new_node->next = head; 
		head = new_node; 
		length++;
	}
	/*********************************************************************
** Function: push_back()
** Description:  insert a new value at the back of the list 
** Parameters: a node address
** Pre-Conditions: List
** Post-Conditions: Updated list re-arranged
*********************************************************************/
	void push_back(int value) { 
		Node* new_node = new Node(value); 
		if(head == NULL) { 
			head = new_node;
		} 
		else { 
			Node* current = head; 
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = new_node;
		}
		length++;
	} 

	/*********************************************************************
** Function: insert()
** Description:  insert a new value in the list at the specified index 
** Parameters: a node value, a node location
** Pre-Conditions: List
** Post-Conditions: Updated list with new node(s)
*********************************************************************/
	void insert(int val, int index) { 
		if (index < 0 || index > length) { 
			return;
		}
		if (index == 0) { 
			push_front(val); 
		} 
		else if (index == length) { 
			push_back(val);
		} 
		else { 
			Node* new_node = new Node(val); 
			Node* current = head; 
			for (int i = 0; i < index - 1; ++i)
			{
				current = current->next;
			}
			new_node->next = current->next; 
			current->next = new_node; 
			length++;
		}
	} 

/*********************************************************************
** Function: merge()
** Description:  helper function to assit in merge process 
** Parameters: head node location, leftmost node, right node
** Pre-Conditions: Seperated list
** Post-Conditions: Combined list
*********************************************************************/
	void merge(Node** head_ref, Node* left, Node* right) { 
		Node* merged = NULL; 
		if (left == NULL) { 
			*head_ref = right; 
			return;
		}
		if (right == NULL) { 
			*head_ref = left; 
			return;
		} 
		if (left->val <= right->val) { 
			merged = left; 
			merged->next = NULL; 
			merge(&(merged->next), left->next, right);
		} 
		else { 
			merged = right; 
			merged->next = NULL; 
			merge(&(merged->next), left, left->next);
		} 
		*head_ref = merged;
	}
/*********************************************************************
** Function: merge_sort_up()
** Description: supposed to sort nodes ascending order 
** Parameters: head node location
** Pre-Conditions: Combined list
** Post-Conditions: Ordered list
*********************************************************************/
	void merge_sort_up(Node** head_ref) { 
		Node* head = *head_ref; 
		Node* left; 
		Node* right; 
		if (head == NULL || head->next == NULL) { 
			return;
		}
		split(head, &left, &right); 
		merge(head_ref, left, right);
	}
/*********************************************************************
** Function: merge_sort_down()
** Description: supposed to sort nodes descending order 
** Parameters: back node location
** Pre-Conditions: Combined list
** Post-Conditions: Ordered list
*********************************************************************/
	void merge_sort_down(Node** back_ref) { 
		Node* head = *back_ref; 
		Node* left; 
		Node* right; 
		if (head == NULL || head->next == NULL) { 
			return;
		}
		split(head, &left, &right);  
		merge(back_ref, left, right);
	}
/*********************************************************************
** Function: split()
** Description: supposed to split list in half 
** Parameters: Node source, front node, back node
** Pre-Conditions: whole list
** Post-Conditions: split
*********************************************************************/
	void split(Node* source, Node** front_ref, Node** back_ref) { 
		Node* slow = source->next; 
		Node* fast = source; 
		while(fast != NULL) { 
			fast = fast->next;
			if (fast != NULL) { 
				slow = slow->next; 
				fast = fast->next;
			}
		}
		*front_ref = source; 
		*back_ref = slow->next; 
		slow->next = NULL;
	}
	/*********************************************************************
** Function: sort_ascending()
** Description: sort the nodes in ascending order using recursive Merge Sort algorithm
** Parameters: None
** Pre-Conditions: Calls helper function passing head node
** Post-Conditions: Ordered list
*********************************************************************/
	void sort_ascending() {
		merge_sort_up(&head);
	}
/*********************************************************************
** Function: sort_descending()
** Description: sort the nodes in descending order using recursive Merge Sort algorithm
** Parameters: None
** Pre-Conditions: Calls helper function passing head node
** Post-Conditions: Ordered list
*********************************************************************/
	void sort_descending() { 
		merge_sort_down(&head);
		}
	
};


#endif
