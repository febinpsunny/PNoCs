#include <iostream>
#include <iomanip>
#include "GlobalTypeDefs.h"
#include "status.h"

//---------------------------------------------------------------------------

void TStats::configure(const int node_id, const double _warm_up_time)
{
  //id = node_id;
  //warm_up_time = _warm_up_time;
}

//---------------------------------------------------------------------------

void TStats::receivedFlit(const double arrival_time,
			  const TFlit& flit)
{
  
}

//---------------------------------------------------------------------------

double TStats::getAverageDelay(const int src_id)
{
  return 0;
}

//---------------------------------------------------------------------------

double TStats::getAverageDelay()
{
  
  return 0;
}

//---------------------------------------------------------------------------

double TStats::getMaxDelay(const int src_id)
{
  
  return 0;
}

//---------------------------------------------------------------------------

double TStats::getMaxDelay()
{
 
  return 0;
}

//---------------------------------------------------------------------------

double TStats::getAverageThroughput(const int src_id)
{
 
    return 0;
}

//---------------------------------------------------------------------------

double TStats::getAverageThroughput()
{
  
  return sum;
}

//---------------------------------------------------------------------------

unsigned int TStats::getReceivedPackets()
{
  
  return 0;
}

//---------------------------------------------------------------------------

unsigned int TStats::getReceivedFlits()
{
  
  return 0;
}

//---------------------------------------------------------------------------

unsigned int TStats::getTotalCommunications()
{
  
  return 0;
}

//---------------------------------------------------------------------------

double TStats::getCommunicationEnergy(int src_id, int dst_id)
{
  
  return 0;
}

//---------------------------------------------------------------------------

int TStats::searchCommHistory(int src_id)
{
 
  return -1;
}

//---------------------------------------------------------------------------

void TStats::showStats(int curr_node,
		       std::ostream& out,
		       bool header)
{

  out << "% Aggregated average delay (cycles): " << getAverageDelay() << endl;
  out << "% Aggregated average throughput (flits/cycle): " << getAverageThroughput() << endl;
}

