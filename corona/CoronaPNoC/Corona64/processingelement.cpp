#include "GlobalTypeDefs.h"
#include "processingelement.h"

//---------------------------------------------------------------------------

int TProcessingElement::randInt(int min, int max)
{
  return min + (int)((double)(max-min+1) * rand()/(RAND_MAX+1.0));
}

//---------------------------------------------------------------------------

void TProcessingElement::rxProcess() // receiving process
{
  if(reset.read())
  {
    ack_rx.write(0);
    current_level_rx = 0;
  }
  else
  {
    if(req_rx.read()==1-current_level_rx)
    {
      TFlit flit_tmp = flit_rx.read();
      if(TGlobalParams::verbose_mode > VERBOSE_OFF)
      {
        cout << sc_simulation_time() << ": ProcessingElement[" << local_id << "] RECEIVING " << flit_tmp << endl;
      }
      current_level_rx = 1-current_level_rx;     // Negate the old value for Alternating Bit Protocol (ABP)
    }
    ack_rx.write(current_level_rx);
  }
}

//---------------------------------------------------------------------------

void TProcessingElement::txProcess()
{
  if(reset.read())
  {
    req_tx.write(0);
    current_level_tx = 0;
    transmittedAtPreviousCycle = false;
  }
  else
  {
    TPacket packet;

    if (canShot(packet))
    {
      packet_queue.push(packet);
      transmittedAtPreviousCycle = true;
    }
    else
      transmittedAtPreviousCycle = false;


    if(ack_tx.read() == current_level_tx)
    {
      if(!packet_queue.empty())
      {
        TFlit flit = nextFlit();                  // Generate a new flit
        if(TGlobalParams::verbose_mode > VERBOSE_OFF)
        {
          cout << sc_time_stamp().to_double()/1000 << ": ProcessingElement[" << local_id << "] SENDING " << flit << endl;
        }
	flit_tx->write(flit);                     // Send the generated flit
	if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   {
         cout<< sc_time_stamp().to_double()/1000  <<"localid: "<< local_id<< " Source_Id --> " <<  flit.src_id <<" Destination_Id --> " <<  flit.dst_id << endl; 	   
	   }
	current_level_tx = 1-current_level_tx;    // Negate the old value for Alternating Bit Protocol (ABP)
	req_tx.write(current_level_tx);
      }
    }
  }
}

//---------------------------------------------------------------------------

TFlit TProcessingElement::nextFlit()
{
		TFlit   flit;
		TPacket packet = packet_queue.front();
		flit.src_id      = packet.src_id;
		flit.dst_id      = packet.dst_id;
		flit.timestamp   = packet.timestamp;
		flit.sequence_no = packet.size - packet.flit_left;
		flit.hop_no      = 0;
		//  flit.payload     = DEFAULT_PAYLOAD;
		if(packet.size == packet.flit_left)
		flit.flit_type = FLIT_TYPE_HEAD;
		else if(packet.flit_left == 1)
		flit.flit_type = FLIT_TYPE_TAIL;
		else
		flit.flit_type = FLIT_TYPE_BODY;
		packet_queue.front().flit_left--;
		if(packet_queue.front().flit_left == 0)
		packet_queue.pop();
		return flit;
	
}

//---------------------------------------------------------------------------

bool TProcessingElement::canShot(TPacket& packet)
{
  bool   shot;
  double threshold;

  if (TGlobalParams::traffic_distribution != TRAFFIC_TABLE_BASED)
    {
      if (!transmittedAtPreviousCycle)
	threshold = TGlobalParams::packet_injection_rate;
      else
	threshold = TGlobalParams::probability_of_retransmission;
    if (TGlobalParams::real_traffic == 1)
	{
		shot = b_mark.packet_injection_response(local_id);
		if(shot==1)
		{
			//cout<< sc_time_stamp().to_double()/1000 <<"localid: "<< local_id << " shot value: "<<shot<<endl;
		}
	}
	else
	{
      shot = (((double)rand())/RAND_MAX < threshold);
    }
      if (shot)
	{
	  switch(TGlobalParams::traffic_distribution)
	    {
	    case TRAFFIC_RANDOM:
	      packet = trafficRandom();
	      break;
	      
	    case TRAFFIC_TRANSPOSE1:
	      packet = trafficTranspose1();
	      break;
	      
	    case TRAFFIC_TRANSPOSE2:
	      packet = trafficTranspose2();
	      break;
	      
	    case TRAFFIC_BIT_REVERSAL:
	      packet = trafficBitReversal();
	      break;

	    case TRAFFIC_SHUFFLE:
	      packet = trafficShuffle();
	      break;

	    case TRAFFIC_BUTTERFLY:
	      packet = trafficButterfly();
	      break;
	    case TRAFFIC_HOTSPOT:
	      packet = hotspot();
	      break;
	    case TRAFFIC_BENCHMARK:
	      packet = benchmarktraffic();
	      break;

	    default:
	      assert(false);
	    }
	}
    }
  //else
    //{ // Table based communication traffic
      //if (never_transmit)
	//return false;

      //double now         = sc_time_stamp().to_double()/1000;
      //bool   use_pir     = (transmittedAtPreviousCycle == false);
      //vector<pair<int,double> > dst_prob;
      //double threshold = traffic_table->getCumulativePirPor(local_id, (int)now, use_pir, dst_prob);

      //double prob = (double)rand()/RAND_MAX;
      //shot = (prob < threshold);
      //if (shot)
	//{
	  //for (unsigned int i=0; i<dst_prob.size(); i++)
	    //{
	      //if (prob < dst_prob[i].second) 
		//{
		  //packet.make(local_id, dst_prob[i].first, now, getRandomSize());
		  //break;
		//}
	    //}
	//}
    //}
 if(TGlobalParams::verbose_mode > VERBOSE_OFF && shot ==1)
	   {
         cout<< sc_time_stamp().to_double()/1000  <<"localid: "<< local_id<< " in shot packet Source_Id --> " <<  packet.src_id <<" in shot packet Destination_Id --> " <<  packet.dst_id << endl; 	   
	   }
  return shot;
}

//---------------------------------------------------------------------------

TPacket TProcessingElement::trafficRandom()
{
  TPacket p;
  p.src_id = local_id;
  double rnd = rand()/(double)RAND_MAX;
  double range_start = 0.0;

  //cout << "\n " << sc_time_stamp().to_double()/1000 << " PE " << local_id << " rnd = " << rnd << endl;

  int max_id = (TGlobalParams::mesh_dim_x * TGlobalParams::mesh_dim_y)-1;

  // Random destination distribution
  do
  {
    p.dst_id = randInt(0, max_id);

    // check for hotspot destination
    for (uint i = 0; i<TGlobalParams::hotspots.size(); i++)
    {
	//cout << sc_time_stamp().to_double()/1000 << " PE " << local_id << " Checking node " << TGlobalParams::hotspots[i].first << " with P = " << TGlobalParams::hotspots[i].second << endl;

	if (rnd>=range_start && rnd < range_start + TGlobalParams::hotspots[i].second)
	{
	    if (local_id != TGlobalParams::hotspots[i].first)
	    {
		//cout << sc_time_stamp().to_double()/1000 << " PE " << local_id <<" That is ! " << endl;
		p.dst_id = TGlobalParams::hotspots[i].first;
	    }
	    break;
	}
	else 
	    range_start+=TGlobalParams::hotspots[i].second; // try next
    }
  } while(p.dst_id==p.src_id);

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}
//benchmark traffic distribution


TPacket TProcessingElement::benchmarktraffic()
{
	//cout<< "benchmark functionaccessed "<<endl;
  TPacket p;
  p.src_id = local_id;

  TCoord src,dst;
  if(local_id % 8 !=7)
  {
	  int k = local_id/8;
	  int did= k*8 + 7;
      p.dst_id = did;
  }
  else
  {
	  int k = randInt(local_id-7, local_id-1);
      p.dst_id = k;
  }
  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();
  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   {
         cout<< sc_time_stamp().to_double()/1000  <<"localid: "<< local_id<< " in packet Source_Id --> " <<  p.src_id <<" in packet Destination_Id --> " <<  p.dst_id << endl; 	   
	   }
  return p;
}
//---------------------------------------------------------------------------

TPacket TProcessingElement::trafficTranspose1()
{
  TPacket p;
  p.src_id = local_id;
  TCoord src,dst;

  // Transpose 1 destination distribution
  src.x = id2Coord(p.src_id).x;
  src.y = id2Coord(p.src_id).y;
  dst.x = TGlobalParams::mesh_dim_x-1-src.y;
  dst.y = TGlobalParams::mesh_dim_y-1-src.x;
  fixRanges(src, dst);
  p.dst_id = coord2Id(dst);

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}

TPacket TProcessingElement::hotspot()
{
  TPacket p;
  p.src_id = local_id;
  if (p.src_id != 1)
  {
	  p.dst_id = 1;
  }
  else
  {
	  p.dst_id = 5;
  }

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}

//---------------------------------------------------------------------------

TPacket TProcessingElement::trafficTranspose2() // Tpacket is th data type
{
  TPacket p;
  p.src_id = local_id;
  TCoord src,dst;

  // Transpose 2 destination distribution
  src.x = id2Coord(p.src_id).x;
  src.y = id2Coord(p.src_id).y;
  dst.x = src.y;
  dst.y = src.x;
  fixRanges(src, dst);
  p.dst_id = coord2Id(dst);

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}

//---------------------------------------------------------------------------

void TProcessingElement::setBit(int &x, int w, int v)
{
  int mask = 1 << w;
  
  if (v == 1)
    x = x | mask;
  else if (v == 0)
    x = x & ~mask;
  else
    assert(false);    
}

//---------------------------------------------------------------------------

int TProcessingElement::getBit(int x, int w)
{
  return (x >> w) & 1;
}

//---------------------------------------------------------------------------

inline double TProcessingElement::log2ceil(double x)
{
  return ceil(log(x)/log(2.0));
}

//---------------------------------------------------------------------------

TPacket TProcessingElement::trafficBitReversal()
{
  
  int nbits = (int)log2ceil((double)(TGlobalParams::mesh_dim_x*TGlobalParams::mesh_dim_y));
  int dnode = 0;
  for (int i=0; i<nbits; i++)
    setBit(dnode, i, getBit(local_id, nbits-i-1));

  TPacket p;
  p.src_id = local_id;
  p.dst_id = dnode;

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}

//---------------------------------------------------------------------------

TPacket TProcessingElement::trafficShuffle()
{
  
  int nbits = (int)log2ceil((double)(TGlobalParams::mesh_dim_x*TGlobalParams::mesh_dim_y));
  int dnode = 0;
  for (int i=0; i<nbits-1; i++)
    setBit(dnode, i+1, getBit(local_id, i));
  setBit(dnode, 0, getBit(local_id, nbits-1));

  TPacket p;
  p.src_id = local_id;
  p.dst_id = dnode;

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}

//---------------------------------------------------------------------------

TPacket TProcessingElement::trafficButterfly()
{
  
  int nbits = (int)log2ceil((double)(TGlobalParams::mesh_dim_x*TGlobalParams::mesh_dim_y));
  int dnode = 0;
  for (int i=1; i<nbits-1; i++)
    setBit(dnode, i, getBit(local_id, i));
  setBit(dnode, 0, getBit(local_id, nbits-1));
  setBit(dnode, nbits-1, getBit(local_id, 0));

  TPacket p;
  p.src_id = local_id;
  p.dst_id = dnode;

  p.timestamp = sc_time_stamp().to_double()/1000;
  p.size = p.flit_left = getRandomSize();

  return p;
}

//---------------------------------------------------------------------------

void TProcessingElement::fixRanges(const TCoord src, TCoord& dst)
{
  // Fix ranges
  if(dst.x<0) dst.x=0;
  if(dst.y<0) dst.y=0;
  if(dst.x>=TGlobalParams::mesh_dim_x) dst.x=TGlobalParams::mesh_dim_x-1;
  if(dst.y>=TGlobalParams::mesh_dim_y) dst.y=TGlobalParams::mesh_dim_y-1;
}

//---------------------------------------------------------------------------

int TProcessingElement::getRandomSize()
{
  return randInt(TGlobalParams::min_packet_size, 
                 TGlobalParams::max_packet_size);
}

//---------------------------------------------------------------------------
