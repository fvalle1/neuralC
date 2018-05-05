#include <iostream>

#include "NeuralNet.h"


int main() {
    std::cout << "Hello, neural net!" << std::endl;
    NeuralNet net;
    net.firstLayer(15,"dataset.csv").addLayer(5).lastLayer("target.csv");
    net.train();
    net.infere("test.csv");

    return 0;
}