cmake_minimum_required(VERSION 3.20)
project(AdvancedProgramingPart3)

set(CMAKE_BUILD_TYPE Debug)

add_executable(AdvancedProgramingPart3_Client Client.cpp IOClass/IOClass.cpp IOClass/IOClass.h)

add_executable(AdvancedProgramingPart3_Server Server.cpp algorithm/Distance.cpp algorithm/Distance.h
        algorithm/CanberraDistance.cpp algorithm/CanberraDistance.h
        algorithm/ChebyshevDistance.cpp algorithm/ChebyshevDistance.h algorithm/EuclideanDistance.cpp
        algorithm/EuclideanDistance.h algorithm/MinkowskiDistance.cpp algorithm/MinkowskiDistance.h
        algorithm/TaxicabGeometry.cpp algorithm/TaxicabGeometry.h algorithm/Knn.cpp algorithm/Knn.h IOClass/IOClass.cpp IOClass/IOClass.h)