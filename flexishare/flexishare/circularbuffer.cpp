#include "circularbuffer.h"

circularbuffer::circularbuffer(int size)
{
	circularbuffer::node* cbuffer = new node[size];
	
	for(int i=0; i<size; i++)
	{ 
		cbuffer[i].flag = true;
		cbuffer[i].channel = i;
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
	}
	head = &cbuffer[0];
	
}

void circularbuffer::rotate()
{
	circularbuffer::head = circularbuffer::head->previous;
	circularbuffer::head->flag = true;
}

bool circularbuffer::assign(int index, int* pulse){
	circularbuffer::node* tmp;
	bool ret;
	tmp = circularbuffer::head;
	for(int i=0; i< index/2 ; i++)
	{
		if(index/2 == 0)
		{
			tmp=tmp;
		}
		else
		{
			tmp = tmp->next;
		}
	} 
	if (tmp->flag == 1)
	{
		tmp->flag =0;
		ret = true;
		*pulse = tmp->channel;
	     return ret;
	 } 
	 else
	 {
		 ret = false;
		 *pulse = tmp->channel;
		 return ret;
	 }
 }
 
 
	
	
		
	
