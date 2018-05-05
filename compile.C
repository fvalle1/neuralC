#include "TSystem.h"

int compile(){
    gSystem->CompileMacro("Perceptron.cxx");
    gSystem->CompileMacro("Layer.cxx");
    gSystem->CompileMacro("NeuralNet.cxx");
    gSystem->CompileMacro("NeuralAnalyzer/NeuralAnalyzer.cxx");
    gSystem->CompileMacro("XRayMachine/XRayMachine.cxx");
    return 0;
}

