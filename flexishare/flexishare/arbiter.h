#ifndef __GLOBAL_ARBITER_H__
#define __GLOBAL_ARBITER_H__

//---------------------------------------------------------------------------

#include <cassert>
#include <queue>
#include "GlobalTypeDefs.h"
#include "circularbuffer.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector


using namespace std;

//---------------------------------------------------------------------------

SC_MODULE(TGlobalarbiter)
{

  // I/O Ports
  sc_in_clk          clock;      // The input clock for the arbiter
  sc_in_clk          photonic_clock;
  sc_in<bool>        reset;      // The reset signal for the arbiter

  /** Ports for communication with Arbiter  - START **/
  
  sc_in<TFlit>      req_tx_arbiter[DEFAULT_MESH_DIM_X][DEFAULT_MESH_DIM_Y];
  sc_out<bool>      ack_tx_arbiter[DEFAULT_MESH_DIM_X][DEFAULT_MESH_DIM_Y]; // ack from arbiter to send data
  sc_out<int>       mwmr_channel_no[DEFAULT_MESH_DIM_X][DEFAULT_MESH_DIM_Y]; // cordinates of channel from arbiter to send data
  sc_in<bool>       ack_txc_arbiter[DEFAULT_MESH_DIM_X][DEFAULT_MESH_DIM_Y]; // ack to arbiter after sending data
  
  /** Ports for communication with Arbiter  - END **/
  
  circularbuffer* cb;          //initialization of circularqueue 
  void proc_arbiter_req_rx();
  void proc_arbiter_index_tx();
  void proc_arbiter_ack_tx();
   SC_CTOR(TGlobalarbiter):
   clock(sc_gen_unique_name("reset"))
  {
    cb = new circularbuffer(32);
    SC_METHOD(proc_arbiter_req_rx);
    sensitive << reset;
    for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  {
				  sensitive << req_tx_arbiter[i][j];
			  }
		  } 
    SC_METHOD(proc_arbiter_index_tx);
    sensitive << reset;
    sensitive << photonic_clock.pos();
    SC_METHOD(proc_arbiter_ack_tx);
    sensitive << reset;
    sensitive << clock.pos();
   }
   
  private:
  bool 				node_packet_status[DEFAULT_MESH_DIM_X][DEFAULT_MESH_DIM_Y];
  
 };

#endif
