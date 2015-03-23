Program: Robot.o main.o
	g++ Robot.o main.o -o Program

Robot.o: Robot.h Robot.cpp
	g++ -c Robot.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o Program