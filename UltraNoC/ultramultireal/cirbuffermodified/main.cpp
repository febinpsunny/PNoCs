#include "circularbuffer.h"
main() {

int c, c1, c2, c3, c4, c5, c6, c7;
circularbuffer* cb[16];
//for(int i=0; i<4; i++)
for(int i=0; i< 16; i++)
{
	int k = i%2;
	cb[i] = new circularbuffer(16, 4, k);
	cb[i]->print(16);
	cb[i]->rotate(4,1);
	cb[i]->print(16);
}

//cb->rotate(4,1);
//for(int i=0; i<11; i++)
//cb->rotate(4,1);
//bool k1 = cb->assign(5);
//cout <<  "node :" << 5 << " channel availability "<< k1 << endl;
//bool k2 = cb->assign(17);
//cout <<  "node :" << 17 << " channel availability "<< k2 << endl;
//cb->print(16);
//cb->rotate();
//bool k = cb->assignnew(2, 3, &c, &c1);
//cout << "channel numberfor indexone "<< c <<"channel number index2 "<< c1 << " channel availability "<< k << endl;
//cb->rotate();
//bool k2 = cb->assignnew(2, 3, &c4, &c5);
//cout << "channel numberfor indexone "<< c4 <<"channel number index2 "<< c5 << " channel availability "<< k2 << endl;
//cb->rotate();
//bool k3 = cb->assignnew(2, 3, &c6, &c7);
//cout << "channel numberfor indexone "<< c6 <<"channel number index2 "<< c7 << " channel availability "<< k3 << endl;
//bool k3 = cb->assign(63, &c2, &c3);
//cout << "channel number 1p: "<< c2 << "channel number 2p: "<< c3<< " channel availability "<< k3 << endl; 

}

