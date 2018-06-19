#include <iostream>

#include "NeuralNet.h"


int main() {
    std::cout << "Hello, neural net!" << std::endl;
    NeuralNet net(800000,100,0.5,100000,.2);
    net.firstLayer(25,"dataset.csv").addLayer(25).addLayer(25).addLayer(25).addLayer(20).lastLayer("target.csv");
    net.train(true);
    net.infere("test.csv");

    return 0;
}
