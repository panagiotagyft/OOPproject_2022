#include "Toll.h"

using namespace std;

Toll::Toll(int x, int k): K(k), electr_or_empl(x), num_of_vehicles(0){ }

Toll::~Toll(){ }

Employee::Employee(int electr_or_empl, int K, int entr, int nsegs):Toll(electr_or_empl, K){
	int random;
	random=(rand()%K)+2;
	
	for(int i=0; i < random; i++){
		int random_destination=(rand()%(nsegs-entr))+entr; // select random destination
		vehicles_empl.push_back(new Vehicle(entr,random_destination));  // create the vehicle and add it to the queue
		increase_num_of_vehicles();
	}
	cout << "The Toll with Employee was created" << endl << endl;
}

Employee::~Employee(){
	cout <<  endl << "The Toll with Employee was destroyed" <<  endl;
	
	// deallocate the vehicles
	VEHICLES::iterator vehicles_emplIt= vehicles_empl.begin();
	while(vehicles_emplIt != vehicles_empl.end()){
		delete *vehicles_emplIt;
		vehicles_emplIt++;
	}
	vehicles_empl.clear();
	
}

Electronic::Electronic(int electr_or_empl, int K, int entr, int nsegs):Toll(electr_or_empl, K){
	int random;
	random=(rand()%K)+2;
	
	for(int i=0; i < random; i++){
		int random_destination=(rand()%(nsegs-entr))+entr; // select random destination
		vehicles_elec.push_back(new Vehicle(entr,random_destination));   // create the vehicle and add it to the queue
		increase_num_of_vehicles();
	}
	cout << "The Electronic Toll was created" << endl <<  endl;
}

Electronic::~Electronic(){
	cout <<  endl << "The Electronic Toll was destroyed" <<  endl;
	
	// deallocate the vehicles
	VEHICLES::iterator vehicles_elecIt= vehicles_elec.begin();
	while(vehicles_elecIt != vehicles_elec.end()){
		delete *vehicles_elecIt;
		vehicles_elecIt++;
	}
	vehicles_elec.clear();
}

//..............................................        Employees         ...........................................................

void Employee::remove(int current_capacity, int *num_of_new_vehicles, int* temp_k, VEHICLES* veh1){
	VEHICLES veh;
	int i, k=get_K();
	int x=*temp_k; 

	for(i=0; i < vehicles_empl.size(); i++){
		
		// if the number of vehicles < K  and there is free space. Else -->> break!
		if(x < k && veh.size() < current_capacity){
			veh.push_back(vehicles_empl[i]);
			x++;
			vehicles_empl.erase(vehicles_empl.begin()+i);
			decrease_num_of_vehicles();     // decrase the number of vehicles in the current toll
			if(!vehicles_empl.empty()){ i=-1;}  // checked the vehicles from the beginning	
		}
		else{ break; }
	}
	*temp_k=x;
	*num_of_new_vehicles=veh.size();
	*veh1=veh;
	veh.clear();
}

void Employee::add(int nsegs, int segment){
	int d=nsegs-segment;
	
	int r=rand()%6+1;
	for(int i=0; i < r; i++){
		int random_destination=(rand()%d)+segment;     // select random destination
		vehicles_empl.push_back(new Vehicle(segment,random_destination));    // create the vehicle and add it to the queue
		increase_num_of_vehicles();    // increase number of vehicles in the current toll
	}	
}

//..............................................        Ålectronic         ...........................................................

void Electronic::remove(int current_capacity, int* num_of_new_vehicles, int* temp_k, VEHICLES* veh1) {
	VEHICLES veh;
	int k=2*get_K();
	int x=*temp_k;

	for(int i=0; i < vehicles_elec.size(); i++){
		
		// if the number of vehicles < 2K  and there is free space. Else -->> break!
		if(x < k && veh.size() < current_capacity){  
			veh.push_back(vehicles_elec[i]); 
			x++;
			vehicles_elec.erase(vehicles_elec.begin()+i);
			decrease_num_of_vehicles();    // decrase the number of vehicles in the current toll
			if(!vehicles_elec.empty()){ i=-1;}  // checked the vehicles from the beginning	
		}
		else{ break; }
	}
	*temp_k=x;
	*num_of_new_vehicles=veh.size();
	*veh1=veh;
	veh.clear();
}

void Electronic::add(int nsegs, int segment){
    int d=nsegs-segment;
    
	int r=rand()%6+1;
    for(int i=0; i < r; i++){
    	int random_destination=(rand()%d)+segment;    // select random destination
		vehicles_elec.push_back(new Vehicle(segment,random_destination));  // create the vehicle and add it to the queue
		increase_num_of_vehicles();   // increase number of vehicles in the current toll
	}
}
