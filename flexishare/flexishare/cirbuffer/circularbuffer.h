#include <iostream>
using namespace std;

class circularbuffer{

private:

	struct node{
		bool flag;
		int channel; // channel number 
		node* next;
		node* previous;
	};
	node* head;
	node* temp;
	int size;

public:

	circularbuffer(int size);
	void rotate();
	bool assign(int index, int* pulse);
};

	
