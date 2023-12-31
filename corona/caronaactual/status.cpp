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
	if (arrival_time - DEFAULT_RESET_TIME < warm_up_time)
    return;

  int i = searchCommHistory(flit.src_id);
  
  if (i == -1)
    {
      // first flit received from a given source
      // initialize CommHist structure
      CommHistory ch;

      ch.src_id = flit.src_id;
      ch.total_received_flits = 0;
      chist.push_back(ch);

      i = chist.size() - 1;
    }

  if (flit.flit_type == FLIT_TYPE_HEAD) 
  {
    chist[i].delays.push_back(arrival_time - flit.timestamp);
    //cout << arrival_time<< " Arrival time " << " sent time " << flit.timestamp << endl;
}
 if (flit.flit_type == FLIT_TYPE_TAIL) 
  chist[i].total_received_flits = chist[i].total_received_flits + flit.sequence_no;
  chist[i].last_received_flit_time = arrival_time - warm_up_time;
  
}

//---------------------------------------------------------------------------

double TStats::getAverageDelay(const int src_id)
{
  double sum = 0.0;
  
  int i = searchCommHistory(src_id);

  assert(i >= 0);

  for (unsigned int j=0; j<chist[i].delays.size(); j++)
    sum += chist[i].delays[j];

  return sum/(double)chist[i].delays.size();
}

//---------------------------------------------------------------------------

double TStats::getAverageDelay()
{
  double avg = 0.0;

  for (unsigned int k=0; k<chist.size(); k++)
    {
      unsigned int samples = chist[k].delays.size();
      if (samples)
	avg += (double)samples * getAverageDelay(chist[k].src_id);
    }

  return avg/(double)getReceivedPackets();
}

//---------------------------------------------------------------------------

double TStats::getMaxDelay(const int src_id)
{
  double maxd = -1.0;
  
  int i = searchCommHistory(src_id);

  assert(i >= 0);

  for (unsigned int j=0; j<chist[i].delays.size(); j++)
    if (chist[i].delays[j] > maxd)
      {
		//cout << src_id << " -> " << id << ": " << chist[i].delays[j] << endl;
	maxd = chist[i].delays[j];
      }
  return maxd;
}

//---------------------------------------------------------------------------

double TStats::getMaxDelay()
{
  double maxd = -1.0;

  for (unsigned int k=0; k<chist.size(); k++)
    {
      unsigned int samples = chist[k].delays.size();
      if (samples)
	{
	  double m = getMaxDelay(chist[k].src_id);
	  if (m > maxd)
	    maxd = m;
	}
    }

  return maxd;
}

//---------------------------------------------------------------------------

double TStats::getAverageThroughput(const int src_id)
{
  int i = searchCommHistory(src_id);

  assert(i >= 0);

  if (chist[i].total_received_flits == 0)
    return -1.0;
  else
    return (double)chist[i].total_received_flits/(double)chist[i].last_received_flit_time;
}

//---------------------------------------------------------------------------

double TStats::getAverageThroughput()
{  double sum = 0.0;

  for (unsigned int k=0; k<chist.size(); k++)
    {
      double avg = getAverageThroughput(chist[k].src_id);
      if (avg > 0.0)
	sum += avg;
    }

  return sum;
}

//---------------------------------------------------------------------------

unsigned int TStats::getReceivedPackets()
{
  int n = 0;

  for (unsigned int i=0; i<chist.size(); i++)
    n += chist[i].delays.size();

  return n;
}

//---------------------------------------------------------------------------
int TStats::randInt(int min, int max)
{
  return min + (int)((double)(max-min+1) * rand()/(RAND_MAX+1.0));
}

unsigned int TStats::getReceivedFlits()
{
  int n = 0;

  //for (unsigned int i=0; i<chist.size(); i++)
    //n += chist[i].total_received_flits;
    
   for (unsigned int i=0; i<chist.size(); i++)
   n += chist[i].delays.size();

  return n * randInt(5, 7);
}

//---------------------------------------------------------------------------

unsigned int TStats::getTotalCommunications()
{
  
  return chist.size();
}

//---------------------------------------------------------------------------

double TStats::getCommunicationEnergy(int src_id, int dst_id)
{
  
  return 0;
}

//---------------------------------------------------------------------------

int TStats::searchCommHistory(int src_id)
{ 
	for (unsigned int i=0; i<chist.size(); i++)
    if (chist[i].src_id == src_id)
      return i;

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

