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
				  gwi_current_level_rx_req[i][j] = 0;
				  ack_tx_arbiter_hf[i][j].write(0);
				  node_packet_status_temp[i][j] = 0;
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
				  TCoord src_coord;              // Coverting source id to co-ordinates
				  src_coord.x = newid2Coord(received_flit.src_hub_id).x;
				  src_coord.y = newid2Coord(received_flit.src_hub_id).y;
				   
						if(received_flit.flit_type == FLIT_TYPE_HEAD)
						{							
							node_packet_status[src_coord.x][src_coord.y] = 1;
							node_packet_status_temp[i][j] = 1;
							 if(TGlobalParams::verbose_mode > VERBOSE_OFF)
				    {
						cout<< sc_time_stamp().to_double()/1000  << " From Arbiter Source hub Id --> " <<  received_flit.src_hub_id <<" Head_Destination_hub_Id --> " <<  received_flit.dst_hub_id << endl;
						}
						}
						else
						{
							node_packet_status[src_coord.x][src_coord.y] = 0;
						}
						if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<< sc_time_stamp().to_double()/1000  << "cooridate [" <<  src_coord.x <<"] [" << src_coord.y <<"]"<<"Head flit Presence ->"<< node_packet_status[i][j] << endl;
							}
						gwi_current_level_rx_req[i][j] = 1-gwi_current_level_rx_req[i][j]; 
						}
						ack_tx_arbiter_hf[i][j].write(gwi_current_level_rx_req[i][j]);			  
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
	  cout<< sc_time_stamp().to_double()/1000<<endl;
	  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j++)
			  {
				 cout << node_packet_status[i][j];
			  }
			  cout << endl;
		  }
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
  }
  
  else
  {
	  if(!reset.read())
	  {
		  
		  for(int i=0; i<TGlobalParams::mesh_dim_x; i++)
		  {
			  for(int j=0; j<TGlobalParams::mesh_dim_y; j = j+8)
			  {					  
				  int k;
				   std::vector<int> node_index;
				   for(int k=0; k<8; k++)
				   {
					   if (node_packet_status[i][k] == 1)
					   {
						    TCoord current_coord;
						    current_coord.x = i;
						    current_coord.y = k;
						    int index = coord2newId(current_coord); // converting the coordinates of index to its ID
						    node_index.push_back(index);            // pushing index values of current group in to the vector 
						}
						//else
						//{
							//node_index.push_back(-1);
						//}
					}
					std::sort(node_index.begin(), node_index.end()); //std::greater<int>()); //Sorting the vector to generate winner 
					if(!node_index.empty() && node_index.front() != -1)
					{
						if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<<"working"<<endl;
						}
						int winner = node_index.front();
						if(TGlobalParams::verbose_mode > VERBOSE_OFF)
						{
							cout<<"winner: "<< winner <<endl;
						}
						node_index.clear();
						int c;
						bool k1 = cb->assign(winner, &c); // sending indexes of winner nodes to arbitration waveguide for sanction of token
						TCoord winner_coord;              // Coverting wineer id to co-ordinates
						winner_coord.x = newid2Coord(node_index[0]).x;
						winner_coord.y = newid2Coord(node_index[0]).y;
						if(k1 == 1 && c!=-1)                     // if channel is available for cluster were the node belongs, then grant permission for that node to send resevation signal and data
						{
							//if(ack_rx_arbiter_ch[winner_coord.x][winner_coord.y].read() == gwi_current_level_tx_ch[winner_coord.x][winner_coord.y])
							{
								mwmr_channel_no[winner_coord.x][winner_coord.y].write(c); // Forwarding channel number to GWI to write data
								node_packet_status[winner_coord.x][winner_coord.y] = 0;
								if(TGlobalParams::verbose_mode > VERBOSE_OFF)
								{
									cout<< sc_time_stamp().to_double()/1000  << "cooridateup [" <<  winner_coord.x <<"] [" << winner_coord.y <<"] "<<"index:"<< winner << " channel number: "<< c << " channel availability: "<< k1 << endl;
								}
								gwi_current_level_tx_ch[winner_coord.x][winner_coord.y] = 1-gwi_current_level_tx_ch[winner_coord.x][winner_coord.y];
								req_rx_arbiter_ch[winner_coord.x][winner_coord.y].write(gwi_current_level_tx_ch[winner_coord.x][winner_coord.y]); 
							}
						}
					}
			}
		}
		
	}
}
}
void TGlobalarbiter::proc_arbiter_ack_tx()
{
	if(reset.read())
  {
	  
  }
  
  else
  {
	  cb->rotate(TGlobalParams::mwmr_waveguides);
	  }
}
				  
				  
