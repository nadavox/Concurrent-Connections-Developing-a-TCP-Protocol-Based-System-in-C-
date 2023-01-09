cmake_minimum_required(VERSION 3.20)
project(AdvancedProgramingPart3)

set(CMAKE_BUILD_TYPE Debug)

add_executable(AdvancedProgramingPart3_Client Client.cpp IOClass.cpp IOClass.h)

add_executable(AdvancedProgramingPart3_Server Server.cpp Distance.cpp Distance.h
        CanberraDistance.cpp CanberraDistance.h
        ChebyshevDistance.cpp ChebyshevDistance.h EuclideanDistance.cpp
        EuclideanDistance.h MinkowskiDistance.cpp MinkowskiDistance.h
        TaxicabGeometry.cpp TaxicabGeometry.h Knn.cpp Knn.h IOClass.cpp IOClass.h Command.cpp Command.h UploadCommand.cpp UploadCommand.h SettingsCommand.cpp SettingsCommand.h ClassifyCommand.cpp ClassifyCommand.h DisplayCommand.cpp DisplayCommand.h DownloadCommand.cpp DownloadCommand.h ExitCommand.cpp ExitCommand.h CLI.cpp CLI.h)