all: stringparser

stringparser: stringparser.cpp stackstring.o ulliststr.o
	g++ -g -Wall stringparser.cpp stackstring.o ulliststr.o -o stringparser

stackstring.o: stackstring.h stackstring.cpp
	g++ -g -Wall -c stackstring.cpp -o stackstring.o

ulliststr.o: ulliststr.h ulliststr.cpp
	g++ -g -Wall -c ulliststr.cpp -o ulliststr.o