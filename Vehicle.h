#pragma once

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;


class Vehicle{
	private:
		bool ready;
		bool destination;
		int output_node;
		int current_segment;
	  
	public:
		Vehicle(int,int);
	    ~Vehicle();
		
		bool is_ready(){ return ready;}
		bool the_vehicle_arrived_at_its_destination(){ return destination; }
		void be_ready_and_check_destination(bool);  
		void set_data(int);   // set current segment , destination, ready=false
		void print(){
			cout << "Exit:  " << output_node 
			     <<"	Current_Segment:  " << current_segment 
				 << "	Ready:  " << ready 
				 << "	Destination:  " << destination << endl ;
		}
};
