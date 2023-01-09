CXXFLAGS = -std=c++11

.PHONY: all
all: client server

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

Distance.o: Distance.cpp Distance.h
	g++ -c Distance.cpp $(CXXFLAGS)

CanberraDistance.o: CanberraDistance.cpp CanberraDistance.h
	g++ -c CanberraDistance.cpp $(CXXFLAGS)

ChebyshevDistance.o: ChebyshevDistance.cpp ChebyshevDistance.h
	g++ -c ChebyshevDistance.cpp $(CXXFLAGS)

EuclideanDistance.o: EuclideanDistance.cpp EuclideanDistance.h
	g++ -c EuclideanDistance.cpp $(CXXFLAGS)

IOClass.o: IOClass.cpp IOClass.h
	g++ -c IOClass.cpp $(CXXFLAGS)

Knn.o: Knn.cpp Knn.h
	g++ -c Knn.cpp $(CXXFLAGS)

MinkowskiDistance.o: MinkowskiDistance.cpp MinkowskiDistance.h
	g++ -c MinkowskiDistance.cpp $(CXXFLAGS)

TaxicabGeometry.o: TaxicabGeometry.cpp TaxicabGeometry.h
	g++ -c TaxicabGeometry.cpp $(CXXFLAGS)

clean:
	rm *.o client.out server.out
