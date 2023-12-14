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
				  reserve_req_queue[i][j].clear();
				  gwi_current_level_rx_req[i][j] = 0;
				  ack_tx_arbiter_hf[i][j].write(0);
				  temp_reserve_req_queue[i][j].clear();
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
				  if( req_tx_arbiter_hf[i][j].read()==1-gwi_current_level_rx_req[i][j])
				  { 
				  
				  TFlit received_flit = req_tx_arbiter_flit[i][j].read(); // Receving Head Flit from a tile 
				    if(TGlobalParams::verbose_mode > VERBOSE_OFF)
				    {
						cout<< sc_time_stamp().to_double()/1000  << " [Arbiter] Source_Id --> " <<  received_flit.src_hub_id <<" Head_Destination_Id --> " <<  received_flit.dst_hub_id << endl;
						}
						
				  if(received_flit.flit_type == FLIT_TYPE_HEAD)
				 {	 
				  TCoord dst;					 // Coverting destination id to co-ordinates
				  dst.x = newid2Coord(received_flit.dst_hub_id).x;
				  dst.y = newid2Coord(received_flit.dst_hub_id).y;
				  temp_reserve_req_queue[dst.x][dst.y].push_back(received_flit.src_hub_id);
				  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
				    {
						cout<< sc_time_stamp().to_double()/1000  << " [Arbiter] dst x coordinate --> " <<  dst.x <<" dst y coordinate --> " <<  dst.y << endl;
						}
				  }
						gwi_current_level_rx_req[i][j] = 1-gwi_current_level_rx_req[i][j]; 
						}
						ack_tx_arbiter_hf[i][j].write(gwi_current_level_rx_req[i][j]);			  
			  }
		  }
		  
		  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  {
				   std::sort(temp_reserve_req_queue[i][j].begin(), temp_reserve_req_queue[i][j].end());
				  reserve_req_queue[i][j].insert(reserve_req_queue[i][j].end(), temp_reserve_req_queue[i][j].begin(), temp_reserve_req_queue[i][j].end());
				  temp_reserve_req_queue[i][j].clear();
				  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
					  {
						  cout << sc_time_stamp().to_double()/1000 << "queue for X.cord" << i << "Y.cord" << j << "queue value"<<reserve_req_queue[i][j].size() << endl;
						  }
			  }
		  }  
	  }
  }	
}

void TGlobalarbiter::print()
{
	if(reset.read())
  {
  }
  else
  {
	  //cout<< sc_time_stamp().to_double()/1000<<endl;
	  //for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  //{
			  //for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  //{
				 //cout << node_packet_status[i][j];
			  //}
			  //cout << endl;
		  //}
	 //for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  //{
			  //for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  //{
				 //cout << node_packet_status_temp[i][j];
			  //}
			  //cout << endl;
		  //}
	  
}
}

void TGlobalarbiter::proc_arbiter_index_tx()
{
	 if(reset.read())
  {
	  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  {
				  req_rx_arbiter_ch[i][j].write(0);
				  gwi_current_level_tx_ch[i][j] = 0;
				  
			  }
		  }
	 for(int i=0; i<TGlobalParams::mesh_dim_x ; i++)
		  {
			  for(int j=0; j< TGlobalParams::mesh_dim_y; j++)
			  {
				  count[i][j] = 4;
				  
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
				  if (!reserve_req_queue[i][j].empty())
				  {
					  
				  int ack_src_newid = reserve_req_queue[i][j].front();
				  TCoord ack_src;                         // cordinates of the source to be acknowledged
				  ack_src.x = newid2Coord(ack_src_newid).x;
				  ack_src.y = newid2Coord(ack_src_newid).y;
				  TCoord ack_dst;
				  ack_dst.x = i;
				  ack_dst.y = j;
				  int channel_number = coord2newId(ack_dst);
				  if(count[i][j] == 6)
				  {
					  //cout<< sc_time_stamp().to_double()/1000 <<"current count : "<<count [channel_number][ack_src_newid]<<"channel_number "<<channel_number << "ack_src_newid"<< ack_src_newid <<endl; 
				  if(ack_rx_arbiter_ch[ack_src.x][ack_src.y].read() == gwi_current_level_tx_ch[ack_src.x][ack_src.y])
				  {
				  mwsr_channel_send[ack_src.x][ack_src.y].write(channel_number); // Forwarding channel ack to GWI to write data
				  reserve_req_queue[i][j].erase (reserve_req_queue[i][j].begin()+0);
				  count [i][j] =0;
				  //count [channel_number][ack_src_newid] = sc_time_stamp().to_double()/1000;
				  //cout<< sc_time_stamp().to_double()/1000 <<"Future count : "<<count [channel_number][ack_src_newid] <<endl; 
				  gwi_current_level_tx_ch[ack_src.x][ack_src.y] = 1-gwi_current_level_tx_ch[ack_src.x][ack_src.y];
				  req_rx_arbiter_ch[ack_src.x][ack_src.y].write(gwi_current_level_tx_ch[ack_src.x][ack_src.y]); 
				  }
			      }
			      else
			      {
					  count[i][j]++;			
				  }
					  
			      }
			      		  
			}
		}
		
	}
}
}
	  
