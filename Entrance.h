#pragma once

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstring>
#include <sstream>

#include "Toll.h"

using namespace std;

class Entrance{
	private: 
		string Node_Name;
		int num_tolls_employees;
		int num_electronic_tolls;  
		int num_of_tolls;
		Toll **tolls_array; 
	
	public:
		Entrance(int,int, int);
		~Entrance();
		
		const VEHICLES operate(int*, int, int, int, int*); // Remove & add vehicles
		
		const VEHICLES vehicles_entrance_in_the_section(int*, int, int*);  // Returns vehicles from the entrance
		void add_random_vehicles(int, int);   // add random number of vehicles in the tolls
		int get_num_of_vehicles();
		void print(int, int);
};
