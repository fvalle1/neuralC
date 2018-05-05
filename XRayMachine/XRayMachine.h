//
// Created by Filippo Valle on 05/05/2018.
//

#ifndef NEURALNET_XRAYMACHINE_H
#define NEURALNET_XRAYMACHINE_H

#include <vector>
#include "NeuralNet.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TLine.h"

class XRayMachine {
public:
    XRayMachine(NeuralNet net);
    TGraph *fGraph;
    TCanvas *fCanvas;
private:
    std::vector<TLine*> fLines;
};


#endif //NEURALNET_XRAYMACHINE_H
