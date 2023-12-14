#ifndef __TGITILE_H__
#define __TGITILE_H__

//---------------------------------------------------------------------------

#include <systemc.h>
#include "processingelement.h"
#include "hub.h"
#include "gatewayinterface.h"
#include "GlobalTypeDefs.h"

SC_MODULE(TGITile)
{

  // I/O Ports

  sc_in_clk           clock;        // The input clock for the tile
  sc_in_clk          photonic_clock;
  sc_in<bool>         reset;        // The reset signal for the tile

  sc_in<TFlit>        flit_rx[DEFAULT_MWMR_WAVEGUIDES][4];   // The input channels
 
  sc_out<TFlit>       flit_tx[DEFAULT_MWMR_WAVEGUIDES][4];   // The output channels
  /** Ports for communication with Arbiter  - START **/
  
   sc_out<TFlit>		     req_tx_arbiter_flit;   // req for arbiter 
  sc_out<bool>           req_tx_arbiter_hf;  //req for arbiter to receive head flit
  sc_in<bool>            ack_tx_arbiter_hf;  // ack of arbiter for receipt of head flit      
  
  sc_in<bool>            req_rx_arbiter_ch;//ack_tx_arbiter;    // ack from arbiter to send data
  sc_in<int>             mwmr_channel_no; // MWMR channel number from arbiter to send data
  sc_out<bool>            ack_rx_arbiter_ch;  // ack of arbiter for receipt of channel number
    
  sc_out<bool>			 req_txc_arbiter;
  sc_out<bool>			 ack_txc_arbiter;    // ack to arbiter after sending data
  sc_in<bool>			 ack_txc_gwi;    // ack from arbiter after receving data
  
  /** Ports for communication with Arbiter  - END **/
  
  
  // NoP signals inside tile
  sc_signal<TFlit>    flit_Nop_temp;   // The duplicated output channels
  
  // Signals for Processing element to Hub and hub to GWI

  sc_signal<TFlit>    flit_rx_local[DIRECTIONS+1];   // The input channels
  sc_signal<bool>     req_rx_local[DIRECTIONS+1];    // The requests associated with the input channels
  sc_signal<bool>     ack_rx_local[DIRECTIONS+1];    // The outgoing ack signals associated with the input channels

  sc_signal<TFlit>    flit_tx_local[DIRECTIONS+1];   // The output channels
  sc_signal<bool>     req_tx_local[DIRECTIONS+1];    // The requests associated with the output channels
  sc_signal<bool>     ack_tx_local[DIRECTIONS+1];    // The outgoing ack signals associated with the output channels
  
  sc_signal<int>     free_slots_local[DIRECTIONS+1];
  sc_signal<int>     free_slots_neighbor_local[DIRECTIONS+1];

  // Instances
  TGatewayInterface*   gwi;				// Gateway interface
  THub*                  h;             // Hub instance
  TProcessingElement* pe[4];              // Processing Element instance
  TStats*               stats;                           // Statistics

  // BENCHMARK INTIALIZATION
   benchmark              &b_mark;

  // Constructor
  TGITile(sc_module_name name, benchmark &_b_mark):
  b_mark(_b_mark)
  //mwmr_data_rx(sc_gen_unique_name("flit_tx"))
  {    
     stats = new TStats();     
    // GatewayInterface pin assignments
    gwi   = new TGatewayInterface("GatewayInterface", *stats);
    
    gwi->clock(clock);
    gwi->photonic_clock(photonic_clock);
    gwi->reset(reset);
	// GatewayInterface data pin assignment with tile
	/** Pin assignment for communication with Arbiter  - START **/
	gwi->req_tx_arbiter_flit(req_tx_arbiter_flit);
	gwi->req_tx_arbiter_hf(req_tx_arbiter_hf);
	gwi->ack_tx_arbiter_hf(ack_tx_arbiter_hf);
	gwi->req_rx_arbiter_ch(req_rx_arbiter_ch);
	gwi->mwmr_channel_no(mwmr_channel_no);
	gwi-> ack_rx_arbiter_ch( ack_rx_arbiter_ch);
	gwi->req_txc_arbiter(req_txc_arbiter);
	gwi->ack_txc_arbiter(ack_txc_arbiter);
	gwi->ack_txc_gwi(ack_txc_gwi);
	/** Pin assignment for communication with Arbiter  - END **/
    for(int i=0; i<(TGlobalParams::mwmr_waveguides); i++)
    {
		for(int j=0; j<4; j++)
		{  
		  gwi->mwmr_data_rx[i][j](flit_rx[i][j]); // Extension of input channels to tile
		  gwi->mwmr_data_tx[i][j](flit_tx[i][j]); // Extension of output channels to tile
	  }
    }
    // GatewayInterface pin assignment with hub
    gwi->flit_rx(flit_rx_local[DIRECTIONS]);
    gwi->req_rx(req_rx_local[DIRECTIONS]);
    gwi->ack_rx(ack_rx_local[DIRECTIONS]);

    gwi->flit_tx(flit_tx_local[DIRECTIONS]);
    gwi->req_tx(req_tx_local[DIRECTIONS]);
    gwi->ack_tx(ack_tx_local[DIRECTIONS]);

    gwi->free_slots(free_slots_local[DIRECTIONS]);
    gwi->free_slots_neighbor(free_slots_neighbor_local[DIRECTIONS]);

    // Processing Element pin assignments to form a concentrator having 4 PE's
    for(int i=0; i<4; i++)
    {
	  char processing_element[20];
	  sprintf(processing_element, "ProcessingElement[%02d]", i);
    pe[i] = new TProcessingElement(processing_element, b_mark, *stats);
    pe[i]->clock(clock);
    pe[i]->reset(reset);

    pe[i]->flit_rx(flit_rx_local[i]);
    pe[i]->req_rx(req_rx_local[i]);
    pe[i]->ack_rx(ack_rx_local[i]);

    pe[i]->flit_tx(flit_tx_local[i]);
    pe[i]->req_tx(req_tx_local[i]);
    pe[i]->ack_tx(ack_tx_local[i]);

    pe[i]->free_slots(free_slots_local[i]);
    pe[i]->free_slots_neighbor(free_slots_neighbor_local[i]);
	}
    
     // Hub pin assignments
    h = new THub("Hub");
    h->clock(clock);
    h->reset(reset);
	// Hub pin assignments with pe and GWI
	for(int i=0; i<DIRECTIONS+1; i++)
    {
    h->flit_tx[i](flit_rx_local[i]);
    h->req_tx[i](req_rx_local[i]);
    h->ack_tx[i](ack_rx_local[i]);

    h->flit_rx[i](flit_tx_local[i]);
    h->req_rx[i](req_tx_local[i]);
    h->ack_rx[i](ack_tx_local[i]);

    h->free_slots[i](free_slots_neighbor_local[i]);
    h->free_slots_neighbor[i](free_slots_local[i]);
	}

  }

};

#endif
