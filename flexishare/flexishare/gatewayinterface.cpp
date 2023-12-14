#include "gatewayinterface.h"

/** This thread transfers flits to the lower electrical layer.
 *  Since the photonic communication comes to an end here , the 
 *  inter pri bit is reset here before sending to electrical router 
**/

void TGatewayInterface::txProcess() // Clock Edge
{
	if (reset.read())
    {
      req_tx.write(0);
	  
	}
  else
    {
		  for(int i=0; i<(TGlobalParams::mesh_dim_x * TGlobalParams::mesh_dim_y)/2; i++)
		  {
			  if( mwmr_data_rx[i]->event())
			  {
				  TFlit received_flit_temp = mwmr_data_rx[i].read();
				  if(received_flit_temp.dst_id == local_id_new)
				  {
					  if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   {
         cout<< sc_time_stamp().to_double()/1000 << " gwi Source_Id --> " <<  received_flit_temp.src_id <<" gwi Destination_Id --> " <<  received_flit_temp.dst_id << endl; 	   
	   }
					  stats.receivedFlit(sc_time_stamp().to_double()/1000, received_flit_temp);
					  flit_tx.write(mwmr_data_rx[i].read());		// passing the flit from cross bar to electircal domain
					  req_tx.write(1);
				  }
				  else
				  {
					  req_tx.write(0);
				  }
			  }
			  
		  }
  }

}

/** This thread recieves  flits from the lower electrical layer and stores it 
 * in the local buffer. Once a flit is pushed in the buffer ,process triggers
 * the photonic transfer process by notifying the reservation process 
**/
void TGatewayInterface::rxProcess() // sensitive -- photonic_to_electrical_tx
{
  if(reset.read())
    { // Clear outputs and indexes of receiving protocol
      ack_rx.write(0);
	  current_level_rx = 0;
	  routed_flits = 0;
      local_drained = 0;
    }
  else
     {

	  if ( (req_rx.read()==1-current_level_rx) && !buffer_local.IsFull() )
	    {
	      TFlit received_flit = flit_rx.read();

	      if(TGlobalParams::verbose_mode > VERBOSE_OFF)
		{
		  cout << sc_time_stamp().to_double()/1000 << ": GWI["<< local_id_new <<"], Input, Received flit: " << received_flit << endl;
		}

	      // Store the incoming flit in the circular buffer
	      buffer_local.Push(received_flit);            

	      // Negate the old value for Alternating Bit Protocol (ABP)
	      current_level_rx = 1-current_level_rx;
	    }
	  ack_rx.write(current_level_rx);
	
    }

    
}
/**--------------------------------------------------------------------------
 * This module writes on crossbar in MWSR fashion and trainsmits data to its destination 
 * based on the decision taken by arbiter 
 * 
---------------------------------------------------------------------------*/
void TGatewayInterface::mwmr_tx_data() // sensitive - Clock
{
  if(reset.read())
  {
	  ack_txc_arbiter.write(1);
	  arbiter_current_level_tx =0;
  }
  
  else if(!reset.read()  && !buffer_local.IsEmpty() && ack_tx_arbiter.read() == 1)
  {
       TFlit flit = buffer_local.Front();   //sending head flit to the channel assigned by the arbiter
       mwmr_data_tx[mwmr_channel_no.read()].write(flit);
       //stats.receivedFlit(sc_time_stamp().to_double()/1000, flit);
	   if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   {
         cout<< sc_time_stamp().to_double()/1000  << "MWMR channel no. " << mwmr_channel_no.read() << " gwi Source_Id --> " <<  flit.src_id <<" gwi Destination_Id --> " <<  flit.dst_id << endl; 	   
	   }
	   if(flit.flit_type == FLIT_TYPE_HEAD) 
	   { 
		   arbiter_current_level_tx = 1;
		   if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   {
         cout<< sc_time_stamp().to_double()/1000  << "Source_Id --> " <<  flit.src_id <<" Destination_Id --> " <<  flit.dst_id << endl; 	   
	   }	  
	   }
	   else
	   {
		   arbiter_current_level_tx = 0;
	   }
	   buffer_local.Pop();
	   ack_txc_arbiter.write(arbiter_current_level_tx);
	   	  
  }	
}

///**--------------------------------------------------------------------------
 //* This module requests arbiter to grant access to arbiter by sending its head flit
 //* 
//---------------------------------------------------------------------------*/
void TGatewayInterface::arbiter_req() // sensitive - Clock
{
  if(reset.read())
  {
	  
  }
  
  else if(!reset.read() && ack_tx_arbiter.read() != 1 && !buffer_local.IsEmpty() && flit_rx->event() )
  {
       TFlit flit = buffer_local.Front();
       // sending head flit to arbiter 
	   if(flit.flit_type == FLIT_TYPE_HEAD) 
	   { 
		  req_tx_arbiter.write(flit);
		   if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   {
         cout<< sc_time_stamp().to_double()/1000  << "Source_Id --> " <<  flit.src_id <<" Head_Destination_Id --> " <<  flit.dst_id << endl; 	   
	   }
		   
	   }
	   	  
  }	
}

void TGatewayInterface::bufferMonitor()
{
  //if (reset.read())
  //{
    //free_slots.write(buffer_local.GetMaxBufferSize());
  //}
  //else
  //{
     //// update current input buffers level to Hub
    //free_slots.write(buffer_local.getCurrentFreeSlots());

    //}
  }

//---------------------------------------------------------------------------
unsigned long TGatewayInterface::getRoutedFlits()
{ 
  //return routed_flits; 
}
