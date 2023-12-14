#include "GlobalTypeDefs.h"
#include "processingelement.h"
#include "arbiter.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

//---------------------------------------------------------------------------
void TGlobalarbiter::proc_arbiter_req_rx() // this section generates binary queue
{
	 if(reset.read())
  {
	  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  {
				  node_packet_status[i][j] = 0;
			  }
		  }
	 
  }
  
  else
  {
	  if(!reset.read())
	  {
		  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  {
				  if( req_tx_arbiter[i][j]->event())
				  {
				  if(ack_txc_arbiter[i][j].read() == 1)
				  { 
				  
				  TFlit received_flit = req_tx_arbiter[i][j].read(); // Receving Head Flit from a tile 
				    if(TGlobalParams::verbose_mode > VERBOSE_OFF)
				    {
						cout<< sc_time_stamp().to_double()/1000  << "Source_Id --> " <<  received_flit.src_id <<" Head_Destination_Id --> " <<  received_flit.dst_id << endl;
						}
						if(received_flit.flit_type == FLIT_TYPE_HEAD)
						{
							node_packet_status[i][j] = 1;
						}
						else
						{
							node_packet_status[i][j] = 0;
						}
						if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< sc_time_stamp().to_double()/1000  << "cooridate [" <<  i <<"] [" << j <<"]"<<"Head flit Presence ->"<< node_packet_status[i][j] << endl;
							}
						}
					} 			  
			  }
		  }  
	  }
  }	
}
void TGlobalarbiter::proc_arbiter_index_tx()
{
	 if(reset.read())
  {
	   
  }
  
  else
  {
	  if(!reset.read())
	  {
		  
		  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j = j+2)
			  {
				  if ((node_packet_status[i][j] == 1 &&  node_packet_status[i][j+1] == 1) || (node_packet_status[i][j] == 1 &&  node_packet_status[i][j+1] == 0) )
				  {
					  TCoord current_coord;
					  current_coord.x = i;
					  current_coord.y = j;
					  int index = coord2newId(current_coord); // converting the coordinates of index to its ID 
					  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< sc_time_stamp().to_double()/1000  << "cooridate [" <<  i <<"] [" << j <<"]"<<"index"<< index << endl;
							}
					  int c; // channel number
					  bool k = cb->assign(index, &c); // sending index of a node to circular queue
					    if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout << sc_time_stamp().to_double()/1000<< "channel number "<< c << " channel availability "<< k << endl;
							}
					  if(k == 1)
					  {
						  ack_tx_arbiter[i][j].write(1); // providing the first guy to write on the available channel
						  ack_tx_arbiter[i][j+1].write(0); // avoiding the second guy to write on the available channel
						  mwmr_channel_no[i][j].write(c); // Forwarding channel number to GWI to write data
						  node_packet_status[i][j] = 0;
						  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< sc_time_stamp().to_double()/1000  << "cooridate [" <<  i <<"] [" << j <<"] "<<"indexup:"<< index << " channel number: "<< c << " channel availability: "<< k << endl;
							}
						  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< "wrongly written" << endl;
							}
					  }
					  //else
					  //{
						  //ack_tx_arbiter[i][j].write(0);
						  //ack_tx_arbiter[i][j+1].write(0);
					  //}          
				  }
				  if (node_packet_status[i][j] == 0 &&  node_packet_status[i][j+1] == 1 )
				  {
					  TCoord current_coord1;
					  current_coord1.x = i;
					  current_coord1.y = j+1;
					  int index1 = coord2newId(current_coord1); // converting the coordinates of index to its ID 
					  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< sc_time_stamp().to_double()/1000  << "cooridate [" <<  i <<"] [" << j <<"]"<<"index"<< index1 << endl;
							}
					  int c1; // channel number
					  bool k1 = cb->assign(index1, &c1); // sending index of a node to circular queue
					  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout << sc_time_stamp().to_double()/1000 << "channel number "<< c1 << " channel availability "<< k1 << endl;
							}
					  if(k1 == 1)
					  {
						  ack_tx_arbiter[i][j+1].write(1);
						  ack_tx_arbiter[i][j].write(0);
						  mwmr_channel_no[i][j+1].write(c1);
						  node_packet_status[i][j+1] = 0;
						  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< sc_time_stamp().to_double()/1000  << "cooridate [" <<  i <<"] [" << j <<"] "<<"indexdown:"<< index1 << " channel number: "<< c1 << " channel availability: "<< k1 << endl;
							}
					  }
					  //else
					  //{
						  //ack_tx_arbiter[i][j+1].write(0);
						  //ack_tx_arbiter[i][j].write(0);

					  //}
				  }
				  //if (node_packet_status[i][j] == 0 &&  node_packet_status[i][j+1] == 0 )
				  //{
					  //ack_tx_arbiter[i][j+1].write(0);
					  //ack_tx_arbiter[i][j].write(0);
				  //} 
			  }
		  }
	  cb->rotate();
	  }
  }
  }
void TGlobalarbiter::proc_arbiter_ack_tx()
{
	 //if(reset.read())
  //{
	   //for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
	  //{
		  //for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
		  //{
			  //ack_tx_arbiter[i][j].write(0);
			  ////arbiter_current_level_tx =0;
		  //}
	  //}
  //}
  
  //else
  //{
	  //for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  //{
			  //for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  //{
				  //if (!reserve_req_queue[i][j].empty())
				  //{
					  //int ack_src_newid = reserve_req_queue[i][j].front();
				  //TCoord ack_src;                         // cordinates of the source to be acknowledged
				  //ack_src.x = id2Coord(ack_src_newid).x;
				  //ack_src.y = id2Coord(ack_src_newid).y;
				  //if (ack_txc_arbiter[ack_src.x][ack_src.y] != 0)
				  //{
					  //ack_tx_arbiter[ack_src.x][ack_src.y].write(1);
				  //}
				  //reserve_req_queue[i][j].erase (reserve_req_queue[i][j].begin()+0);
			  //}
			  //}
		  //}
	  //}
}
				  
				  
