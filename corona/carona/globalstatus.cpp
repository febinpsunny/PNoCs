#include <iomanip>
#include "globalstatus.h"


//---------------------------------------------------------------------------
// Initialize global configuration parameters (can be overridden with command-line arguments)
int   TGlobalParams::verbose_mode                     = DEFAULT_VERBOSE_MODE;
int   TGlobalParams::trace_mode                       = DEFAULT_TRACE_MODE;
char  TGlobalParams::trace_filename[128]              = DEFAULT_TRACE_FILENAME;
int   TGlobalParams::topology                         = MESH_2D;
int   TGlobalParams::mesh_dim_x                       = DEFAULT_MESH_DIM_X;
int   TGlobalParams::mesh_dim_y                       = DEFAULT_MESH_DIM_Y;
int   TGlobalParams::mesh_dim_z                       = DEFAULT_MESH_DIM_Z;
int   TGlobalParams::buffer_depth                     = DEFAULT_BUFFER_DEPTH;
int   TGlobalParams::photonic_buffer_depth            = PHOTONIC_BUFFER_DEPTH;
int   TGlobalParams::min_packet_size                  = DEFAULT_MIN_PACKET_SIZE;
int   TGlobalParams::max_packet_size                  = DEFAULT_MAX_PACKET_SIZE;
int   TGlobalParams::routing_algorithm                = DEFAULT_ROUTING_ALGORITHM;
char  TGlobalParams::routing_table_filename[128]      = DEFAULT_ROUTING_TABLE_FILENAME;
int   TGlobalParams::selection_strategy               = DEFAULT_SELECTION_STRATEGY;
float TGlobalParams::packet_injection_rate            = DEFAULT_PACKET_INJECTION_RATE;
float TGlobalParams::probability_of_retransmission    = DEFAULT_PROBABILITY_OF_RETRANSMISSION;
int   TGlobalParams::traffic_distribution             = DEFAULT_TRAFFIC_DISTRIBUTION;
char  TGlobalParams::traffic_table_filename[128]      = DEFAULT_TRAFFIC_TABLE_FILENAME;
int   TGlobalParams::simulation_time                  = DEFAULT_SIMULATION_TIME;
int   TGlobalParams::stats_warm_up_time               = DEFAULT_STATS_WARM_UP_TIME;
int   TGlobalParams::rnd_generator_seed               = time(NULL);
bool  TGlobalParams::detailed                         = DEFAULT_DETAILED;
float TGlobalParams::dyad_threshold                   = DEFAULT_DYAD_THRESHOLD;
int   TGlobalParams::photonic_noc                     = DEFAULT_PHOTONIC_NOC;

unsigned int TGlobalParams::max_volume_to_be_drained  = DEFAULT_MAX_VOLUME_TO_BE_DRAINED;
vector<pair<int,double> > TGlobalParams::hotspots;



//---------------------------------------------------------------------------

TGlobalStats::TGlobalStats(TNoC* _noc)
{
  //noc = _noc;
//#ifdef TESTING
  //drained_total = 0;
//#endif
    
    //threeCrossThree      = (TGlobalParams::mesh_dim_x == 3 && TGlobalParams::mesh_dim_y == 3) ? 1 : 0;
    //fourCrossFour        = (TGlobalParams::mesh_dim_x == 4 && TGlobalParams::mesh_dim_y == 4) ? 1 : 0;
    
    //if(threeCrossThree) 
    //{ 
		//photonic_router_id.push_back(3); photonic_router_id.push_back(5); 
	//}
	//else if(fourCrossFour) 
	//{ 
		//photonic_router_id.push_back(4); photonic_router_id.push_back(7); 
		//photonic_router_id.push_back(8); photonic_router_id.push_back(11); 
	//}
	//else
	//{
		//photonic_router_id.push_back(1 *  TGlobalParams::mesh_dim_x + 1);
		//photonic_router_id.push_back(1 *  TGlobalParams::mesh_dim_x + (TGlobalParams::mesh_dim_x - 2));
		//photonic_router_id.push_back((TGlobalParams::mesh_dim_y - 2) *  TGlobalParams::mesh_dim_x + 1);
		//photonic_router_id.push_back((TGlobalParams::mesh_dim_y - 2) *  TGlobalParams::mesh_dim_x + 
									//(TGlobalParams::mesh_dim_x - 2));
	//}
}

//---------------------------------------------------------------------------

double TGlobalStats::getAverageDelay()
{
  unsigned int total_packets    = 0;
  double       avg_delay        = 0.0;
  unsigned int received_packets = 0;
  std::vector<int>::iterator it;
  int x, y;

  //for (int j=0; j<TGlobalParams::mesh_dim_y; j++)
  //{
    //for (int i=0; i<TGlobalParams::mesh_dim_x; i++)
    //{
	   //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), j * TGlobalParams::mesh_dim_x + i) ;
	   //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	   //{
         //continue;
	   //}

  	   //received_packets = noc->t[i][j]->r->stats.getReceivedPackets(); 

	    //if (received_packets)
	    //{
	      //avg_delay += received_packets * noc->t[i][j]->r->stats.getAverageDelay();
	      //total_packets += received_packets;
	    //}
      //}
    //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int j=0; j<(int) photonic_router_id.size(); j++)
    //{
	   //coord = id2Coord(photonic_router_id[j]);
	   //x     =  coord.x;
	   //y     =  coord.y;
	   
	   //received_packets = noc->git[x][y] -> r->stats.getReceivedPackets(); 

	   //if (received_packets)
	   //{
		//avg_delay += received_packets * noc->git[x][y]->r->stats.getAverageDelay();
		//total_packets += received_packets;
	   //}
	 //}
  //}
    //avg_delay /= (double)total_packets;

    return avg_delay;  
}

//---------------------------------------------------------------------------

double TGlobalStats::getAverageDelay(const int src_id, const int dst_id)
{
  //std::vector<int>::iterator it;
  
  //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), dst_id) ;
  //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
  //{
    //TGITile* gitile = noc->searchGINode(dst_id);
    //assert(gitile != NULL);

    //return gitile->r->stats.getAverageDelay(src_id);
  //}
  //else
  //{
    //TTile* tile = noc->searchNode(dst_id);
    //assert(tile != NULL);
    //return tile->r->stats.getAverageDelay(src_id);
  //}
   return 0;
}

/*----------------------NO CHANGE TO BE MADE HERE---------------------------*/

double TGlobalStats::getMaxDelay()
{
  double maxd = -1.0;

  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
      //{
	//TCoord coord;
	//coord.x = x;
	//coord.y = y;
	//int node_id = coord2Id(coord);
	//double d = getMaxDelay(node_id);
	//if (d > maxd)
	  //maxd = d;
      //}

  return maxd;
}

//---------------------------------------------------------------------------

double TGlobalStats::getMaxDelay(const int node_id)
{
  //TCoord coord = id2Coord(node_id);

  //std::vector<int>::iterator iter;
  //iter = std::find(photonic_router_id.begin(), photonic_router_id.end(), node_id) ;

  //if(iter != photonic_router_id.end() && TGlobalParams::photonic_noc) 
  //{
    //unsigned int received_packets = noc->git[coord.x][coord.y]->r->stats.getReceivedPackets(); 
	//if (received_packets)
      //return noc->git[coord.x][coord.y]->r->stats.getMaxDelay();
    //else
      //return -1.0;  
  //}
  //else
  //{
    //unsigned int received_packets = noc->t[coord.x][coord.y]->r->stats.getReceivedPackets(); 
    //if (received_packets)
      //return noc->t[coord.x][coord.y]->r->stats.getMaxDelay();
    //else
      return -1.0;
  }
}

//---------------------------------------------------------------------------

double TGlobalStats::getMaxDelay(const int src_id, const int dst_id)
{

  //std::vector<int>::iterator iter;
  //iter = std::find(photonic_router_id.begin(), photonic_router_id.end(), dst_id) ;

  //if(iter != photonic_router_id.end() && TGlobalParams::photonic_noc) 
  //{
    //TGITile* gtile = noc->searchGINode(dst_id);
    //assert(gtile != NULL);
    //return gtile->r->stats.getMaxDelay(src_id);
  //}
  //else
  //{
    //TTile* tile = noc->searchNode(dst_id);
    //assert(tile != NULL);
    //return tile->r->stats.getMaxDelay(src_id);
  //}
   return 0;
}


//---------------------------------------------------------------------------

vector<vector<double> > TGlobalStats::getMaxDelayMtx()
{
  //vector<vector<double> > mtx;

  //mtx.resize(TGlobalParams::mesh_dim_y);
  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //mtx[y].resize(TGlobalParams::mesh_dim_x);

  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
      //{
	    //TCoord coord;
	    //coord.x = x;
	    //coord.y = y;
	    //int id = coord2Id(coord);
	    //mtx[y][x] = getMaxDelay(id);
      //}

  //return mtx;
   return 0;
}

//---------------------------------------------------------------------------

double TGlobalStats::getAverageThroughput(const int src_id, const int dst_id)
{
  //std::vector<int>::iterator iter;
  //iter = std::find(photonic_router_id.begin(), photonic_router_id.end(), dst_id) ;

  //if(iter != photonic_router_id.end() && TGlobalParams::photonic_noc) 
  //{
    //TGITile* gitile = noc->searchGINode(dst_id);
    //assert(gitile != NULL);
    //return gitile->r->stats.getAverageThroughput(src_id);
  //}
  //else
  //{	
    //TTile* tile = noc->searchNode(dst_id);
    //assert(tile != NULL);
    //return tile->r->stats.getAverageThroughput(src_id);
  //}
   return 0;
}

//---------------------------------------------------------------------------

double TGlobalStats::getAverageThroughput()
{
  //unsigned int total_comms    = 0;
  //double       avg_throughput = 0.0;
  //std::vector<int>::iterator it;
  //unsigned int ncomms;
  //int i , j;

  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
      //{
  	     //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	     //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	     //{
          //continue;
	     //}
	     //ncomms = noc->t[x][y]->r->stats.getTotalCommunications(); 

	    //if (ncomms)
	    //{
	      //avg_throughput += ncomms * noc->t[x][y]->r->stats.getAverageThroughput();
	      //total_comms += ncomms;
	     //}
       //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int k=0; k<(int) photonic_router_id.size(); k++)
    //{
	   //coord = id2Coord(photonic_router_id[k]);
	   //i     =  coord.x;
	   //j     =  coord.y;
	   
	   //ncomms = noc->git[i][j]->r->stats.getTotalCommunications(); 

	   //if (ncomms)
	   //{
	     //avg_throughput += ncomms * noc->git[i][j]->r->stats.getAverageThroughput();
	     //total_comms += ncomms;
	   //}
     //}
   //}
       

  //avg_throughput /= (double)total_comms;

  //return avg_throughput;
   return 0;
}

//---------------------------------------------------------------------------

unsigned int TGlobalStats::getReceivedPackets()
{
  //unsigned int n = 0;
  //std::vector<int>::iterator it;
  //int i,j;
  ////cout << photonic_router_id.size() << "  THE SIZE " << endl;
  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
    //{
  	  //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	  //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	  //{
        //continue;
	  //}
      //n += noc->t[x][y]->r->stats.getReceivedPackets();
    //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int k=0; k<(int) photonic_router_id.size(); k++)
    //{
	   //coord = id2Coord(photonic_router_id[k]);
	   //i     =  coord.x;
	   //j     =  coord.y;
       //n += noc->git[i][j]->r->stats.getReceivedPackets();
    //}
   //}
    
  //return n;
   return 0;
}

//---------------------------------------------------------------------------

unsigned int TGlobalStats::getReceivedFlits()
{
  //unsigned int n = 0;
  //std::vector<int>::iterator it;
  //int i,j;

  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
    //{
	   //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	   //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	   //{
         //continue;
	   //}

       //n += noc->t[x][y]->r->stats.getReceivedFlits();
//#ifdef TESTING
       //drained_total+= noc->t[x][y]->r->local_drained;
//#endif
    //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int k=0; k<(int) photonic_router_id.size(); k++)
    //{
	   //coord = id2Coord(photonic_router_id[k]);
	   //i     =  coord.x;
	   //j     =  coord.y;
       //n += noc->git[i][j]->r->stats.getReceivedFlits();
//#ifdef TESTING
       //drained_total+= noc->t[x][y]->r->local_drained;
//#endif       
    //}
   //}    

  //return n;
   return 0;
}

//---------------------------------------------------------------------------

double TGlobalStats::getThroughput()
{
  //int total_cycles = TGlobalParams::simulation_time - 
    //TGlobalParams::stats_warm_up_time;
    //int i,j;

  //std::vector<int>::iterator it;

  //unsigned int n   = 0;
  //unsigned int trf = 0;
  //unsigned int rf;
  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
      //{
	    //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	    //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	    //{
         //continue;
	    //}
		  
	    //rf = noc->t[x][y]->r->stats.getReceivedFlits();
	    //if (rf != 0)
	    //n++;
	    //trf += rf;
      //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int k=0; k<(int) photonic_router_id.size(); k++)
    //{
	   //coord = id2Coord(photonic_router_id[k]);
	   //i     =  coord.x;
	   //j     =  coord.y;
	   //rf = noc->git[i][j]->r->stats.getReceivedFlits();
	   //if (rf != 0)
	   //n++;
	   //trf += rf;      
     //}   
   //}
   
  //return (double)trf/(double)(total_cycles * n);
   return 0;

}

//---------------------------------------------------------------------------

vector<vector<unsigned long> > TGlobalStats::getRoutedFlitsMtx()
{

  //vector<vector<unsigned long> > mtx;
  //std::vector<int>::iterator it;
  //int i,j;

  //mtx.resize(TGlobalParams::mesh_dim_y);
  //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //mtx[y].resize(TGlobalParams::mesh_dim_x);

  //for(int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for(int x=0; x<TGlobalParams::mesh_dim_x; x++)
    //{
      //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	  //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	  //{
         //continue;
	  //}
		
      //mtx[y][x] = noc->t[x][y]->r->getRoutedFlits();
    //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int k=0; k<(int) photonic_router_id.size(); k++)
    //{
	   //coord = id2Coord(photonic_router_id[k]);
	   //i     =  coord.x;
	   //j     =  coord.y;
       //mtx[i][j] = noc->git[i][j]->r->getRoutedFlits();
	   
    //}
  //}

  //return mtx;
   return 0;
}

//---------------------------------------------------------------------------

double TGlobalStats::getPower()
{
  //double power = 0.0;
  //std::vector<int>::iterator it;
  //int i,j;

  //for(int y=0; y<TGlobalParams::mesh_dim_y; y++)
    //for(int x=0; x<TGlobalParams::mesh_dim_x; x++)
    //{
      //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	  //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	  //{
         //continue;
	  //}

      //power += noc->t[x][y]->r->getPower();
    //}

  //if(TGlobalParams::photonic_noc)
  //{ 
	//TCoord coord;
    //for(int k=0; k<(int) photonic_router_id.size(); k++)
    //{
	   //coord = id2Coord(photonic_router_id[k]);
	   //i     =  coord.x;
	   //j     =  coord.y;
       //power += noc->git[i][j]->r->getPower();
      
    //}
  //} 
  //return power;
   return 0;
}

//---------------------------------------------------------------------------

void TGlobalStats::showStats(std::ostream& out, bool detailed)
{
  out << "% Total received packets: " << getReceivedPackets() << endl;
  out << "% Total received flits: " << getReceivedFlits() << endl;
  out << "% Global average delay (cycles): " << getAverageDelay() << endl;
  out << "% Global average throughput (flits/cycle): " << getAverageThroughput() << endl;
  out << "% Throughput (flits/cycle/IP): " << getThroughput() << endl;
  out << "% Max delay (cycles): " << getMaxDelay() << endl;
  out << "% Total energy (J): " << getPower() << endl;

  std::vector<int>::iterator it;
  int i , j;

  //if (detailed)
    //{
      //out << endl << "detailed = [" << endl;
      //for (int y=0; y<TGlobalParams::mesh_dim_y; y++)
	    //for (int x=0; x<TGlobalParams::mesh_dim_x; x++)
	    //{
          //it = std::find(photonic_router_id.begin(), photonic_router_id.end(), y * TGlobalParams::mesh_dim_x + x) ;
	      //if(it != photonic_router_id.end() && TGlobalParams::photonic_noc) 
	      //{
            //continue;
	      //}  			
	      //noc->t[x][y]->r->stats.showStats(y*TGlobalParams::mesh_dim_x+x,
					   //out, 
					   //true);
        //}
       //if(TGlobalParams::photonic_noc)
       //{ 
	     //TCoord coord;
         //for(int k=0; k<(int) photonic_router_id.size(); k++)
         //{
	       //coord = id2Coord(photonic_router_id[k]);
	       //i     =  coord.x;
	       //j     =  coord.y;
	       //noc->git[i][j]->r->stats.showStats(j*TGlobalParams::mesh_dim_x+i,
					   //out, 
					   //true);	       
	     //}
	   //}
       //out << "];" << endl;

      //// show MaxDelay matrix
      //vector<vector<double> > md_mtx = getMaxDelayMtx();

      //out << endl << "max_delay = [" << endl;
      //for (unsigned int y=0; y<md_mtx.size(); y++)
	//{
	  //out << "   ";
	  //for (unsigned int x=0; x<md_mtx[y].size(); x++)
	    //out << setw(6) << md_mtx[y][x];
	  //out << endl;
	//}
      //out << "];" << endl;

      //// show RoutedFlits matrix
      //vector<vector<unsigned long> > rf_mtx = getRoutedFlitsMtx();

      //out << endl << "routed_flits = [" << endl;
      //for (unsigned int y=0; y<rf_mtx.size(); y++)
	//{
	  //out << "   ";
	  //for (unsigned int x=0; x<rf_mtx[y].size(); x++)
	    //out << setw(10) << rf_mtx[y][x];
	  //out << endl;
	//}
      //out << "];" << endl;
    //}
}

//---------------------------------------------------------------------------

