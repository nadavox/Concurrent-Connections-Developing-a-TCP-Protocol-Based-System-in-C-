cmake_minimum_required(VERSION 3.20)
project(AdvancedProgramingPart3)

set(CMAKE_BUILD_TYPE Debug)

add_executable(AdvancedProgramingPart3_Client Client.cpp IOClass/IOClass.cpp IOClass/IOClass.h)

add_executable(AdvancedProgramingPart3_Server Server.cpp Algorithms/Distance.cpp Algorithms/Distance.h
        Algorithms/CanberraDistance.cpp Algorithms/CanberraDistance.h
        Algorithms/ChebyshevDistance.cpp Algorithms/ChebyshevDistance.h Algorithms/EuclideanDistance.cpp
        Algorithms/EuclideanDistance.h Algorithms/MinkowskiDistance.cpp Algorithms/MinkowskiDistance.h
        Algorithms/TaxicabGeometry.cpp Algorithms/TaxicabGeometry.h Algorithms/Knn.cpp
        Algorithms/Knn.h IOClass/IOClass.cpp
        IOClass/IOClass.h Command.cpp Command.h UploadCommand.cpp UploadCommand.h
        SettingsCommand.cpp SettingsCommand.h ClassifyCommand.cpp ClassifyCommand.h
        DisplayCommand.cpp DisplayCommand.h DownloadCommand.cpp DownloadCommand.h
        ExitCommand.cpp ExitCommand.h CLI.cpp CLI.h)