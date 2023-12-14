#include <cassert>
#include "GlobalTypeDefs.h"
#include "power.h"


using namespace std;

TPower::TPower()
{
  pwr = 0.0;
  pwr_standby  = PWR_STANDBY;
  pwr_forward  = PWR_FORWARD_FLIT;
  pwr_incoming = PWR_INCOMING;

  //if (TGlobalParams::routing_algorithm == ROUTING_XY) pwr_routing = PWR_ROUTING_XY;
  //else if (TGlobalParams::routing_algorithm == ROUTING_XYZ) pwr_routing = PWR_ROUTING_XYZ;
  //else assert(false);

  //if (TGlobalParams::selection_strategy == SEL_RANDOM) pwr_selection = PWR_SEL_RANDOM;
  //else assert(false);
}

// ---------------------------------------------------------------------------

void TPower::Routing()
{
  pwr += pwr_routing;
}

// ---------------------------------------------------------------------------

void TPower::Selection()
{
  pwr += pwr_selection;
}

// ---------------------------------------------------------------------------

void TPower::Standby()
{
  pwr += pwr_standby;
}

// ---------------------------------------------------------------------------

void TPower::Forward()
{
  pwr += pwr_forward;
}

// ---------------------------------------------------------------------------

void TPower::Incoming()
{
  pwr += pwr_incoming;
}

// ---------------------------------------------------------------------------



