#include <iostream>

#include "NeuralNet.h"


int main() {
    std::cout << "Hello, neural net!" << std::endl;
    NeuralNet net(5000,10,0.01,1000,20);
    net.firstLayer(15,"dataset.csv").addLayer(10).addLayer(10).lastLayer("target.csv");
    net.train(true);
    net.infere("test.csv");

    return 0;
}