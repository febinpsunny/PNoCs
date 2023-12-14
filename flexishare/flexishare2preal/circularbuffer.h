#ifndef __CIRCULARBUFFER_H__
#define __CIRCULARBUFFER_H__

#include <iostream>
#include "GlobalTypeDefs.h"
using namespace std;

class circularbuffer{

private:

	struct node{
		bool flag;
		int channel; // channel number
		int token_priority_node; //  node for which channel is preffered in the first pass   
		node* next;
		node* previous;
	};
	node* head;
	node* head2p;
	node* temp;
	int size;
	int priority_node_count;
	int current_priority_node_index;

public:

	circularbuffer(int size, int total_nodes);
	void rotate();
	bool assign_second_pass(int index, int* pulse2p);
	bool assign_first_pass(int index, int* pulse1p);
};

	
#endif
