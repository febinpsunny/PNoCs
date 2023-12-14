#include "noc.h"

//---------------------------------------------------------------------------


void TNoC::buildCrossbar()
{

  // Create the grid as a matrix of tiles
  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
    {
      for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
	{
	  // Create the single Tile with a proper name
	  char tile_name[20];
	  sprintf(tile_name, "Tile[%02d][%02d]", i, j);
	  git[i][j] = new TGITile(tile_name);

	  // Tell to the router its coordinates
	

	  // Tell to the PE its coordinates
	  git[i][j]->pe->local_id = j * TGlobalParams::mesh_dim_x + i;
          git[i][j]->pe->never_transmit = (gttable.occurrencesAsSource(git[i][j]->pe->local_id) == 0);

	  // Map clock and reset
	  git[i][j]->clock(clock);
	  git[i][j]->reset(reset);

	  // Map Rx signals
	  git[i][j]->flit_rx(cross_bar[i][j]);
	  
	  // Map Tx signals
	   for(int k=0; k<(TGlobalParams::mesh_dim_x); k++) 
		{ 
			for(int l=0; l<(TGlobalParams::mesh_dim_y); l++) 
		{ 
			if(k == i && l == j)
			{ // Tell to the GWI its coordinates
				git[i][j]->gwi->local_xid = i;
				git[i][j]->gwi->local_yid = j;
			} else
			git[i][j]->flit_tx[k][l](cross_bar[k][l]);
			
		}
		}

	  // Map buffer level signals (analogy with req_tx/rx port mapping)
	  
	  // NoP 

	}
    }

}

//---------------------------------------------------------------------------

