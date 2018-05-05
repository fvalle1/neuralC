//
// Created by Filippo Valle on 05/05/2018.
//

#include "NeuralNet.h"
#include "XRayMachine/XRayMachine.h"

void run_xray(){
    auto cx = XRayMachine(NeuralNet().firstLayer(3, "dataset.csv").addLayer(5).lastLayer("target.csv")).fCanvas;
}