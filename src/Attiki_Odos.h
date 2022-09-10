#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Segment.h"

class Attiki_Odos{
	private:
		int NSegs;  	    // Number of segments
		int no_of_vehicles;    //  Number of vehicles
		Segment** segment_array;  
	
	public:
		Attiki_Odos(int,int,int);
		~Attiki_Odos();
    	
		void oparate();	
		
		int get_no_of_vehicles(){ return no_of_vehicles;} 
        void set_no_of_vehicles();     // set the current number of vehicles
};
