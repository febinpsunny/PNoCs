#include <iostream>
using namespace std;

class circularbuffer{

private:

	struct node{
		bool flag;
		int channel; // channel number 
		int slotid;
		node* next;
		node* previous;
	};
	node* head;
	node* temp;
	int size;
	int waveguide_no;
	int count;
	int countlw;
	

public:

	circularbuffer(int size , int waveguide_no);
	void rotate(int waveguide_no);
	bool assign(int index, int* pulse);
	void print(int size);
};

	
