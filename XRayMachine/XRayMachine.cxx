//
// Created by Filippo Valle on 05/05/2018.
//

#include "XRayMachine.h"

XRayMachine::XRayMachine(NeuralNet net) {
    fGraph=new TGraph();
    fCanvas = new TCanvas("Neural net");

    fGraph->SetMarkerSize(1.5);
    fGraph->SetMarkerStyle(24);

    Int_t nGraph=0;
    for(uint64_t l=0; l <= net.fDepth; l++){
        uint64_t currentN = net.getLayer(l).fNeurons.size();
        for(uint64_t i= 0; i < currentN ; i++){
            fGraph->SetPoint(nGraph++, l, i-(double_t)currentN/2.);
        }
    }

    fCanvas->cd();
    fGraph->Draw("AP");
    fGraph->GetXaxis()->SetLimits(-1, net.fDepth+1);


    for(uint64_t l=0; l < net.fDepth; l++){
        uint64_t currentN = net.getLayer(l).size();
        uint64_t nextN = net.getLayer(l+1).size();

        for(uint64_t i= 0; i < currentN ; i++){
            for(uint64_t j= 0; j < nextN ; j++) {
                TLine* line;
                line = new TLine(l, i - (double_t) currentN / 2., l + 1, j - (double_t) nextN /2. );
                fLines.push_back(line);
                fCanvas->cd();
                line->Draw();
            }
        }
    }

}
