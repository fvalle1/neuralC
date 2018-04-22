//
// Created by Filippo Valle on 17/04/2018.
//

#include "NeuralNet.h"

NeuralNet::NeuralNet() : fDepth(0), fmaxiterations(5000), fLearningRate(0.1), fEpsilon(0.001){

}

NeuralNet &NeuralNet::firstLayer(uint64_t numOfNeurons, const std::vector<datatype> &input) {
    fLayers.emplace_back(InputLayer(numOfNeurons, input[0].size(), fLearningRate, fDepth));
    fX = input;

    return *this;
}

NeuralNet &NeuralNet::addLayer(uint64_t numOfNeurons) {

    //number of input is the number of neurons in previous layer
    uint64_t numOfInputs = fLayers[fDepth].fNeurons.size();

    fLayers.emplace_back(Layer(numOfNeurons, numOfInputs, fLearningRate, fDepth));
    fDepth++;

    return *this;
}

NeuralNet &NeuralNet::lastLayer(const std::vector<double> &y) {
    //number of input is the number of neurons in previous layer
    uint64_t numOfInputs = fLayers[fDepth].fNeurons.size();

    fLayers.emplace_back(OutputLayer(numOfInputs, fLearningRate, fDepth));
    fDepth++;
    fy = y;
    return *this;
}

NeuralNet & NeuralNet::train() {
    double error;
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<uint64_t > uniform_dist(0, fX.size()-1);
    for (uint64_t step = 0; step < fmaxiterations; step++) {
        //uint64_t iData = step % fX[0].size();
        uint64_t iData = uniform_dist(e1);
        auto data = fX[iData];
        //fwd propagate
        propagate(data);

        //backpropagate
        backPropagate(iData);

        //update
        for (auto &layer: fLayers) {
            layer.updateWeigths();
            layer.freeze();
        }

        error = getInSampleError();
        if(step>0) {
            if (error > fError) {
                //printf("\n errore:%f", error);
                for (auto &layer: fLayers) {layer.restoreWeigths(); }
                continue;
            }
            if ((fError - error) < fEpsilon) {
                printf("\nFinal steps: %llu\t\tError: %.4f", step, error);
                break;
            }
        }

        fError = error;
        printf("\nstep: %llu/%llu\t\tError: %.4f", step, fmaxiterations, error);

    }

    return *this;
}


double NeuralNet::getInSampleError() {
    double_t error = 0.;
    for(int iData=0; iData < fX.size(); iData++){
        propagate(fX[iData]);
        //printf("\n%f\t%f    %d",fLayers[fDepth][0].getOutputX(), fy[iData], iData );
        error+= (fLayers[fDepth][0].getOutputX()-fy[iData]) * (fLayers[fDepth][0].getOutputX()-fy[iData]);
    }
    error*=1./(double)fX.size();
    return error;
}

double NeuralNet::getAccurancy() {
    uint64_t guessed = 0;
    for(int iData=0; iData < fX.size(); iData++){
        if(fabs(infere(fX[iData])-fy[iData]) < fEpsilon) guessed++;
    }
    //printf("guessed: %llu",guessed);
    return (double_t) guessed/(double)fX.size();
}


void NeuralNet::backPropagate(uint64_t iData) {
    double deltaLast = 0.;
    double XLast = fLayers[fDepth].fNeurons[0].getOutputX();
    double thetaprimeLast = fLayers[fDepth].fNeurons[0].getOutputtheta_d();
    deltaLast += 2 * (XLast - fy[iData]) * thetaprimeLast;
    fLayers[fDepth].fNeurons[0].setDelta(deltaLast);

    for (uint64_t l = fDepth - 1; ; l-=1) {
        auto layer = fLayers[l];
        auto nextLayer = fLayers[l + 1];

        for (auto &neuron : layer.fNeurons) {
            double delta = 0.;

            for (auto &nextNeuron : nextLayer.fNeurons) {
                delta += nextNeuron.fdelta * nextNeuron.fW[neuron.fID] * nextNeuron.getOutputtheta_d();
            }

            fLayers[l][neuron.fID].setDelta(delta);
        }

        //l is unsigned long cannot go negative to compare l>=0
        if(l==0) break;
    }
}

void NeuralNet::propagate(const datatype &data) {
    //set global input as input for first layer
    for (auto &neuron : fLayers[0].fNeurons) {
        neuron.setInput(data);
    }

    for (auto layer = fLayers.begin() + 1; layer != fLayers.end(); layer++) {
        auto outputs = (layer - 1)->getOutputs();

        for (auto &neuron : layer->fNeurons) {
            neuron.setInput(outputs);
            neuron.fit();
        }
    }
}

double NeuralNet::infere(std::vector<double> &X, bool continuos) {
    propagate(X);

    auto output = fLayers[fDepth][0].getOutputX();
    if(continuos) return output;
    else return output>0?1:-1;
}

NeuralNet & NeuralNet::toOstream() {
    printf("\n\n\n********\nNeural Net\nnum of layers: %llu\nmaxiterations: %llu\n", fDepth, fmaxiterations);
    for(auto &layer:fLayers){
        layer.toOstream();
    }

    return *this;
}
