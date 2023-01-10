cmake_minimum_required(VERSION 3.20)
project(AdvancedProgramingPart4)

set(CMAKE_BUILD_TYPE Debug)

add_executable(AdvancedProgramingPart4_Client Client.cpp IOClass/IOClass.cpp
        IOClass/IOClass.h IOClass/DefaultIO.cpp IOClass/DefaultIO.h IOClass/StandardIO.cpp
        IOClass/StandardIO.h IOClass/SocketIO.cpp IOClass/SocketIO.h IOClass/FileIO.cpp
        IOClass/FileIO.h Values.cpp Values.h)

add_executable(AdvancedProgramingPart4_Server Server.cpp Algorithms/Distance.cpp Algorithms/Distance.h
        Algorithms/CanberraDistance.cpp Algorithms/CanberraDistance.h
        Algorithms/ChebyshevDistance.cpp Algorithms/ChebyshevDistance.h Algorithms/EuclideanDistance.cpp
        Algorithms/EuclideanDistance.h Algorithms/MinkowskiDistance.cpp Algorithms/MinkowskiDistance.h
        Algorithms/TaxicabGeometry.cpp Algorithms/TaxicabGeometry.h Algorithms/Knn.cpp
        Algorithms/Knn.h IOClass/IOClass.cpp
        IOClass/IOClass.h Command_pattern/Command.cpp Command_pattern/Command.h Command_pattern/UploadCommand.cpp Command_pattern/UploadCommand.h
        Command_pattern/SettingsCommand.cpp Command_pattern/SettingsCommand.h Command_pattern/ClassifyCommand.cpp Command_pattern/ClassifyCommand.h
        Command_pattern/DisplayCommand.cpp Command_pattern/DisplayCommand.h Command_pattern/DownloadCommand.cpp Command_pattern/DownloadCommand.h
        Command_pattern/ExitCommand.cpp Command_pattern/ExitCommand.h Command_pattern/CLI.cpp Command_pattern/CLI.h Values.cpp Values.h)