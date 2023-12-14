#include "circularbuffer.h"
main() {

int c, c1, c2, c3;
circularbuffer* cb;
cb = new circularbuffer(8, 1);
//cb->print(8);
for(int i = 0; i< 200; i++)
{cb->rotate(1);
cb->print(1);
}
//bool k = cb->assign(63, &c);
//cout << "channel number "<< c << " channel availability "<< k << endl;
//bool k1 = cb->assign(55, &c1);
//cout << "channel number "<< c1 << " channel availability "<< k1 << endl;
//cb->print(8);
//cout << "channel number "<< c << " channel availability "<< k << endl;
//cb->rotate(8);
//cb->rotate(1);

cb->print(8);
//bool k = cb->assign(15, &c);
//cout << "channel number "<< c << " channel availability "<< k << endl;
//bool k1 = cb->assign(23, &c1);
//cout << "channel number "<< c1 << " channel availability "<< k1 << endl;  
//cb->print(8); 
//bool k1 = cb->assign(3, &c1);
//cout << "channel number "<< c1 << " channel availability "<< k1 << endl; 
////cb->rotate();
////cb->rotate();
//bool k2 = cb->assign(62, &c2);
//cout << "channel number "<< c2 << " channel availability "<< k2 << endl; 
//bool k3 = cb->assign(64, &c3);
//cout << "channel number "<< c3 << " channel availability "<< k3 << endl; 

}

