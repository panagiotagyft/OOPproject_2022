#include "Segment.h"

using namespace std;

Segment::Segment(int K, int id, int NSegs, int percent):Percent(percent), capacity((rand()%15)+5), segment_serial_number(id){
	int i, seg, random_destination;
    
	no_of_vehicles=rand()%capacity; // random vehicles 
	
	entrance=new Entrance(K,id, NSegs);  // create the entrance
    
    
	for(i=0; i < no_of_vehicles; i++){
		random_destination=(rand()%(NSegs-segment_serial_number))+segment_serial_number; // select random destination
		vehicles_array.push_back(new Vehicle(segment_serial_number,random_destination));  // create the vehicle and add it to the queue
	} 
	
	seg=segment_serial_number+1; 
	
	if(seg==1){ cout<< "The first segment was created." << endl << endl; }
	if(seg==2){ cout<< "The second segment was created." << endl << endl; } 
	if(seg==3){ cout<< "The third segment was created." << endl << endl;}
	if(seg > 3){ cout<< "The "<< seg << "th segment was created." << endl << endl;}	
}

Segment::~Segment(){
	cout << endl  << "Segment was destroyed" << endl;
	VEHICLES::iterator vehicles_arrayIt= vehicles_array.begin();
	
	// first step: deallocate the vehicles
	while(vehicles_arrayIt != vehicles_array.end()){
		delete *vehicles_arrayIt;
		vehicles_arrayIt++;
	}
	vehicles_array.clear();
	
	// Second step: deallocate the entrance
	delete entrance;
}


void Segment::exit(){
	int count=0;
	// Check all vehicles
	for(int i=0; i < no_of_vehicles; i++){
		 // if current vehicle is ready and and has reached its destination -->> removed the car from the motorway
		if(vehicles_array[i]->is_ready()==true && vehicles_array[i]->the_vehicle_arrived_at_its_destination()==true){ 
		    // remove the vehicle
			Vehicle *v=vehicles_array[i];
			vehicles_array.erase(vehicles_array.begin()+i); 
			cout << endl << "Vehicle Exit" << endl;
			delete v;
		
			no_of_vehicles--;      // decrease the number of vehicles in the current segment
			count++;        // counter --->> vehicles exit
            if(!vehicles_array.empty()){ i=-1;}   // checked the vehicles from the beginning
            else{ break;}
		}
	}
	cout << endl << "The number of vehicles that left from the motorway: " << count << endl << endl;
}


void Segment::pass(){
	
	for(int i=0; i < no_of_vehicles; i++){
		// if current vehicle is ready and and has not reached its destination -->> transfer the vehicle to the next segment
		if(vehicles_array[i]->is_ready()==true && vehicles_array[i]->the_vehicle_arrived_at_its_destination()==false){
			// If space is available
			if(next_segment->no_of_vehicles < next_segment->capacity){
				
				// Vehicle is added to the next segment
				next_segment->vehicles_array.push_back(vehicles_array[i]); 
				next_segment->vehicles_array[next_segment->vehicles_array.size()-1]->set_data(next_segment->segment_serial_number);    // data update
				
				// removed the car from the current segment
				vehicles_array.erase(vehicles_array.begin()+i);   
				
				next_segment->no_of_vehicles++;  // increase the number of vehicles in the next segment
				no_of_vehicles--;                // decrease the number of vehicles in the current segment
				if(!vehicles_array.empty()){ i=-1;}   // checked the vehicles from the beginning
                else{ break;}
			}
		}
	}
}

void Segment::enter(int nsegs){
	VEHICLES veh, veh1;
	int num_of_new_vehicles, current_capacity, i, flag1=0, flag2=0, flag=-1, temp1, temp2=0;
	
	temp1=no_of_vehicles;
	
	// if the current segment is not the first --->>> add vehicles from the previous segment
	if(previous_segment!=NULL){ previous_segment->pass(); flag1=1;}   
	
	temp1=no_of_vehicles-temp1;  // number of new vehicles added after pass()
	if(previous_segment!=NULL){ 
		cout << "The number of vehicles that passed from the previous to the next segment :  " << temp1 << endl << endl;
	}
	
	current_capacity=capacity-no_of_vehicles; 

    // If space is available
	if(current_capacity!=0){ 
	    // add vehicles from the entrance
		veh=entrance->operate(&num_of_new_vehicles, current_capacity, segment_serial_number, nsegs, &temp2); 
		cout << endl << "The number of vehicles that passed from the entrance to the next segment :  " << num_of_new_vehicles << endl << endl;
		flag2=1;
	}
    
    // Add vehicles from veh
	if(!veh.empty()){
		for(i=0; i < veh.size(); i++){
			vehicles_array.push_back(veh[i]);
			vehicles_array[vehicles_array.size()-1]->set_data(segment_serial_number);  // set destination status and set the vehicle not to be ready
			no_of_vehicles++;   // increase the number of vehicles
		}
	}
	veh.clear();
	
	// Motorway  advice to road users
	// print notifications
	
	if(flag2==1 && temp2!=1){  // if received vehicles from the entrance && the number of vehicles serviced by the tolls < Ê+2Ê -->> print notification
		cout << "DELAYS in entering the node " << segment_serial_number << endl;
		flag=0;
	}
    
    // if received vehicles from the previous segment && the number of vehicles going to the next segment is less than the ready vehicles -->> print notification
	if(flag1==1 && temp1>0 && temp1 < previous_segment->get_ready_vehicles()){ 
		cout << "DELAYS after node " << segment_serial_number << endl; 
		flag=0;
	}
	
	// else print
	if(flag==-1){
		cout << "OBSERVE the safety distances in the segment after node " << segment_serial_number << endl;
	}
}

void Segment::operate(int nsegs){
	int counter=0;
	
	// Print information for current segment
	cout << "Segment " << segment_serial_number << " information: " << endl 
	     << " 1. The number of vehicles is " << no_of_vehicles << endl 
		 << " 2. Capacity: "<< capacity <<  endl << endl; 
	
	// Call basic functionalities 
	exit();  
	enter(nsegs);
	
	// Print -->> the number of cars in the new status
	cout << endl << "After exit() & enter() the new situation is: Segment " << segment_serial_number 
	     << " ->> the number of vehicles is " << no_of_vehicles << endl << endl; 
	
	// Set -> ready cars for the new simulation cycle
	num_ready_vehicles=(Percent*no_of_vehicles)/100;
	
	cout << "Ready Vehicles:  " << num_ready_vehicles << endl;
	
	for(int i=0; i < no_of_vehicles; i++){ 
		if(vehicles_array[i]->is_ready()==true){ counter++;}  
	}
	
	while(counter < num_ready_vehicles){
		int r=rand()%no_of_vehicles;
		if(vehicles_array[r]->is_ready()==false){
			vehicles_array[r]->be_ready_and_check_destination(true);
			counter++;
		}
	}

	for(int i=0; i < no_of_vehicles; i++){  vehicles_array[i]->print(); }  // optional
	
	cout << "=========================================================================" << endl << endl;
	
	
}

// Set the pointers
void Segment::set_data(Segment &previous, Segment &next){
	if(!(&next)){  next_segment=NULL;  }
	else{ next_segment=&next;}
	
	if(!(&previous)){  previous_segment=NULL;  }
	else{ previous_segment=&previous;}
}


int Segment::get_ready_vehicles(){
	int counter=0;
	// count the ready vehicles
	for(int i=0; i < no_of_vehicles; i++){
		if(vehicles_array[i]->is_ready()==true){ counter++;}
	}
	
	return counter;	  // returns the counter
}
