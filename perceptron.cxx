//
// Created by Filippo Valle on 17/04/2018.
//

#include "Perceptron.h"

Perceptron::Perceptron(uint64_t id, uint64_t numOfFeatures, theta_function theta, theta_function theta_d,
                       double learningRate, uint64_t seed, uint64_t stream)
        :
        fID(id),
        fLearningRate(learningRate),
        fStatus(kReady),
        fNumOfFeatures(numOfFeatures),
        fTheta(theta),
        fTheta_d(theta_d)
{
    fRNG = pcg32(seed, stream);
    std::uniform_real_distribution<double> distribution(-0.5,0.5);

    fW.reserve(fNumOfFeatures+1);
    fW_stored.reserve(fNumOfFeatures+1);


    //add vapnick dimension and random init w
    for(int i=0;i<fNumOfFeatures+1;i++){
        fW.push_back(distribution(fRNG));
    }
}

void Perceptron::setInput(const std::vector<double> &X) {
    fInputs.clear();
    fInputs.reserve(fNumOfFeatures);
    for (size_t i = 0; i < fNumOfFeatures; ++i) {
        fInputs.emplace_back(X[i]);
    }
    fStatus = kDataLoaded;
}


void Perceptron::fit() {
    if(fStatus<1){
        std::cerr<<"Data not loaded in Perceptron " << fID <<std::endl;
        return;
    }

    fSignal = std::inner_product(fInputs.begin(),fInputs.end(),fW.begin()+1,fW[0]);
    fX = fTheta(fSignal);
    fThetaprime = fTheta_d(fSignal);
    fStatus = kTrained;
}


double Perceptron::getOutputX() {
    if (fStatus<2) fit();
    return fX;
}


double Perceptron::getOutputtheta_d() {
    return fThetaprime;
}

void Perceptron::predict(std::vector<double> X) {
    if (fStatus < 2) fit();
//TODO
}

void Perceptron::toOstream(){
    printf("neuron id: %llu\n",fID);
}

void Perceptron::updateWeights() {
    fW[0]+=-fLearningRate*fdelta;
    for(size_t i = 1; i< fW.size(); i++){
        fW[i] += -fLearningRate * fdelta * fInputs[i];
    }
    fStatus = kReady;
}

void Perceptron::freeze() {
    fW_stored.clear();
    for(size_t i = 0; i< fW.size(); i++) {
        fW_stored.push_back(fW[i]);
    }
}

void Perceptron::reset() {
    std::uniform_real_distribution<double> distribution(-0.5,0.5);
    for(int i=0;i<fNumOfFeatures+1;i++){
        fW.push_back(distribution(fRNG));
    }
}

void Perceptron::restoreWeights(){
    fW.clear();
    //std::copy(fW_stored.begin(),fW_stored.end(),fW.begin());
    for(size_t i = 0; i< fW_stored.size(); i++) {
        fW.push_back(fW_stored[i]);
    }
}