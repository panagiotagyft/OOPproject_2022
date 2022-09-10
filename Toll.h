#pragma once

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "Vehicle.h"

using namespace std;

typedef vector <Vehicle*> VEHICLES;

class Toll{
	private:
		int K;
		int num_of_vehicles;
		int electr_or_empl;
		
    protected:
    	void increase_num_of_vehicles(){ num_of_vehicles++; }
    	void decrease_num_of_vehicles(){ num_of_vehicles--; }
	
	public:
		Toll(int, int);
		virtual ~Toll();
		
		// Basic functionalities 
		virtual void remove(int , int*, int*, VEHICLES*)=0;  
		virtual void add(int, int)=0;                        // add vehicles in the toll
		
		void set_data(int temp){ K=K+temp; }  // increase/decrease K
		int is_employee(){ return electr_or_empl;} 
		int get_K(){ return K; }
		int get_num_of_vehicles(){ return num_of_vehicles;}
		virtual void print()=0;
		
};

class Employee:public Toll{
	private:
		VEHICLES vehicles_empl;
	
	public:
		Employee(int, int, int, int);
		~Employee();
		
		// Basic functionalities 
		void add(int, int);
	    void remove(int , int*, int*, VEHICLES*);
	    
	    void print(){ cout << " | Empl:  " <<  vehicles_empl.size(); }
};

class Electronic:public Toll{
	private:
		VEHICLES vehicles_elec;
	
	public:
		Electronic(int, int, int, int);
		~Electronic();
		
		// Basic functionalities 
		void add(int, int);
		void remove(int , int*, int*, VEHICLES*);	
		
		void print(){	cout << " | Electr:  " <<  vehicles_elec.size(); }
};
