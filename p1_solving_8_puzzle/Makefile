p1: main.o board.o search.o minmax.o tree.o
	g++ main.o board.o search.o minmax.o tree.o -o p1

main.o: main.cpp main.h
	g++ -c main.cpp

board.o: board.cpp board.h
	g++ -c board.cpp

search.o: search.cpp search.h
	g++ -c search.cpp

minmax.o: minmax.cpp minmax.h
	g++ -c minmax.cpp

tree.o: tree.cpp tree.h
	g++ -c tree.cpp

clean:
	rm *.o p1