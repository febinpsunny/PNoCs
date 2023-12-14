std::vector<int> benchmark::packet_injection_nodeindex(double current_cycle)
{
	int lineNumber=0;
	string stringitem[3];
	node_id.clear();
	while(1)
	{ 
	istringstream myline(v[count]);
	int word_no = 0;
	while(getline(myline, stringitem[word_no], ' ')) 
	{
		cout << stringitem[word_no] << endl;
		word_no++;	
    }
    const char* temp1 = stringitem[0].c_str();
    double temp = atof(temp1);
    if(temp == current_cycle)
    {
		const char* temp2 = stringitem[1].c_str();
		int temp_nid = atoi(temp2);
		node_id.push_back(temp_nid);
	}
	else
	{
		//break;
	}
	cout << "node id " << node_id[0] << endl;
	count++;
   }
   cout<< "returning node ids for current cycle "<< endl;
	
	return node_id;

}
