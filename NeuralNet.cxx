//
// Created by Filippo Valle on 17/04/2018.
//

#include "NeuralNet.h"

NeuralNet::NeuralNet() :
        fDepth(0),
        fmaxiterations(5000),
        fLearningRate(0.05),
        fEpsilon(0.001),
        fNinit(1000),
        fBatchSize(100),
        fSeed(42),
        fStatus(net::netStatuses::kReady){

}

NeuralNet::NeuralNet(uint64_t iterations, double_t learningrate, double_t epsilon, uint64_t ninit,
                     double batchsize) : fDepth(0), fStatus(net::netStatuses::kReady){
    fmaxiterations=iterations;
    fLearningRate=learningrate;
    fEpsilon=epsilon;
    fNinit=ninit;
    fBatchSize=batchsize;
    fSeed=std::time(NULL);
}



NeuralNet &NeuralNet::firstLayer(uint64_t numOfNeurons, const std::vector<datatype> &input) {
    fLayers.emplace_back(InputLayer(numOfNeurons, input[0].size(), fLearningRate, fSeed, fDepth));
    fX = input;
    fStatus = net::netStatuses::kDataloaded;
    return *this;
}

NeuralNet &NeuralNet::firstLayer(uint64_t numOfNeurons, const std::string datafilename) {
    std::__1::fstream file(datafilename);
    std::vector<datatype> input;

    if (file.is_open()) {
        std::__1::string line;
        while (getline(file, line)) {
            std::__1::istringstream s(line);
            std::__1::string field;
            std::vector<double> x;
            while (getline(s, field, ',')) {
                x.push_back(atof(field.c_str()));
            }
            input.push_back(x);
        }
    } else {
        std::__1::cerr << "file " << datafilename << " not found";
    }

    file.close();

    return firstLayer(numOfNeurons, input);
}

NeuralNet &NeuralNet::addLayer(uint64_t numOfNeurons) {

    //number of input is the number of neurons in previous layer
    uint64_t numOfInputs = fLayers[fDepth].fNeurons.size();

    fLayers.emplace_back(Layer(numOfNeurons, numOfInputs, fLearningRate, fSeed, ++fDepth));

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


NeuralNet &NeuralNet::lastLayer(std::string targetfilename) {
    std::__1::fstream filetarget(targetfilename);
    std::vector<double> output;

    if (filetarget.is_open()) {
        std::__1::string line;
        while (getline(filetarget, line)) {
            output.push_back(atof(line.c_str()));
        }
    } else {
        std::__1::cerr << "file " << targetfilename << " not found";
    }

    filetarget.close();
    return lastLayer(output);
}

NeuralNet & NeuralNet::train(bool storeErrordata) {
    if(fStatus<1){
        std::cerr<<"Dataset not loaded" <<std::endl;
        return *this;
    }

    fStatus = net::netStatuses::kTrained;

    clearErrorFile();

    double error;
    uint8_t ninit = 0;
    uint64_t nskipped = 0;
    uint64_t nequal = 0;
    bool isReinitLoop = false;
    std::random_device rd;
    std::default_random_engine e1(rd());

    std::uniform_int_distribution<uint64_t > uniform_dist(0, fX.size()-1);
    for (uint64_t step = 0; step < fmaxiterations; step++) {
        //uint64_t iData = step % fX[0].size();
        uint64_t iData = uniform_dist(e1);

        if(!isReinitLoop) {
            //freeze
            for (auto &layer: fLayers) {
                layer.freeze();
            }
        }

        for(uint64_t iBatch = iData; iBatch < fX.size()*fBatchSize; iBatch++) {
            auto data = fX[iBatch%fX.size()];
            //fwd propagate
            propagate(data);

            //backpropagate
            backPropagate(iData);

            //update
            for (auto &layer: fLayers) {
                layer.updateWeigths();
            }
        }

        error = getInSampleError();
        printf("\nstep: %llu/%llu\t\tError: %.6f %.6f\t\t", step, fmaxiterations, fError, error);

        if(step>0) {
            if (ninit < fNinit && (nskipped > fX.size() / 10 || nequal > fX.size() / 10) ){
                printf("REINIT WEIGHTS");
                reset();
                ninit++;
                nskipped = 0;
                nequal = 0;
                isReinitLoop = true;
                continue;
            }

            if (error > fError + fEpsilon * (1 - (double_t) step/fmaxiterations )) {

                //printf("\n errore:%f", error);
                for (auto &layer: fLayers) { layer.restoreWeigths(); }
                printf("SKIPPING");
                nskipped++;
                continue;

            }else if (std::fabs(fError - error) < fEpsilon ) {
                if (getAccurancy() > 0.9) {
                    printf("\nFinal steps: %llu\tError: %.4f\n\n", step, error);
                    break;
                }
                nequal++;
            }
        }

        fError = error;
        isReinitLoop = false;
        if (storeErrordata) addErrorToFile(fError);

    }

    printf("\n*********\nTrained\n");
    printf("\nError of the net:\t%1.2f", getInSampleError());
    printf("\nAccuracy of the net:\t%1.2f", getAccurancy());
    printf("\n*********\n");
    return *this;
}


double NeuralNet::getInSampleError() {
    double_t error = 0.;
    for(uint64_t iData=0; iData < fX.size(); iData++){
        propagate(fX[iData]);
        //printf("\n%f\t%f    %d",fLayers[fDepth][0].getOutputX(), fy[iData], iData );
        error+= (fLayers[fDepth][0].getOutputX()-fy[iData]) * (fLayers[fDepth][0].getOutputX()-fy[iData]);
    }
    error*=1./(double)fX.size();
    return error;
}

double NeuralNet::getAccurancy() {
    uint64_t guessed = 0;
    for(uint64_t iData=0; iData < fX.size(); iData++){
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

double NeuralNet::infere(datatype &X, bool continuos) {
    double output = 0;

    if(fStatus==net::netStatuses::kTrained) {
        auto it = fCache.find(X);
        if (it != fCache.end()) {
            output = it->second;

        } else {
            propagate(X);

            output = fLayers[fDepth][0].getOutputX();
            fCache[X] = output;
        }
    }else{
        std::cerr<<"Net not trained"<<std::endl;
        return output;
    }

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

NeuralNet &NeuralNet::infere(std::string testfilename) {
    std::__1::fstream filetest(testfilename, std::ios::in);
    const auto inferefilename = "infered.csv";
    std::__1::fstream fileresult(inferefilename, std::ios::out);

    std::vector<datatype> input;

    if(fileresult.is_open()){
        if (filetest.is_open()) {
            std::__1::string line;
            while (getline(filetest, line)) {
                std::__1::istringstream s(line);
                std::__1::string field;
                std::vector<double> x;
                while (getline(s, field, ',')) {
                    x.push_back(atof(field.c_str()));
                }
                auto infered = infere(x);
                fileresult<<infered<<"\n";
            }
        } else {
            std::__1::cerr << "file " << testfilename << " not found";
        }
    }else{
        std::__1::cerr << "file " << inferefilename << " not opened";
    }

    filetest.close();
    fileresult.close();
    return *this;
}

void NeuralNet::reset() {
    for(auto &layer : fLayers){
        layer.reset();
    }
}

void NeuralNet::clearErrorFile() {
    std::fstream errorfile("errors.csv", std::ios::out);

    errorfile.close();
}


void NeuralNet::addErrorToFile(double error) {
    std::fstream errorfile("errors.csv", std::ios::app);
    errorfile<<error<<"\n";
    errorfile.close();
}