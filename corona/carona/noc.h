#ifndef __NOC_H__
#define __NOC_H__

//---------------------------------------------------------------------------

#include <systemc.h>
#include "gitile.h"
#include "gatewayinterface.h"
#include <vector>
#include <map>
#include <algorithm>

SC_MODULE(TNoC)
{

  // I/O Ports

  sc_in_clk        clock;        // The input clock for the NoC
  sc_in<bool>      reset;        // The reset signal for the NoC

  // strutture per NoP !
  sc_mutex<TFlit>     cross_bar[MAX_STATIC_DIM][MAX_STATIC_DIM];
  
  // Matrix of tiles

  TGITile*            git[MAX_STATIC_DIM][MAX_STATIC_DIM];
  
  // Constructor

  SC_CTOR(TNoC)
  {

    // Build the Mesh
    buildCrossbar();
  }
  

  private:
  void buildCrossbar();
};

//---------------------------------------------------------------------------

#endif

