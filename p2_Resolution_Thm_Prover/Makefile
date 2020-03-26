prover: prover.o literal.o clause.o term.o
	g++ prover.o literal.o clause.o term.o -o prover

prover.o: prover.cpp prover.h
	g++ -c prover.cpp

literal.o: literal.cpp literal.h
	g++ -c literal.cpp

clause.o: clause.cpp clause.h
	g++ -c clause.cpp

term.o: term.cpp term.h
	g++ -c term.cpp

clean:
	rm *.o prover
