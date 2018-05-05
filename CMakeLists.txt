cmake_minimum_required(VERSION 3.10)
project(NeuralNet)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        .
        pcg/.
        ~/root/include/
)

add_executable(NeuralNet
        main.cpp
        NeuralNet.cxx
        Layer.cxx
        Perceptron.cxx
        )

add_executable(plotter
        NeuralAnalyzer.cxx
        run_plot.cxx
)

add_subdirectory(
        tests/
)