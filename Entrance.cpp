#include "Entrance.h"

using namespace std;

Entrance::Entrance(int k, int id, int nsegs){
	int i, electr_or_empl;
	string node_name[10]={"Olympia", "Mandra", "Magoula", "Aspropyrgos", "Gerakas", "Marathonos", "Rafina", "Paiania", "Kantza", "Airport"};
	string s, name;
    stringstream conversion;
    
	conversion << id;
	s=conversion.str();
	name=node_name[rand()%10];
	Node_Name=name+s;
	
	num_of_tolls=rand()%5+k;
	
	num_tolls_employees=0;
	num_electronic_tolls=0;
	
	// create tolls
	tolls_array=new Toll*[num_of_tolls];  
	for(i=0; i < num_of_tolls; i++){
		electr_or_empl=rand()%2;
		if(electr_or_empl==1){
			tolls_array[i]=new Employee(electr_or_empl, k, id, nsegs);   // create Employee toll
			num_tolls_employees++;
		}
		else{
			tolls_array[i]=new Electronic(electr_or_empl, k, id, nsegs);  // create Electronic toll
			num_electronic_tolls++;
		}
	}
	cout  << endl <<  "The Entrance  " << Node_Name << "  was created" << endl << endl;
}

Entrance::~Entrance(){
	cout <<  endl << "The Entrance  " << Node_Name << "  was destroyed" << endl << endl;
	
	// deallocate the tolls
	for(int i=0; i < num_of_tolls; i++){
		delete tolls_array[i];
	}
	delete[] tolls_array;
}

const VEHICLES Entrance::vehicles_entrance_in_the_section(int* num_of_new_vehicles, int current_capacity, int *flag){
	VEHICLES veh2, veh1;
	int i, j, l, num_of_new_veh_elec=0, num_of_new_veh_empl=0, K_elec=0, K_empl=0, temp; 
	
	temp=current_capacity;
	for(i=0; i < num_of_tolls; i++){
		
		// if toll is "employee"
		if(tolls_array[i]->is_employee()==1){
			tolls_array[i]->remove(temp, &num_of_new_veh_empl, &K_empl, &veh1);  // remove vehicles from the current toll
			
			for(j=0; j < num_of_new_veh_empl; j++){  
				veh2.push_back(veh1[j]);         // save the vehicles that are to be added to the segment in the veh2
			}
			
			temp=temp-veh1.size();
			veh1.clear();
		}
		else{ // if toll is "electronic"
			tolls_array[i]->remove(temp, &num_of_new_veh_elec, &K_elec, &veh1);
			
			for(j=0; j < num_of_new_veh_elec; j++){ 
				veh2.push_back(veh1[j]); 
			}
			
			temp=temp-veh1.size();	
			veh1.clear();
		}
		
		// the required number of vehicles has been completed -->> there is no need to carry out unnecessary inspections -> BREAK
        if(temp==0 && current_capacity==veh2.size()){ break; } 
		  
	}
	
	*num_of_new_vehicles=veh2.size();   
	
	// check if the maximum number of K + 2K vehicles crossed the tolls
	int k=tolls_array[0]->get_K();
	if( (K_empl+K_elec) < (k+(2*k)) ){  // if less than the maximum number of K + 2K vehicles has passed -->> Ê--
		for(i=0; i < num_of_tolls; i++){  tolls_array[i]->set_data(-1); }
	}
	else{  // else K++
		*flag=1;
		for(i=0; i < num_of_tolls; i++){  tolls_array[i]->set_data(1); }
	}
	
	cout << "K = "<< tolls_array[0]->get_K() << endl  << endl;
	return veh2;   // Returns vehicles
}

void Entrance::add_random_vehicles(int nsegs, int segment){
	for(int i=0; i < num_of_tolls; i++){
		tolls_array[i]->add(nsegs, segment); // add vehicles in the current toll
	}
}


const VEHICLES Entrance::operate(int* num_of_new_vehicles, int current_capacity, int segment, int nsegs, int* flag){
	int num, random, flag1;
	VEHICLES veh;
	
	cout << "The number of vehicles standing at Entrance " << Node_Name << " : " << get_num_of_vehicles() << endl << endl;  
	
	veh=vehicles_entrance_in_the_section(&num, current_capacity, &flag1);  // returns vehicles that will be added to the segment
	
	*num_of_new_vehicles=num;
	*flag=flag1;
	
	cout << "-- Add new vehicles at the entrance --" << endl << endl;
	random=rand()%1+1;
	for(int i=0; i < random; i++){
		add_random_vehicles(nsegs, segment);  // add random number of vehicles in the tolls
	}
	
	return veh;  // Returns vehicles
}

int Entrance::get_num_of_vehicles(){
	int counter=0;
	for(int i=0; i < num_of_tolls; i++){
		counter=counter+tolls_array[i]->get_num_of_vehicles();
	}
	return counter;
}

void Entrance::print(int num_of_vehicles, int capacity){
	cout <<"Tolls:    ";
	for(int i=0; i < num_of_tolls; i++){
		tolls_array[i]->print();
	}
	cout << "|" << endl << endl << "\t\t\t|	   	  |" << endl << "\t\t\t|	" << num_of_vehicles << " / " << capacity  << "	  |" << endl
	     <<"\t\t\t|		  |" << endl << endl;
}
