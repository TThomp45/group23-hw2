CC=g++
DEPS = loan.h

all: main.o loan.o
	$(CC) -std=c++11 main.o loan.o -o a.out

main.o: main.cpp $(DEPS)
	$(CC) -c -std=c++11 main.cpp

loan.o: loan.cpp $(DEPS)
	$(CC) -c -std=c++11 loan.cpp

clean:
	rm -f *.o a.out
