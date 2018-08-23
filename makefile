output:main.o populateDir.o fileAttributes.o functions.h
	g++ main.o populateDir.o -o output

main.o: main.cpp functions.h
	g++ -c main.cpp

populateDir.o:populateDir.cpp fileAttributes.cpp functions.h
	g++ -c populateDir.cpp


