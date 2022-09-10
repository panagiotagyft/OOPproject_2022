#include "Vehicle.h"

typedef vector <Vehicle*> VEHICLES;   // Vehicle*: definition of class Vehicles

using namespace std;

Vehicle::Vehicle(int current_seg, int exit):current_segment(current_seg), output_node(exit){
	
	if(current_segment==output_node){ destination=true; }   // the vehicle arrived at its destination 
	else{ destination=false; }  // the vehicle did not reach its destination
	
	ready=false;
	
	cout << "The vehicle was created" << endl;
}

Vehicle::~Vehicle(){
	cout << "The vehicle was destroyed" << endl;
}

void Vehicle::be_ready_and_check_destination(bool temp){
	ready=temp; // ready or not
	if(output_node==current_segment){ destination=true;}   // the vehicle arrived at its destination
	else{ destination=false;}      // the vehicle did not reach its destination
}

void Vehicle::set_data(int segment){
	current_segment=segment;    // set current segment 
	be_ready_and_check_destination(false);   // is not ready
} 
