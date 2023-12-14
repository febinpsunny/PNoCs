#include <iostream>
#include <cmath>        // std::abs
using namespace std;

class circularbuffer{

private:

	struct node{
		bool flag;
		int tokentype; // provide token number of a cluster 
		int slotid;    // Has current slot number
		int destinationid;
		node* next;
		node* previous;
	};
	node* head;
	node* head2p;
	node* temp;
	int size;
	int clusters;
	int tokensync;
	int current_priority;
	int count;
	int currenttoken;
	int initialisetoken[12];
	

public:

	circularbuffer(int size, int clusters, int tokensync);
	void rotate(int clusters, int current_priority);
	bool assignnew(int indexnew1, int indexnew2);
	bool assign(int index);
	void print(int size);
};

	
