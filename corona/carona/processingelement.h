#ifndef __TPROCESSING_ELEMENT_H__
#define __TPROCESSING_ELEMENT_H__

//---------------------------------------------------------------------------

#include <queue>
#include <systemc.h>
#include <vector>
#include <algorithm>
#include "GlobalTypeDefs.h"
using namespace std;

SC_MODULE(TProcessingElement)
{

  // I/O Ports

  sc_in_clk            clock;        // The input clock for the PE
  sc_in<bool>          reset;        // The reset signal for the PE

  sc_in<TFlit>         flit_rx;      // The input channel
  sc_in<bool>          req_rx;       // The request associated with the input channel
  sc_out<bool>         ack_rx;       // The outgoing ack signal associated with the input channel

  sc_out<TFlit>        flit_tx;      // The output channel
  sc_out<bool>         req_tx;       // The request associated with the output channel
  sc_in<bool>          ack_tx;       // The outgoing ack signal associated with the output channel

  sc_out<int>         free_slots;
  sc_in<int>          free_slots_neighbor;

  // Registers

  int                  local_id;                     // Unique identification number
  bool                 current_level_rx;       // Current level for Alternating Bit Protocol (ABP)
  bool                 current_level_tx;       // Current level for Alternating Bit Protocol (ABP)
  queue<TPacket>       packet_queue;           // Local queue of packets
  bool                 transmittedAtPreviousCycle;  // Used for distributions with memory

  // Functions

  void                 rxProcess();                       // The receiving process
  void                 txProcess();                       // The transmitting process
  bool                 canShot(TPacket& packet);          // True when the packet must be shot
  TFlit                nextFlit();                        // Take the next flit of the current packet
  TPacket              trafficRandom();                   // Random destination distribution
  TPacket              trafficTranspose1();               // Transpose 1 destination distribution
  TPacket              trafficTranspose2();               // Transpose 2 destination distribution
  TPacket              trafficBitReversal();              // Bit-reversal destination distribution
  TPacket              trafficShuffle();                  // Shuffle destination distribution
  TPacket              trafficButterfly();                // Butterfly destination distribution


  //TGlobalTrafficTable* traffic_table;                     // Reference to the Global traffic Table
  bool                 never_transmit;                    // true if the PE does not transmit any packet 
                                                          //  (valid only for the table based traffic)

  void                 fixRanges(const TCoord, TCoord&);  // Fix the ranges of the destination
  int                  randInt(int min, int max);         // Extracts a random integer number between min and max
  int                  getRandomSize();                   // Returns a random size in flits for the packet
  void                 setBit(int &x, int w, int v);
  int                  getBit(int x, int w);
  double               log2ceil(double x);
  
  // Constructor

  SC_CTOR(TProcessingElement)
  {
	  
	local_id_photonic.push_back(0);
	local_id_photonic.push_back(1);
	local_id_photonic.push_back(8);
	local_id_photonic.push_back(6);
	local_id_photonic.push_back(7);
	local_id_photonic.push_back(15);
	local_id_photonic.push_back(48);
	local_id_photonic.push_back(56);
	local_id_photonic.push_back(57);
	local_id_photonic.push_back(55);
	local_id_photonic.push_back(62);
	local_id_photonic.push_back(63);
	
	
    SC_METHOD(rxProcess);
    sensitive << reset;
    sensitive << clock.pos();

    SC_METHOD(txProcess);
    sensitive << reset;
    sensitive << clock.pos();
  }    
  
  private:
  
  vector<int>           local_id_photonic;
  int                   electrical_transfer;
  int                   photonic_transfer;
  vector<int>::iterator flight_test;
  vector<int>::iterator pilot_test;
  vector<int>::iterator recieve_flit_test;
  vector<int>::iterator send_flit_test;
  int                   hops_to_destination;

};

#endif
