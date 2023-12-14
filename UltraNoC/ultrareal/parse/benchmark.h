#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>        // std::abs
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h> 

using namespace std;

class benchmark{

private:

	int count;
	double current_cycle;
	int benchmark_type;
	ifstream myfile;
	string line;
	std::vector<std::string> v;
	vector<int> node_id;
	int nodeid_request;
	
	

public:

	benchmark(int benchmark_type);
	void packet_injection_nodeindex(double _current_cycle);
	bool packet_injection_response(int nodeid_request);
	void clear_vector();

};

	
