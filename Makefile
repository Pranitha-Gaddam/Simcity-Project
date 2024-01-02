output: main.o Commercial.o io.o Person.o Persons.o Pollution.o power.o Residential.o Industrial.o
	g++ main.o Commercial.o io.o Person.o Persons.o Pollution.o power.o Residential.o Industrial.o -o simcity

main.o: main.cpp
	g++ -c main.cpp

Commercial.o: Commercial.cpp Commercial.h
	g++ -c Commercial.cpp

io.o: io.cpp io.h
	g++ -c io.cpp

Person.o: Person.cpp Person.h
	g++ -c Person.cpp

Persons.o: Persons.cpp Persons.h
	g++ -c Persons.cpp

Pollution.o: Pollution.cpp Pollution.h
	g++ -c Pollution.cpp

power.o: power.cpp power.h
	g++ -c power.cpp

Residential.o: Residential.cpp Residential.h
	g++ -c Residential.cpp

Industrial.o: Industrial.cpp Industrial.h
	g++ -c Industrial.cpp

clean:
	rm *.o simcity