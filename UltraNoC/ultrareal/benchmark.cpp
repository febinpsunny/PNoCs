#include "benchmark.h"

void benchmark::packet_injection_nodeindex()
{
	if(reset.read())
  {
    
  }
  else
  {
	  int lineNumber=v.size();
	  if((lineNumber-2) > count)
	  {
	
	double _current_cycle= sc_time_stamp().to_double()/1000;
	double cc= _current_cycle;
	//cout<< "current time: "<< cc << endl;
	std::string stringitem[3];
	int i=0;
	node_id.clear();
	while(i<16)
	{ 
	std:: string str = v[count];
	std::istringstream myline(str);
	int word_no = 0;
	while(std::getline(myline, str, ' ')) 
	{
		stringitem[word_no] = str;
		//cout << stringitem[word_no] << endl;
		word_no++;
		//cout<< "word_no: "<< word_no<<endl;	
    }
    //const char* temp1 = stringitem[0].c_str();
    //cout<< "temp1 value: "<< temp1<< endl;
    double temp =  double(atof(stringitem[0].c_str()));
    //cout<< "temp value: "<< temp<<" cycle time : "<< cc << " i: "<< i << endl;
    if(temp == cc)
    {
		const char* temp2 = stringitem[1].c_str();
		int temp_nid = atoi(temp2);
		for(int k =0; k<4; k++ )
		{
			node_id.push_back(temp_nid + k*16);
		}
		count++;
		i++;
		//cout << "node id " << node_id.back()<<" " <<node_id.size()  << "count: "<< count << endl;
				
	}
	else
	{
		i=17;
	}
	//cout<< "i value: "<< i<< endl;
	//cout << "node id " << node_id.back()<<" " <<node_id.size()  << endl;
	}
	//cout << "one iteration compelete proceeding to next one"<<endl;
	//int j=0;
	////for( j=0; j< node_id.size(); j++ )
	//{
		////cout << "node id " << node_id.back() << endl;
	//}
	////cout<< "after returning one set of ids and Nodesize:" << node_id.size() << endl;
}
}

}

bool benchmark::packet_injection_response(int nodeid_request)
{
	if(std::find(node_id.begin(), node_id.end(), nodeid_request) != node_id.end())
	{
		//cout<< "query reponse 1"<<endl;
		return 1;
	}
	else
	{
		//cout<< "query reponse 0"<<endl;
		return 0;
	}
}

void benchmark::clear_vector()
{
	v.clear();
	
} 



 
	
	
		
	
