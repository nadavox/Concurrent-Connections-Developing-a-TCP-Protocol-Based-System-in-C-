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

Distance.o: algorithm/Distance.cpp algorithm/Distance.h
	g++ -c Distance.cpp $(CXXFLAGS)

CanberraDistance.o: algorithm/CanberraDistance.cpp algorithm/CanberraDistance.h
	g++ -c CanberraDistance.cpp $(CXXFLAGS)

ChebyshevDistance.o: algorithm/ChebyshevDistance.cpp algorithm/ChebyshevDistance.h
	g++ -c ChebyshevDistance.cpp $(CXXFLAGS)

EuclideanDistance.o: algorithm/EuclideanDistance.cpp algorithm/EuclideanDistance.h
	g++ -c EuclideanDistance.cpp $(CXXFLAGS)

IOClass.o: IOClass/IOClass.cpp IOClass/IOClass.h
	g++ -c IOClass.cpp $(CXXFLAGS)

Knn.o: algorithm/Knn.cpp algorithm/Knn.h
	g++ -c Knn.cpp $(CXXFLAGS)

MinkowskiDistance.o: algorithm/MinkowskiDistance.cpp algorithm/MinkowskiDistance.h
	g++ -c MinkowskiDistance.cpp $(CXXFLAGS)

TaxicabGeometry.o: algorithm/TaxicabGeometry.cpp algorithm/TaxicabGeometry.h
	g++ -c TaxicabGeometry.cpp $(CXXFLAGS)

clean:
	rm *.o client.out server.out
