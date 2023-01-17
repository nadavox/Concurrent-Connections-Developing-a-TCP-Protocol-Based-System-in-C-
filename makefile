CXXFLAGS = -std=c++11

.PHONY: all
all: client server

client: Client.o IOClass/DefaultIO.o IOClass/SocketIO.o IOClass/StandardIO.o
	g++ Client.o DefaultIO.o SocketIO.o StandardIO.o -o client.out $(CXXFLAGS)

server: Server.o Algorithms/Distance.o Algorithms/CanberraDistance.o Algorithms/ChebyshevDistance.o Algorithms/EuclideanDistance.o \
         IOClass/DefaultIO.o IOClass/SocketIO.o IOClass/StandardIO.o Algorithms/Knn.o Algorithms/MinkowskiDistance.o Algorithms/TaxicabGeometry.o Command_pattern/Command.o \
         Command_pattern/UploadCommand.o Command_pattern/SettingsCommand.o Command_pattern/ClassifyCommand.o Command_pattern/DisplayCommand.o \
         Command_pattern/DownloadCommand.o Command_pattern/CLI.o Values.o
	g++ Server.o Distance.o CanberraDistance.o ChebyshevDistance.o EuclideanDistance.o \
         DefaultIO.o SocketIO.o StandardIO.o Knn.o MinkowskiDistance.o TaxicabGeometry.o Command.o \
         UploadCommand.o SettingsCommand.o ClassifyCommand.o DisplayCommand.o \
         DownloadCommand.o CLI.o Values.o -o server.out $(CXXFLAGS)

Client.o: Client.cpp
	g++ -c Client.cpp $(CXXFLAGS)

Server.o: Server.cpp
	g++ -c Server.cpp $(CXXFLAGS)

Algorithms/Distance.o: Algorithms/Distance.cpp
	g++ -c Algorithms/Distance.cpp $(CXXFLAGS)

Algorithms/CanberraDistance.o: Algorithms/CanberraDistance.cpp
	g++ -c Algorithms/CanberraDistance.cpp $(CXXFLAGS)

Algorithms/ChebyshevDistance.o: Algorithms/ChebyshevDistance.cpp
	g++ -c Algorithms/ChebyshevDistance.cpp $(CXXFLAGS)

Algorithms/EuclideanDistance.o: Algorithms/EuclideanDistance.cpp
	g++ -c Algorithms/EuclideanDistance.cpp $(CXXFLAGS)

IOClass/DefaultIO.o: IOClass/DefaultIO.cpp IOClass/DefaultIO.h
	g++ -c IOClass/DefaultIO.cpp $(CXXFLAGS)

IOClass/SocketIO.o: IOClass/SocketIO.cpp IOClass/SocketIO.h
	g++ -c IOClass/SocketIO.cpp $(CXXFLAGS)

IOClass/StandardIO.o: IOClass/StandardIO.cpp IOClass/StandardIO.h
	g++ -c IOClass/StandardIO.cpp $(CXXFLAGS)

Algorithms/Knn.o: Algorithms/Knn.cpp
	g++ -c Algorithms/Knn.cpp $(CXXFLAGS)

Algorithms/MinkowskiDistance.o: Algorithms/MinkowskiDistance.cpp
	g++ -c Algorithms/MinkowskiDistance.cpp $(CXXFLAGS)

Algorithms/TaxicabGeometry.o: Algorithms/TaxicabGeometry.cpp
	g++ -c Algorithms/TaxicabGeometry.cpp $(CXXFLAGS)

Command_pattern/Command.o: Command_pattern/Command.cpp
	g++ -c Command_pattern/Command.cpp $(CXXFLAGS)

Command_pattern/UploadCommand.o: Command_pattern/UploadCommand.cpp
	g++ -c Command_pattern/UploadCommand.cpp $(CXXFLAGS)

Command_pattern/SettingsCommand.o: Command_pattern/SettingsCommand.cpp
	g++ -c Command_pattern/SettingsCommand.cpp $(CXXFLAGS)

Command_pattern/ClassifyCommand.o: Command_pattern/ClassifyCommand.cpp
	g++ -c Command_pattern/ClassifyCommand.cpp $(CXXFLAGS)

Command_pattern/DisplayCommand.o: Command_pattern/DisplayCommand.cpp
	g++ -c Command_pattern/DisplayCommand.cpp $(CXXFLAGS)

Command_pattern/DownloadCommand.o: Command_pattern/DownloadCommand.cpp
	g++ -c Command_pattern/DownloadCommand.cpp $(CXXFLAGS)

Command_pattern/CLI.o: Command_pattern/CLI.cpp
	g++ -c Command_pattern/CLI.cpp $(CXXFLAGS)

Values.o: Values.cpp
	g++ -c Values.cpp $(CXXFLAGS)

clean:
	rm *.o client.out server.out

