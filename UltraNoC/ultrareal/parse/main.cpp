#include "benchmark.h"
main() {

int c, c1, c2, c3, c4, c5, c6, c7;
benchmark* cb;
cb = new benchmark(1);
//int co1[4];
//co1[0] =0; co1[1] =2; co1[2] =1; co1[3] = 1;
//double k = 10000.4;
//for(int i=0; i<5; i++)
//{
////cout<<"k Value 1st: "<< k<<endl;
//cb->packet_injection_nodeindex(k);
////cout<<"k Value 2nd: "<< k<<endl;
//k=k+double(0.2);
//}
cb->packet_injection_nodeindex(10000);
cb->packet_injection_nodeindex(10000.2);
cb->packet_injection_nodeindex(10000.4);
cb->packet_injection_nodeindex(10000.6);
cb->packet_injection_nodeindex(10000.8);
cb->packet_injection_nodeindex(10001);
cb->packet_injection_nodeindex(10001.2);
cb->packet_injection_nodeindex(10001.4);
cb->packet_injection_nodeindex(10001.6);
//cb->packet_injection_nodeindex(10004.2);
//bool k = cb->packet_injection_response(5);
//bool k1 = cb->packet_injection_response(2);
//cout<< "k for node 5 : "<<k<< "k1 for node 2: "<<k1<<endl;
//cb->packet_injection_nodeindex(10004.6);
//cb->packet_injection_nodeindex(10004.8);
cb->clear_vector();

}

