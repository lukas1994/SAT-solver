
SRC=$(wildcard *.cpp)

all:
	g++ -o out -g -std=c++11 -Wall -pedantic $(SRC)

clean:
	rm -f *.o
	rm out