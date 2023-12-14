#ifndef __GATEWAYINTERFACE_H__
#define __GATEWAYINTERFACE_H__

//---------------------------------------------------------------------------

#define GI_BUFFER_DEPTH 2
#define GLOBAL_TX_INDEX 1
#define LOCAL_TX_INDEX  0
#define RESET_REQ_QUEUE 200
#define ONE_CYCLE 0.5

#include <systemc.h>
#include <vector>
#include <algorithm>
#include "buffer.h"
#include "status.h"
//#include "reservationtable.h"
#include "GlobalTypeDefs.h"
extern unsigned int lambda[];

SC_MODULE(TGatewayInterface)
{
	int 			local_xid; 			// X-Coordinates of current location
	int 			local_yid;			// Y-Cordinates of current location
  // I/O Ports

  sc_in_clk          photonic_clock;      // The input clock for the router
  sc_in<bool>        reset;               // The reset signal for the router

  /** Ports for the bottom electrical layer - START **/
  sc_in<TFlit>       flit_rx;
  sc_in<bool>          req_rx;       
  sc_out<bool>         ack_rx; 
  
  sc_out<TFlit>      flit_tx;
  sc_out<bool>       req_tx; 
  sc_in<bool>        ack_tx; 
  
  sc_out<int>        free_slots;
  sc_in<int>         free_slots_neighbor;
  
  // Neighbor-on-Path related I/O

  sc_out<TNoP_data>       NoP_data_out;
  sc_in<TNoP_data>        NoP_data_in;
  
  /** Ports for the bottom electrical layer - END **/
  
  /** Ports for optical communication  - START **/
  
  //sc_vector<sc_out<sc_uint<2> > > swmr_tx;
  //sc_vector<sc_in<sc_uint<2> > >  swmr_reservation_rx;
  //sc_vector<sc_in<sc_uint<2> > >  swmr_reservation_ack_rx;
  //sc_vector<sc_in<sc_uint<2> > >  swmr_data_ack_rx;
  
  sc_out<TFlit>                   mwmr_data_tx[MAX_STATIC_DIM][MAX_STATIC_DIM];
  sc_in<TFlit>                   mwmr_data_rx;
  //sc_vector<sc_in<TFlit> >        swmr_data_rx;
  
  /** Ports for optical communication  - END **/
  
  bool               current_level_rx;    // Current level for Alternating Bit Protocol (ABP)
  bool               current_level_tx;    // Current level for Alternating Bit Protocol (ABP)

  
  TBuffer            *buffer[GI_BUFFER_DEPTH];         // Buffer for each input channel 


  // Threads and Functions
  void               rxProcess();           // The receiving process
  void               txProcess();           // The Tx Process

  //void               swmr_tx_reserve();      // writes into reservation channel
  //void               swmr_tx_reserve_ack();  // writes into reservation ack channel
  //void               swmr_tx_data();         // Send the data (Non Header flits)
  //void               swmr_tx_data_ack();     // writes into data ack channel
  
  //void               swmr_rx_reserve();     // reads from all other channels except self
  //void               swmr_rx_reserve_ack(); // reads from all other channels except self
  //void               swmr_rx_dt_ack();      // reads from all other channels except self
  //void               swmr_rx_data();    // receives the data from other channels
  
  //// Function
  //void  configure(const int _id, const int _nearest_gateway_id,
  //std::map<int, int>  _gateway_map);
  
  //void  test_ports();
			         
  // Constructor

  //SC_CTOR(TGatewayInterface):swmr_tx("swmr_tx", SWMR_SIZE),
  //swmr_reservation_rx("swmr_reservation_rx", 
  //(TGlobalParams::mesh_dim_x == 3 && TGlobalParams::mesh_dim_y == 3) ? 1 : 3),
  //swmr_reservation_ack_rx("swmr_reservation_ack_rx", 
  //(TGlobalParams::mesh_dim_x == 3 && TGlobalParams::mesh_dim_y == 3) ? 1 : 3),
  //swmr_data_ack_rx("swmr_data_ack_rx", 
  //(TGlobalParams::mesh_dim_x == 3 && TGlobalParams::mesh_dim_y == 3) ? 1 : 3),
  //swmr_data_rx("swmr_data_rx",
  //(TGlobalParams::mesh_dim_x == 3 && TGlobalParams::mesh_dim_y == 3) ? 1 : 3)
  //{
      //// reset the required parameters
	  //current_level_tx = 0;
	  //prev_winner = 0;
	  //safe_to_reserve = 1;
	  //safe_to_send    = 0;
	  
	  //reserve_req_queue.resize(swmr_reservation_rx.size());
	  //std::fill( reserve_req_queue.begin(), reserve_req_queue.end(), RESET_REQ_QUEUE);
	  
	  //data_ack_queue.resize(swmr_reservation_ack_rx.size());
	  //std::fill( reserve_req_queue.begin(), reserve_req_queue.end(), RESET_REQ_QUEUE);
	  
	  
	  //for(int i = 0 ; i < GI_BUFFER_DEPTH; i++)
	  //{	  
	   //buffer[i] = new TBuffer(1);
	  //}
	  
	  //SC_METHOD(test_ports);
	  //sensitive << photonic_clock.pos();

	  SC_METHOD(rxProcess);
      sensitive << reset;
      sensitive << photonic_clock.pos();

      SC_METHOD(txProcess);
      sensitive << reset;
      sensitive << photonic_clock.pos();
      
      //SC_METHOD(swmr_tx_reserve);
      //sensitive << reservation_req;
      
      //SC_METHOD(swmr_tx_reserve_ack);
      //sensitive << reset;
      //sensitive << photonic_clock.pos();
      
      //SC_METHOD(swmr_tx_data);
      //sensitive << reset;
      //sensitive << photonic_clock.pos();
      
      //SC_METHOD(swmr_tx_data_ack);
      //sensitive << data_ack;
      
      //SC_METHOD(swmr_rx_reserve);
      //for( unsigned i= 0; i<swmr_reservation_rx.size(); i++ )
      //sensitive << swmr_reservation_rx[i];

      //SC_METHOD(swmr_rx_reserve_ack);
      //for( unsigned i= 0; i<swmr_reservation_ack_rx.size(); i++ )
	  //sensitive << swmr_reservation_ack_rx[i];   
	  	            
      //SC_METHOD(swmr_rx_dt_ack);
      //for( unsigned i= 0; i<swmr_data_ack_rx.size(); i++ )
	  //sensitive << swmr_data_ack_rx[i];   	
	  
	  //SC_METHOD(swmr_rx_data);
      //for( unsigned i= 0; i<swmr_data_rx.size(); i++ )
	  //sensitive << swmr_data_rx[i]; 	  
	    	            
  //}

  private:
 
  int                           local_id;            // Unique ID
  int                           nearest_gateway_id ; // nearest_gateway_id
  std::map<int, int>            gateway_map;
  std::map<int, int>::iterator  pri_gateway_it;  
   
  // sends the reservation request if the 
  //local buffer is found to have at least a flit
  sc_event_queue      reservation_req;     
  
  // sends reservation ack event to notify the 
  //sender if local buffer has space to be allotted
  sc_event           reservation_ack;    
  
  sc_event           data_ack;
  sc_event           photonic_to_electrical_tx;
  
  vector<int>        reserve_req_queue;
  vector<int>        data_ack_queue;
  sc_uint<2>         req_source_id;
  int                prev_winner;
  bool               safe_to_reserve;
  bool               safe_to_send;
 
};  

#endif

