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

#if defined(_OPENMP)
#include <omp.h>
#endif

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
    NeuralNet(uint64_t iterations, double_t learningrate, double_t epsilon, uint64_t ninit,
              double batchsize);

    NeuralNet &firstLayer(uint64_t numOfNeurons, const std::vector<std::vector<double>> &input);
    NeuralNet &firstLayer(uint64_t numOfNeurons, std::string datafilename);
    NeuralNet &addLayer(uint64_t numOfNeurons);
    NeuralNet &lastLayer(const std::vector<double> &y);
    NeuralNet &lastLayer(std::string targetfilename);
    NeuralNet & toOstream();
    NeuralNet &train(bool storeErrordata);

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
    double_t fBatchSize;
    uint64_t  fNinit;
    uint64_t fSeed;
    std::vector<datatype> fX;
    std::vector<double> fy;
    std::vector<Layer> fLayers;
    std::map<datatype, double> fCache;

    void propagate(const datatype &data);
    void backPropagate(uint64_t iData);
    void reset();
    void clearErrorFile();
    void addErrorToFile(double error);

    net::netStatuses fStatus;
};


#endif //NEURALNET_TOPOLOGY_H
