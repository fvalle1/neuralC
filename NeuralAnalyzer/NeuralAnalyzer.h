#ifndef PLOT_H
#define PLOT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TRandom.h"


class NeuralAnalyzer{
public:
    NeuralAnalyzer();

    void GenerateDataset();

    inline TMultiGraph* GetDataset(){return fDatasetGraph;};
    TGraph* GenerateTest();
    TMultiGraph * GetResults();


private:
    void Fill();
    std::vector<std::vector<double>> fDataset;
    std::vector<double> fTarget;

    TRandom* frandom;

    TMultiGraph *fDatasetGraph;
    TGraph *fTestGraph;
    TMultiGraph *fResultsGraph;


};

#endif