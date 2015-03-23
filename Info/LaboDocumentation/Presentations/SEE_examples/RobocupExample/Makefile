
Program: main.o Robot.o Manager.o Point.o
	g++ main.o Robot.o Manager.o Point.o -o Program

main.o: main.cpp
	g++ -c main.cpp

Robot.o: Robot.cpp
	g++ -c Robot.cpp

Manager.o: Manager.cpp
	g++ -c Manager.cpp

Point.o: Point.cpp
	g++ -c Point.cpp

clean:
	rm -f *.o Program