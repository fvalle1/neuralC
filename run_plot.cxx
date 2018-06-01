//
// Created by Filippo Valle on 01/05/2018.
//

#include "NeuralAnalyzer/NeuralAnalyzer.h"
#include "TAxis.h"

int run_plot(){
    auto cx=new TCanvas("net", "Neural net", 10, 10, 640, 480);
    auto cz=new TCanvas("cz", "Neural net - dataset", 10, 490, 640, 480);
    auto *analyser = new NeuralAnalyzer();

    auto dataset = analyser->GetDataset();
    auto test = analyser->GenerateTest();
    auto results = analyser->GetResults();
    cx->cd();

    auto graph=new TMultiGraph();
    //graph->Add(dataset);
    graph->Add(results);
    graph->Add(test);
    graph->Draw("AP");

    cz->cd();
    dataset->Draw("AP");

    auto cy = new TCanvas("err", "Error", 650, 10, 640, 480);
    auto eplot = analyser->GetErrorGraph();
    cy->cd();
    eplot->Draw("AP");
    eplot->GetYaxis()->SetTitle("Error");
    eplot->GetXaxis()->SetTitle("epoch");

    return 0;
}