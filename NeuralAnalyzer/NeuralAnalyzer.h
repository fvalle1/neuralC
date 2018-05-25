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

namespace datasets {
    enum datasetType {
        kGauss,
        kCircle
    };
}

class NeuralAnalyzer{
public:
    NeuralAnalyzer(datasets::datasetType type = datasets::kGauss);

    void DatasetToFile();

    TMultiGraph* GetDataset();
    TGraph* GenerateTest();
    TMultiGraph * GetResults();
    TGraph *GetErrorGraph();


private:
    void Fill();
    std::vector<std::vector<double>> fDataset;
    std::vector<double> fTarget;

    TRandom* frandom;

    TMultiGraph *fDatasetGraph;
    TMultiGraph *fResultsGraph;
    TGraph *fTestGraph;
    TGraph *fErrorGraph;
    datasets::datasetType fType;


    void ReadFromFile(TGraph **g, std::string Xdata, std::string Ydata);
};

#endif