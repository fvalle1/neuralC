//
// Created by Filippo Valle on 17/04/2018.
//

#ifndef NEURALNET_PERCEPTRON_H
#define NEURALNET_PERCEPTRON_H

#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <random>
#include <cmath>

#include "pcg/pcg_random.hpp"

enum PerceptronStatuses{
    kReady,
    kDataLoaded,
    kTrained,
    kBackProp
};

typedef double (*theta_function)(double);
typedef std::vector<double> datatype;


class Perceptron {
public:
    Perceptron(uint64_t id, uint64_t numOfFeatures, theta_function theta, theta_function theta_d,
                   double learningRate, uint64_t seed, uint64_t stream);

    void setInput(const std::vector<double> &X);
    void updateWeights();
    void restoreWeights();
    void freeze();
    void reset();
    void fit();
    void predict(std::vector<double> X);
    void toOstream();
    inline void setDelta(double delta){fdelta = delta;};


    uint64_t fID;
    std::vector<double> fInputs;
    std::vector<double> fW;
    std::vector<double> fW_stored;
    double fdelta;

    double getOutputX();
    double getOutputtheta_d();



private:
    PerceptronStatuses fStatus;

    pcg32 fRNG;
    double fSignal;
    double fX; //theta of (fSignal)
    double fThetaprime; //theta_d of (fSignal)
    double fLearningRate;

    uint64_t fNumOfFeatures;

    theta_function fTheta;
    theta_function fTheta_d;

};

#endif //NEURALNET_PERCEPTRON_H
