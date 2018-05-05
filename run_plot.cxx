//
// Created by Filippo Valle on 01/05/2018.
//

#include "NeuralAnalyzer/NeuralAnalyzer.h"
#include "TMultiGraph.h"
#include "TCanvas.h"

int run_plot(){
    auto cx=new TCanvas("Neural net");
    auto *p = new NeuralAnalyzer();
    p->GenerateDataset();

    auto dataset = p->GetDataset();
    auto test = p->GenerateTest();
    auto results = p->GetResults();
    cx->cd();

    auto graph=new TMultiGraph();
    graph->Add(results);
    graph->Add(dataset);
    graph->Add(test);
    graph->Draw("AP");

    return 0;
}