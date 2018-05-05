//
// Created by Filippo Valle on 17/04/2018.
//

#ifndef NEURALNET_LAYER_H
#define NEURALNET_LAYER_H


#include <vector>
#include "Perceptron.h"

class Layer {
public:
    Layer(){};
    Layer(uint64_t numOfNeurons, uint64_t numOfFeatures, double learningRate, uint64_t stream);

    std::vector<double> getOutputs();
    std::vector<Perceptron> fNeurons;

    void updateWeigths();
    void restoreWeigths();
    void freeze();
    void reset();
    void toOstream();

    inline Perceptron &operator[](uint64_t neuron){return fNeurons[neuron];};
    inline uint64_t size(){ return fNeurons.size();}

private:
    uint64_t fnumOfNeurons;
};




class InputLayer: public Layer{
public:
    InputLayer(uint64_t fnumOfNeurons, uint64_t inputSize, double learningRate, uint64_t stream);

};

class OutputLayer: public Layer{
public:
    explicit OutputLayer(uint64_t inputSize, double learningRate, uint64_t stream): Layer(1, inputSize, learningRate, stream) {};
};


#endif //NEURALNET_LAYER_H
