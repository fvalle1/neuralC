//
// Created by Filippo Valle on 17/04/2018.
//

#include "Layer.h"

Layer::Layer(uint64_t numOfNeurons, uint64_t numOfFeatures, double learningRate, uint64_t stream)
        : fnumOfNeurons(numOfNeurons) {
    fNeurons.reserve(numOfNeurons);

    for(uint64_t i = 0; i < numOfNeurons; i++){
        fNeurons.emplace_back(Perceptron(i, numOfFeatures, +[](double x) { return tanh(x); },
                                         +[](double x) { return 1. / (cosh(x) * cosh(x)); }, learningRate, 42, stream*i));
    }
}

std::vector<double> Layer::getOutputs() {
    std::vector<double> output;
    output.reserve(fnumOfNeurons);

    for(auto &neuron : fNeurons){
        output.emplace_back(neuron.getOutputX());
    }

    return output;
}

InputLayer::InputLayer(uint64_t numOfNeurons, uint64_t inputSize, double learningRate, uint64_t stream) : Layer(numOfNeurons, inputSize, learningRate, stream) {

}

void Layer::toOstream() {
    printf("\n\n*************\nIm a layer\nI have %lu neurons\n", fNeurons.size());
    for(auto &neuron : fNeurons){
        neuron.toOstream();
    }
}

void Layer::updateWeigths() {
    for(auto &neuron : fNeurons){
        neuron.updateWeights();
    }
}

void Layer::restoreWeigths() {
    for(auto &neuron : fNeurons){
        neuron.restoreWeights();
    }
}

void Layer::freeze() {
    for(auto &neuron : fNeurons){
        neuron.freeze();
    }
}

void Layer::reset() {
    for(auto &neuron : fNeurons){
        neuron.reset();
    }
}