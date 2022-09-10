main : main.o Attiki_Odos.o Segment.o Entrance.o Toll.o Vehicle.o
	g++ main.o Attiki_Odos.o Segment.o Entrance.o Toll.o Vehicle.o -o main

main.o :main.cpp Attiki_Odos.h 
	g++ -c main.cpp

Attiki_Odos.o :Attiki_Odos.cpp Segment.h
	g++ -c Attiki_Odos.cpp

Segment.o : Segment.cpp Entrance.h Vehicle.h
	g++ -c Segment.cpp

Entrance.o : Entrance.cpp Toll.h
	g++ -c Entrance.cpp

Toll.o : Toll.cpp Vehicle.h
	g++ -c Toll.cpp


Vehicle.o : Vehicle.cpp 
	g++ -c Vehicle.cpp

clean:
	rm  main main.o Attiki_Odos.o Segment.o Entrance.o Toll.o Vehicle.o 
