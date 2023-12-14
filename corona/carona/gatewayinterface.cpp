#include "gatewayinterface.h"

//--------------------------DONE HERE----------------------------------------

void TGatewayInterface::configure(const int _id, const int _nearest_gateway_id,
                                  std::map<int, int>  _gateway_map)
{
  local_id           = _id;
  nearest_gateway_id = _nearest_gateway_id;
  gateway_map        = _gateway_map;
  //cout <<  nearest_gateway_id  << " < -- nearest_gateway_id  local_id -->  " << local_id << endl;
}

//--------------------------DONE HERE----------------------------------------

void TGatewayInterface::test_ports()
{
 
}

/** This thread recieves  flits from the lower electrical layer and stores it 
 * in the local buffer. Once a flit is pushed in the buffer ,process triggers
 * the photonic transfer process by notifying the reservation process 
**/

void TGatewayInterface::rxProcess() // Clock Edge
{
  //if(reset.read())
    //{
	  //ack_rx.write(0);
	  //current_level_rx = 0;
	  
    //}
  //else
    //{
        //if(TGlobalParams::verbose_mode > VERBOSE_OFF )//&& received_flit.flit_type == FLIT_TYPE_HEAD)
		//{
		  //cout << sc_time_stamp().to_double()/1000 
		  //<< ": Router["<< local_id <<"],Received flit - Gateway Before: " << !buffer[LOCAL_TX_INDEX] -> IsFull() << 
		   //"  current_level_rx --> " <<  current_level_rx << " req_rx.read() --> " << req_rx.read() << endl;
		//}		
	  //if ( (req_rx.read()==1-current_level_rx) && !buffer[LOCAL_TX_INDEX] -> IsFull())
	    //{
	      //TFlit received_flit = flit_rx.read();

        //if(TGlobalParams::verbose_mode > VERBOSE_OFF )//&& received_flit.flit_type == FLIT_TYPE_HEAD)
		//{
		  //cout << sc_time_stamp().to_double()/1000 
		  //<< ": Router["<< local_id <<"],Received flit - GI: " << received_flit.wdm <<  " First tag " <<  received_flit << endl;
		//}

	      //// Store the incoming flit in the circular buffer
	      //buffer[LOCAL_TX_INDEX] -> Push(received_flit);            

	      //// Negate the old value for Alternating Bit Protocol (ABP)
	      //current_level_rx =  1-current_level_rx;

	      //// Incoming flit - Reserve a channel only with the header flit.
	      //if (received_flit.flit_type==FLIT_TYPE_HEAD)
	      //{
               //TFlit flit = buffer[LOCAL_TX_INDEX] -> Front();
			   ////cout << flit  << "  <-- TIME CHECK -->   "  << received_flit << endl;
			   //reservation_req.notify(ONE_CYCLE, SC_NS); // Build an event queue here - Check back here
		  //}
	      
	    //}
 	  //ack_rx.write(current_level_rx);
	//}
}

/** This thread transfers flits to the lower electrical layer.
 *  Since the photonic communication comes to an end here , the 
 *  inter pri bit is reset here before sending to electrical router 
**/

void TGatewayInterface::txProcess() // sensitive -- photonic_to_electrical_tx
{
  //if(reset.read())
  //{
	 //req_tx.write(0);
	 //current_level_tx = 0;
  //}
  //else 
  //{
         //if(TGlobalParams::verbose_mode > VERBOSE_OFF && buffer[GLOBAL_TX_INDEX] -> IsEmpty())
	     //{
               //cout << sc_time_stamp().to_double()/1000 
			       //<< ": Router Forward[" << local_id 
			       //<< "], flit  - GI :  Ninth Srinivas " << endl;
		 //}	  
    //if ( !buffer[GLOBAL_TX_INDEX] -> IsEmpty() )
    //{
	  //TFlit flit = buffer[GLOBAL_TX_INDEX] -> Front();
         //if(TGlobalParams::verbose_mode > VERBOSE_OFF && current_level_tx != ack_tx.read())
	     //{
               //cout << sc_time_stamp().to_double()/1000 
			       //<< ": Router Forward[" << local_id 
			       //<< "], flit  - GI : " << flit <<  " Ninth before  " << endl;
		 //}
	  
	  //if ( current_level_tx == ack_tx.read() )
	  //{
		 ////now that the inter pri transfer is coming to end, 
		 ////reset the inter pri flag
		 //flit.inter_pri = 0; // check back here
	     //flit_tx.write(flit);
	     //current_level_tx = 1 - current_level_tx;
	     //req_tx.write(current_level_tx);
         //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	     //{
               //cout << sc_time_stamp().to_double()/1000 
			       //<< ": Router Forward[" << local_id 
			       //<< "], flit  - GI : " << flit <<  " Ninth tag " <<  current_level_tx << endl;
		 //}	     
	     //buffer[GLOBAL_TX_INDEX] -> Pop();
	  //}
    //}
  //}
    
}

/*--------------------------------------------------------------------------
Changes to be made in this function - Done
**** Cannot reserve next request before the first item is popped out *****
* Reason for serialization of requests is : 
* Cannot access the second element directly without popping out the first one
---------------------------------------------------------------------------*/
//void TGatewayInterface::swmr_tx_reserve() // sensitive to "reservation_req" event
//{
	  //// Checking "safe_to_reserve" makes sure that there can be no outstanding 
	  //// requests for data transfers
	  //if ( !buffer[LOCAL_TX_INDEX] -> IsEmpty() && safe_to_reserve)
	  //{
		//TFlit flit = buffer[LOCAL_TX_INDEX] -> Front();
		//swmr_tx[0].write((sc_uint<2>)gateway_map.find(flit.nearest_gateway_id) -> second); 
		//if(TGlobalParams::verbose_mode > VERBOSE_OFF)
		//{	
		  //cout << sc_time_stamp().to_double()/1000 << " self local_id --> " <<  local_id << " nearest local id -->  "  << 
		  //gateway_map.find(flit.nearest_gateway_id) -> second << " flit.(sc_uint<2>) -->"
		  //<< flit.nearest_gateway_id << "   " <<  flit <<  " Second tag " << endl;
	    //}
		
		//safe_to_reserve = 0;
	  //}
//}

///*---------------------------------------------------------------------------
//Changes to be made in this function
//* Implement round robin - Done
//* More of cyclic arbitration with no mercy to non-requesters
//* Check for buffer space availability - Enough space for an entire sequence - Not just HEADER
//---------------------------------------------------------------------------*/

//void TGatewayInterface::swmr_tx_reserve_ack() // Sensitivity - Clock edge
//{
	//if(reset)
	//{
	//}
	//else
	//{
	//if(prev_winner == 1 && reserve_req_queue[prev_winner] == RESET_REQ_QUEUE) prev_winner++;
	//else if(prev_winner == 2 && reserve_req_queue[prev_winner] == RESET_REQ_QUEUE) prev_winner = 0;

	//for(int i= prev_winner; i < reserve_req_queue.size(); i++) 
	//{  
       //if((local_id == reserve_req_queue[i]) && // comparing the wrong nearest gateway id - Not anymore
       //!buffer[GLOBAL_TX_INDEX] -> IsFull())	
       //{
		  //req_source_id = (i < local_id) ? i : i + 1;
		  //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
		  //{	
		    //cout<< sc_time_stamp().to_double()/1000  << "swmr_tx_reserve_ack --> " <<  reserve_req_queue[i] << 
		    //"  req_source_id --> " << req_source_id << "  self local_id " << local_id <<  " Fourth tag " << endl;
		  //}
  		  //swmr_tx[1].write(req_source_id);
  		  //prev_winner = i ;
  		  //reserve_req_queue[i] = RESET_REQ_QUEUE;
  		  //break;
	   //}
	//}
	//prev_winner =  (prev_winner == reserve_req_queue.size() - 1) ? 0 : prev_winner++; 
    //}
//}

/*--------------------------------------------------------------------------
 * 
 * 
---------------------------------------------------------------------------*/
//void TGatewayInterface::swmr_tx_data() // sensitive - Clock
//{
  //if(reset)
  //{
  //}
  
  //else if(!reset.read() && safe_to_send && !buffer[LOCAL_TX_INDEX]-> IsEmpty() )
  //{
       //TFlit flit = buffer[LOCAL_TX_INDEX] -> Front();
	   //swmr_data_tx.write(flit);
	   //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   //{
         //cout<< sc_time_stamp().to_double()/1000  << " local_id --> " <<  local_id <<
         //" nearest_gateway_id -->  "  << nearest_gateway_id 
         //<< " swmr_tx_data -->" << flit << "  Sixth tag " << endl; 	   
	   //}
	   //if(flit.flit_type == FLIT_TYPE_TAIL) 
	   //{ 
		   //safe_to_reserve = 1;
		   //safe_to_send    = 0;	  
	   //}
	   //buffer[LOCAL_TX_INDEX] -> Pop();
	   
	  
	  
  //}	
//}


///*---------------------------------------------------------------------------
//Changes to be made in this function - Nothing in the first review
//* But with second look , it seems that I have to transfer the recieved flit to 
//* locally attached electrical router - Done
//---------------------------------------------------------------------------*/
//void TGatewayInterface::swmr_tx_data_ack()
//{
	
    //for(int i= 0; i < data_ack_queue.size(); i++) 
	//{  
       //if(nearest_gateway_id == data_ack_queue[i])
       //{
		  //req_source_id = (i < local_id) ? i : i + 1;
  		  //swmr_tx[2].write(req_source_id);
  		  //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
		  //{
            //cout<< sc_time_stamp().to_double()/1000  << " local_id --> " 
            //<<  local_id << " nearest_gateway_id -->  "  << nearest_gateway_id 
            //<< " swmr_tx_data_ack[i].read() -->" << req_source_id << " 8th tag "<< endl; 
		  //}
          //data_ack_queue[i] = RESET_REQ_QUEUE;
	   //}
	//}
	//photonic_to_electrical_tx.notify();
//}

///*---------------------------------------------------------------------------
//Changes to be made in this function - Nothing
//---------------------------------------------------------------------------*/
//void TGatewayInterface::swmr_rx_reserve()
//{
  
      //for( unsigned i= 0; i<swmr_reservation_rx.size(); i++ )
	  //{
	    //if( swmr_reservation_rx[i]->event() )
	    //{
		  //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
		  //{
            //cout << sc_time_stamp().to_double()/1000  << " local_id --> " <<  local_id 
            //<< " nearest_gateway_id -->  "  << nearest_gateway_id 
            //<< " swmr_rx_reserve -->" << swmr_reservation_rx[i].read() <<  "  Third tag " << endl;
	      //}
		  //reserve_req_queue[i] = (swmr_reservation_rx[i].read());  
        //}
      //}
    ////reservation_ack.notify();
//}


///*---------------------------------------------------------------------------
//Changes to be made in this function -
//* Let know tx_reserve that it can now safely pass on next request
//---------------------------------------------------------------------------*/
//void TGatewayInterface::swmr_rx_reserve_ack() // swmr_reservation_ack_rx signal
//{
    //for( unsigned i= 0; i<swmr_reservation_ack_rx.size(); i++ )
	//if( swmr_reservation_ack_rx[i]->event() && local_id ==  swmr_reservation_ack_rx[i].read())
	//{
       //TFlit flit = buffer[LOCAL_TX_INDEX] -> Front();
	   //swmr_data_tx.write(flit);
	   //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	   //{
         //cout<< sc_time_stamp().to_double()/1000  << " local_id --> " <<  local_id <<
         //" nearest_gateway_id -->  "  << nearest_gateway_id 
         //<< " swmr_rx_reserve_ack -->" << flit <<  "  Fifth tag " << endl;
	   //}
	   //buffer[LOCAL_TX_INDEX] -> Pop();
	   //safe_to_send = 1;
    //}
//}

///*---------------------------------------------------------------------------
//Changes to be made in this function -
//* Receive the data and push inside the second buffer
//* Done
//---------------------------------------------------------------------------*/
//void TGatewayInterface::swmr_rx_data() // Sensitive -- swmr_data_rx
//{
    //for( unsigned i= 0; i<swmr_data_rx.size(); i++ )
    //{ 
	//if( swmr_data_rx[i]->event() )
	//{
       //TFlit received_flit = swmr_data_rx[i].read();
     	 //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	     //{
		   
		   //cout << sc_time_stamp().to_double()/1000  << " local_id --> " <<  local_id 
		   //<< " nearest_gateway_id -->  "  << nearest_gateway_id 
           //<< " swmr_rx_data -->" << received_flit << " Seventh Tag "<< !buffer[GLOBAL_TX_INDEX] -> IsFull() << endl; 
	     //}       
       //if(nearest_gateway_id == (int) received_flit.nearest_gateway_id
       //&& !buffer[GLOBAL_TX_INDEX] -> IsFull())
       //{
     	 //if(TGlobalParams::verbose_mode > VERBOSE_OFF)
	     //{
		   
		   //cout << sc_time_stamp().to_double()/1000  << " local_id --> " <<  local_id 
		   //<< " nearest_gateway_id -->  "  << nearest_gateway_id 
           //<< " swmr_rx_data -->" << received_flit << " Seventh Tag "<< endl; 
	     //}
		   //data_ack_queue[i] = received_flit.nearest_gateway_id;
           //buffer[GLOBAL_TX_INDEX] -> Push(received_flit);
	   //}
    //}
    //}
    //data_ack.notify();
//}

//-----------------------------------------------------------------------------------

void TGatewayInterface::swmr_rx_dt_ack()
{
	
}

//---------------------------------------------------------------------------
