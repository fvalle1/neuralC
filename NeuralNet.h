//
// Created by Filippo Valle on 17/04/2018.
//

#ifndef NEURALNET_TOPOLOGY_H
#define NEURALNET_TOPOLOGY_H

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Layer.h"

namespace net {
    enum netStatuses {
        kReady,
        kDataloaded,
        kTrained
    };
}

class NeuralNet {
public:
    NeuralNet();

    NeuralNet &firstLayer(uint64_t numOfNeurons, const std::vector<std::vector<double>> &input);
    NeuralNet &firstLayer(uint64_t numOfNeurons, std::string datafilename);
    NeuralNet &addLayer(uint64_t numOfNeurons);
    NeuralNet &lastLayer(const std::vector<double> &y);
    NeuralNet &lastLayer(std::string targetfilename);
    NeuralNet & toOstream();
    NeuralNet & train();

    NeuralNet& infere(std::string testfilename);
    double infere(datatype &X, bool continuos = false);

    double getInSampleError();
    double getAccurancy();

    inline Layer getLayer(uint64_t l) const {return fLayers[l];};
    inline Layer& operator[] (uint64_t l){return fLayers[l];};

    uint64_t fmaxiterations;
    uint64_t fDepth;

private:
    double_t fLearningRate;
    double_t fError;
    double_t fEpsilon;
    uint8_t  fNinit;
    std::vector<datatype> fX;
    std::vector<double> fy;
    std::vector<Layer> fLayers;
    std::map<datatype, double> fCache;

    void propagate(const datatype &data);
    void backPropagate(uint64_t iData);
    void reset();

    net::netStatuses fStatus;
};


#endif //NEURALNET_TOPOLOGY_H
