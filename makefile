CXXFLAGS = -std=c++11

.PHONY: all
all: client IOClass

client: Client.o IOClass.o
	g++ Client.o IOClass.o  -o client.out $(CXXFLAGS)

server: Server.o Distance.o CanberraDistance.o ChebyshevDistance.o EuclideanDistance.o\
          IOClass.o Knn.o MinkowskiDistance.o TaxicabGeometry.o
	g++ Server.o Distance.o CanberraDistance.o ChebyshevDistance.o EuclideanDistance.o\
          IOClass.o Knn.o MinkowskiDistance.o TaxicabGeometry.o -o server.out $(CXXFLAGS)

Client.o: Client.cpp
	g++ -c Client.cpp $(CXXFLAGS)

Server.o: Server.cpp
	g++ -c Server.cpp $(CXXFLAGS)

Distance.o: Algorithms Algorithms
	g++ -c Distance.cpp $(CXXFLAGS)

CanberraDistance.o: Algorithms Algorithms
	g++ -c CanberraDistance.cpp $(CXXFLAGS)

ChebyshevDistance.o: Algorithms Algorithms
	g++ -c ChebyshevDistance.cpp $(CXXFLAGS)

EuclideanDistance.o: Algorithms Algorithms
	g++ -c EuclideanDistance.cpp $(CXXFLAGS)

IOClass.o: IOClass/IOClass.cpp IOClass/IOClass.h
	g++ -c IOClass.cpp $(CXXFLAGS)

Knn.o: Algorithms Algorithms
	g++ -c Knn.cpp $(CXXFLAGS)

MinkowskiDistance.o: Algorithms Algorithms
	g++ -c MinkowskiDistance.cpp $(CXXFLAGS)

TaxicabGeometry.o: Algorithms Algorithms
	g++ -c TaxicabGeometry.cpp $(CXXFLAGS)

clean:
	rm *.o client.out server.out
