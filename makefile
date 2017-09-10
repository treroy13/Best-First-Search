 

all: BestFirstSearch

BestFirstSearch: BestFirstSearch.o
	    g++ -std=c++11 BestFirstSearch.o -o BestFirstSearch

BestFirstSearch.o: BestFirstSearch.cpp
	      g++ -std=c++11 -c BestFirstSearch.cpp

clean:
	rm -f *.o BestFirstSearch 

 
