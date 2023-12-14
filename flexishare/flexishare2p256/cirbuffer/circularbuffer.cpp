#include "circularbuffer.h"

circularbuffer::circularbuffer(int size, int total_nodes)
{
	circularbuffer::node* cbuffer = new node[size];
	priority_node_count = total_nodes;
	current_priority_node_index = 0;
	for(int i=0; i<size; i++)
	{ 
		cbuffer[i].flag = true;
		cbuffer[i].channel = 8 - 1 - (i % 8);
		cbuffer[i].token_priority_node = size-1-current_priority_node_index;
		//cout << "first pass :" << cbuffer[i].channel << endl;
		//cout << "first pass :" << cbuffer[i].token_priority_node << endl;
		
		if(i != size-1 && i != 0)
		{
			cbuffer[i].next = &cbuffer[i+1];
			cbuffer[i].previous = &cbuffer[i-1];
		}
		if(i == size-1)
		{
			cbuffer[i].next = &cbuffer[0];
			cbuffer[i].previous = &cbuffer[size-2];
		}
		if(i == 0)
		{
			cbuffer[i].next = &cbuffer[i+1];
			cbuffer[i].previous = &cbuffer[size-1];
		}
		current_priority_node_index++;
	}
	head = &cbuffer[0];
	head2p = &cbuffer[size/2];
	current_priority_node_index = size;
	
}

void circularbuffer::rotate()
{
	circularbuffer::head = circularbuffer::head->previous;
	circularbuffer::head2p = circularbuffer::head2p->previous;
	if(current_priority_node_index < priority_node_count)
	{
	 circularbuffer::head->token_priority_node = current_priority_node_index;
		
	 current_priority_node_index++;
    }
    else
    {
		current_priority_node_index = 0;
		circularbuffer::head->token_priority_node = current_priority_node_index;
		
	 current_priority_node_index++;
	}	
	circularbuffer::head->flag = true;
}

bool circularbuffer::assign_second_pass(int index, int* pulse2p){
	
	circularbuffer::node* tmp2p;
	bool ret = false;
	tmp2p = circularbuffer::head2p;
	for(int i=0; i< index/8 ; i++)
	{
		if(index/8 == 0)
		{
			tmp2p=tmp2p;
		}
		else
		{
			tmp2p= tmp2p->next;
		}
	}
		if (tmp2p->flag == 1)
	 {
		tmp2p->flag =0;
		ret = true;
		*pulse2p = tmp2p->channel;
	     return ret;
	 } 
	 else
	 {
		 ret = false;
		 *pulse2p = -1;
		 return ret;
	 }
 }

bool circularbuffer::assign_first_pass(int index, int* pulse1p){
	
	circularbuffer::node* tmp1p;
	bool ret = false;
	tmp1p = circularbuffer::head;
	for(int i=0; i< index/8 ; i++)
	{
		if(index/8 == 0)
		{
			tmp1p=tmp1p;
		}
		else
		{
			tmp1p= tmp1p->next;
		}
	}
		if (tmp1p->flag == 1 && index == tmp1p->token_priority_node)
	 {
		tmp1p->flag =0;
		ret = true;
		*pulse1p = tmp1p->channel;
	     return ret;
	 } 
	 else
	 {
		 ret = false;
		 *pulse1p = -1;
		 return ret;
	 }
 }
 
 
	
	
		
	
