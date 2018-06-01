//
// Created by Filippo Valle on 05/05/2018.
//

#include "NeuralNet.h"
#include "XRayMachine/XRayMachine.h"

void run_xray(){
    auto cx = XRayMachine(NeuralNet().firstLayer(15,"dataset.csv").addLayer(25).addLayer(25).lastLayer("target.csv")).fCanvas;
}