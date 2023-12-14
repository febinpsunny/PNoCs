#include "circularbuffer.h"
main() {

int c, c1, c2, c3, c4, c5, c6, c7;
circularbuffer* cb[16];
int co1[16][4];
int co[4];
co[0] =1; co[1] =1; co[2] =1; co[3] = 1;
//cb = new circularbuffer(16, 4, 5, co);
//int co1[4];
//co1[0] =0; co1[1] =2; co1[2] =1; co1[3] = 1;
//cb->change_token_priority(4, 5, co1);
for(int i=0; i< 16; i++)
{
cout<< "waveguide : "<< i <<endl;
int k= i%12;
cb[i] = new circularbuffer(16, 4, k, co);
cb[i]->print(16);

}

//for(int j=0; j< 8; j++)
{
for(int i=0; i< 16; i++)
{
cout<< "waveguide in rotation : "<< i << "iteration"<< 0 <<endl;
cb[i]->transferpriority(64, 16, 4, &co1[i][0]);
cb[i]->print(16);
//cb[i]->rotate(4,co);
//cb[i]->print(16);

}
}
//cb->rotate(4,co);
//int co1[4];
//co1[0] =4; co1[1] =2; co1[2] =3; co1[3] = 1;
//cb->change_token_priority(4, co1);

//for(int i=0; i< 4; i++)
//{
	////cb->rotate(4,co1);
	////cb[w]->transferpriority(64, 16, 4, &co[w][0]);
	////cb->print(16);
	////for(int j=0; j<4; j++)
	////{
		////cout<<"Waveguide Number: "<< w <<"cluster no in main: " << j << " count of tokens: "<< co[w][j]<< endl;;
	////} 
//}
//for(int i=0; i< 4; i++)
//{
	//for(int j=0; j< 4; j++)
	//{
		//co[i][j]=0;
	//}
//}
//for(int w=0; w<4; w++)
//{
	//int k = w%2;
	//cb[w] = new circularbuffer(16, 4, k);
	//for(int i=0; i< 4; i++)
	//{
		//cb[w]->rotate(4,1);
		//cb[w]->transferpriority(64, 16, 4, &co[w][0]);
		//cb[w]->print(16);
		//for(int j=0; j<4; j++)
		//{
			//cout<<"Waveguide Number: "<< w <<"cluster no in main: " << j << " count of tokens: "<< co[w][j]<< endl;;
		//} 
	//}
//}

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

