#include "circularbuffer.h"

circularbuffer::circularbuffer(int size, int waveguide_no)
{
	circularbuffer::node* cbuffer = new node[size];
	count = waveguide_no-1;
	countlw = 7;
	
	for(int i=0; i<size; i++)
	{ 
		cbuffer[i].flag = true;
		cbuffer[i].channel = i;
		cbuffer[i].slotid = i;
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

void circularbuffer::rotate(int waveguide_no)
{
	circularbuffer::head = circularbuffer::head->previous;
	if( waveguide_no < 8)
	{
		if(count >=0)
		{
			circularbuffer::head->channel = count;
			circularbuffer::head->flag = true;
			count--;
			countlw--;
		}
		else
		{
			circularbuffer::head->channel = -1;
			circularbuffer::head->flag = false;
			countlw--;
		}
		if(countlw<0 && count <0)
		{
			count = waveguide_no-1;
			countlw = 7;
		}
	}
	else
	{
		
	if(count >= 0)
	{
		circularbuffer::head->channel = count;
		circularbuffer::head->flag = true;
		count--;
	}
	else
	{
		circularbuffer::head->channel = waveguide_no-1;
		circularbuffer::head->flag = true;
		count = waveguide_no-2;
	}
} 
}

bool circularbuffer::assign(int index, int* pulse){
	circularbuffer::node* tmp;
	bool ret;
	tmp = circularbuffer::head;
	for(int i=0; i< index/8 ; i++)
	{
		if(index/8 == 0)
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
 
 void circularbuffer::print(int size)    // print details of circular buffer
{
	circularbuffer::node* tmp;
	tmp = circularbuffer::head;
	for(int i=0; i< size ; i++)
	{
		cout << "Current slot number:" << tmp->slotid << " Current token :" << tmp->channel << " Current flag :" << tmp->flag << endl;
		tmp = tmp->next;
	} 
}
 
 
 
 
	
	
		
	
