#include "Attiki_Odos.h"


using namespace std;

Attiki_Odos::Attiki_Odos(int nSegs, int K, int percent): NSegs(nSegs), no_of_vehicles(0){
	segment_array=new Segment*[NSegs];

	for(int i=0; i < NSegs; i++){
		segment_array[i]=new Segment(K,i, NSegs, percent);  
		no_of_vehicles=no_of_vehicles+segment_array[i]->get_no_of_vehicles();
		no_of_vehicles=no_of_vehicles+segment_array[i]->get_no_of_vehicles_entrance();
	}
	
	// initialize the pointers points to the next/previous segment
	for(int i=0; i < NSegs; i++){
		
		if(i==0){ 	// if current segment is the first --->> there is no previous segment (previous pointer points to NULL)
			Segment *temp= NULL;     
		    segment_array[i]->set_data(*temp, *segment_array[i+1]);
		} 
		else if(i==NSegs-1){ // if current segment is the last --->> there is no next segment (next pointer points to NULL)
			Segment *temp= NULL;
		    segment_array[i]->set_data(*segment_array[i-1], *temp);			
		}
		else{ segment_array[i]->set_data(*segment_array[i-1], *segment_array[i+1]);	}
		
	}

	cout << "Motorway  in operation" << endl << endl;
}

Attiki_Odos::~Attiki_Odos(){
	int i;
	
	cout << "The Attiki Odos was destroyed" << endl << endl;
	
	// deallocate the segments
	for(i=0; i < NSegs; i++){
		delete segment_array[i];
	}
	
	delete[] segment_array;
}


void Attiki_Odos::set_no_of_vehicles(){
	int x=0, y=0;
	for(int i=0; i <NSegs; i++){
		x=x+segment_array[i]->get_no_of_vehicles();   // get the number of vehicles moving in the segment
		
		y=y+segment_array[i]->get_no_of_vehicles_entrance();  // get the number of vehicles at the entrance
	}
	no_of_vehicles=x+y;		
}

void Attiki_Odos::oparate(){ 
    
	for(int j=0; j < NSegs; j++){ segment_array[j]->print();}     // optional: print Attiki Odos 
	
	for(int i=NSegs-1; i >= 0; i--){
	    
		// set the new number of vehicles on the Attiki road   
		set_no_of_vehicles();    
		
		cout << endl << "-----  Attiki Odos: The number of vehicles is " << get_no_of_vehicles() << "  -----" << endl << endl;
		
		segment_array[i]->operate(NSegs);   
	}
}
