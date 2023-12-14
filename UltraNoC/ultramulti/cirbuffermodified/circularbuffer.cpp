#include "circularbuffer.h"

circularbuffer::circularbuffer(int size, int clusters, int tokensync)
{
	circularbuffer::node* cbuffer = new node[size];
	int basicslot = 3 * clusters;
	int tempsync = tokensync;
	int j =0;
	currenttoken = clusters - 1;
	count = std::abs(11 -(tokensync % 12));
	for(int i=0; i< (3 * clusters) ; i++)
	{ 
		
		if(i%3 == 0)
		{
			initialisetoken[i] = j;
			//cout << "first pass :" << initialisetoken[i] << " count: " << i << endl;
			j++;
			if(j== clusters)
			{
				j=0;
			}
		}
		else
		{
			initialisetoken[i] = -1;
			//cout << "first pass :" << initialisetoken[i] << " count: " << i << endl;
		}
	}
	
	int t=0;
	int tempts = tokensync;
	for(int i=0; i<size; i++)
	{
		cbuffer[i].destinationid = -1;
		if (tempsync < size)
		{
			cbuffer[tempsync].tokentype = initialisetoken[t];
			if(initialisetoken[t] != -1)
			{
				cbuffer[tempsync].flag = true;
			}
			else
			{
				cbuffer[tempsync].flag = false;
			}
			t++;
			tempsync++;
			if(t == (3* clusters))
			{
				t=0;
			}
		}
		else
		{
			tempts --;
			basicslot--;
			cbuffer[tempts].tokentype = initialisetoken[basicslot];
			if(initialisetoken[basicslot] != -1)
			{
				cbuffer[tempts].flag = true;
			}
			else
			{
				cbuffer[tempts].flag = false;
			}
			
			if(basicslot == 0)
			{
				basicslot = 3*clusters;
			}
		}
					
				
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
	head2p = &cbuffer[size/2];
	
}

void circularbuffer::rotate(int clusters, int current_priority)    // function that rotates circular buffer
{
	circularbuffer::head = circularbuffer::head->previous;
	circularbuffer::head2p = circularbuffer::head2p->previous;
	if (count >= 0)
	{
		circularbuffer::head->tokentype = initialisetoken[count];
		//cout << "sample value: "<< initialisetoken[count] << " count : "<< count << endl;
		if (initialisetoken[count] != -1)
		{
			circularbuffer::head->flag = true;
		}
		else
		{
			circularbuffer::head->flag = false;
		}
		count--;
	}
	else
	{
		count = (3* clusters) -1;
		circularbuffer::head->tokentype = initialisetoken[count];
		count--;
	}
}

bool circularbuffer::assignnew(int indexnew1, int indexnew2)
{
	circularbuffer::node* tmp1;
	circularbuffer::node* tmp2p1;
	bool ret1 = false;
	tmp1 = circularbuffer::head;
	tmp2p1 = circularbuffer::head2p;
	int clusternumber = indexnew1/16;
	for(int i=0; i< indexnew1/2 ; i++)
	{
		if(indexnew1/2 == 0)
		{
			tmp1=tmp1;
			tmp2p1=tmp2p1;
		}
		else
		{
			tmp1 = tmp1->next;
			tmp2p1 = tmp2p1->next;
		}
	} 
	if (tmp1->flag == 1 && tmp1->tokentype == clusternumber)
	{
		tmp1->flag =0;
		tmp1->tokentype = -1;
		ret1 = true;
	 }
	 else
	 {
		 ret1 = false;
	 }
	 return ret1; 
 }

bool circularbuffer::assign(int index){
	circularbuffer::node* tmp;
	circularbuffer::node* tmp2p;
	bool ret = false;
	tmp = circularbuffer::head;
	tmp2p = circularbuffer::head2p;
	int clusternumber = index/16;
	for(int i=0; i< index/8 ; i++)
	{
		if(index/8 == 0)
		{
			tmp=tmp;
			tmp2p=tmp2p;
		}
		else
		{
			tmp = tmp->next;
			tmp2p = tmp2p->next;
		}
	} 
	if (tmp->flag == 1 && tmp->tokentype == clusternumber)
	{
		tmp->flag =0;
		tmp->tokentype = -1;
		ret = true;
	 } 
	 else 
	 {
		ret = false; 
	 }
	 return ret; 
 }
 
 void circularbuffer::print(int size)    // print details of circular buffer
{
	circularbuffer::node* tmp;
	tmp = circularbuffer::head;
	for(int i=0; i< size ; i++)
	{
		cout << "Current slot number:" << tmp->slotid << " Current token :" << tmp->tokentype << " Current flag :" << tmp->flag << endl;
		tmp = tmp->next;
	} 
}
 
 
	
	
		
	
