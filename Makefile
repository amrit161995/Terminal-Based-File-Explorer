output: main.o cursor.o list.o command_mode.o
	g++ main.o cursor.o list.o command_mode.o -o output
list.o:list.cpp list.h
	g++ -c list.cpp
command.o:command_mode.cpp command_mode.h list.o list.h
	g++ -c command_mode.cpp
cursor.o: cursor.cpp cursor.h list.o command.o
	g++ -c cursor.cpp 
main.o: main.cpp cursor.o command_mode.o
	g++ -c main.cpp
clean:
	-rm -f *.o
