//
// Created by Filippo Valle on 08/05/2018.
//

#include "NeuralAnalyzer/NeuralAnalyzer.h"

int run_dataset(){
    auto cx=new TCanvas("cx", "Neural net");
    auto *analyser = new NeuralAnalyzer(datasets::kCircle);
    analyser->DatasetToFile();

    auto dataset = analyser->GetDataset();
    auto test = analyser->GenerateTest();
    cx->cd();

    auto graph=new TMultiGraph();
    graph->Add(dataset);
    graph->Draw("AP");

    return 0;
}
