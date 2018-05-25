#include "TSystem.h"

int compile(){
    gSystem->CompileMacro("Perceptron.cxx", "kO");
    gSystem->CompileMacro("Layer.cxx", "kO");
    gSystem->CompileMacro("NeuralNet.cxx", "kO");
    gSystem->CompileMacro("NeuralAnalyzer/NeuralAnalyzer.cxx", "kO");
    gSystem->CompileMacro("XRayMachine/XRayMachine.cxx", "kO");
    return 0;
}

