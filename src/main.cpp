#include <iostream>
#include <cstdlib>
#include "Attiki_Odos.h"

using namespace std;

int main(int argc, char* argv[]){
	int N, NSegs, K, Percent;
	
	if(argc==1 || argc<=4){
		printf("Missing arguments...\n");
		return 1;
	}
	
	srand(time(NULL));
	
	N=atoi(argv[1]);										
	NSegs=atoi(argv[2]);
	K=atoi(argv[3]);
	Percent=atoi(argv[4]);
	
	Attiki_Odos attiki_odos(NSegs, K, Percent);
	
	// Starts the  simulation
	for(int i=0; i < N; i++){ 
		cout << endl << "	LOOP  " << i+1 << endl << "------------------------" << endl << endl;
		attiki_odos.oparate(); 
	}
	
	return 0;
}
