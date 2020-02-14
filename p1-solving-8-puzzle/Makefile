p1: main.o board.o search.o
	g++ main.o board.o search.o -o p1

main.o: main.cpp main.h
	g++ -c main.cpp

board.o: board.cpp board.h
	g++ -c board.cpp

search.o: search.cpp search.h
	g++ -c search.cpp

clean:
	rm *.o p1