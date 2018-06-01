cmake_minimum_required(VERSION 3.10)
project(NeuralNet)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories(
        .
        pcg/.
        ~/root/include/
        ~/libomp/openmp/include/
)

add_executable(NeuralNet
        main.cpp
        NeuralNet.cxx
        Layer.cxx
        Perceptron.cxx
        )



add_subdirectory(tests/)

add_subdirectory(NeuralAnalyzer/)
add_subdirectory(XRayMachine/)