#pragma once

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "Entrance.h"
#include "Vehicle.h"

using namespace std;

typedef vector <Vehicle*> VEHICLES;   // Vehicle*: definition of class Vehicle

class Segment{
	private:
		int no_of_vehicles;   //  Number of vehicles
		int capacity;   	  
		int Percent;   		  // percent -->> Ready Vehicles
		int num_ready_vehicles; 	
		int segment_serial_number;  
		Entrance *entrance;  		
		VEHICLES vehicles_array; 	
		Segment* next_segment;       // pointer points to the next segment 
		Segment* previous_segment;   // pointer points to the previous segment 
    
	public:
		Segment(int,int,int,int);
		~Segment();	
		
		// Basic functionalities 
		void enter(int);
		void exit();
		void pass();
		void operate(int);
		
		void set_data(Segment &, Segment &);     // initialize pointers (next & previous)
		int get_ready_vehicles();
		int get_no_of_vehicles(){ return no_of_vehicles;}
		int get_no_of_vehicles_entrance(){ return entrance->get_num_of_vehicles(); }
		void print(){ entrance->print(no_of_vehicles, capacity); }
};
