#include "noc.h"

//---------------------------------------------------------------------------


void TNoC::buildCrossbar()
{
	// Arbiter pin assignments
    garbiter   = new TGlobalarbiter("Globalarbiter");
    // Map clock and reset
	  garbiter->clock(clock);
	  garbiter->photonic_clock(photonic_clock);
	  garbiter->reset(reset);
  // Create the grid as a matrix of tiles
  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
    {
      for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
	{
	  // Create the single Tile with a proper name
	  char tile_name[20];
	  sprintf(tile_name, "Tile[%02d][%02d]", i, j);
	  git[i][j] = new TGITile(tile_name);

	  // Tell to the PE its coordinates
	  git[i][j]->pe->local_id = j * TGlobalParams::mesh_dim_x + i;
	  //cout << "pe local id : " <<i<<j<< git[i][j]->pe->local_id << endl;
      git[i][j]->gwi->local_id_new = j * TGlobalParams::mesh_dim_x + i;
	  // Map clock and reset
	  git[i][j]->clock(clock);
	  git[i][j]->photonic_clock(photonic_clock);
	  git[i][j]->reset(reset);
	  
	  // Map Arbiter signals
	  git[i][j]->req_tx_arbiter(req_tx_arbiter_signal[i][j]);
	  git[i][j]->ack_tx_arbiter(ack_tx_arbiter_signal[i][j]);
	  git[i][j]->mwmr_channel_no(mwmr_channel_no_signal[i][j]);
	  git[i][j]->ack_txc_arbiter(ack_txc_arbiter_signal[i][j]);
	  	
	  // Map Tx signals and Rx Signals
	   for(int k=0; k<((TGlobalParams::mesh_dim_x * TGlobalParams::mesh_dim_y)/2); k++) 
		{ 
			git[i][j]->flit_tx[k](cross_bar[k]);  // channel assignment for sending data 
			//cout << "Tile" <<i<<j<< "Output connect to channel"<< k << endl;
			git[i][j]->flit_rx[k](cross_bar[k]); // channel assignment for receveing data 
			//cout << "Tile" <<i<<j<< "Input connect to channel"<< k << endl;
		}

	  // connect arbiter with tiles
	  
	   garbiter->req_tx_arbiter[i][j](req_tx_arbiter_signal[i][j]);
	   garbiter->ack_tx_arbiter[i][j](ack_tx_arbiter_signal[i][j]);
	   garbiter->mwmr_channel_no[i][j](mwmr_channel_no_signal[i][j]);
	   garbiter->ack_txc_arbiter[i][j](ack_txc_arbiter_signal[i][j]);

	}
    }

}

TGITile* TNoC::searchNode(const int id) const
{
  for (int i=0; i<TGlobalParams::mesh_dim_x; i++)
    for (int j=0; j<TGlobalParams::mesh_dim_y; j++)
      if (git[i][j]->gwi->local_id == id)
	return git[i][j];

  return false;
}

//---------------------------------------------------------------------------

