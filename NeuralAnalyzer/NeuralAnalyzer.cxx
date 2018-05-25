#include <sstream>
#include "NeuralAnalyzer.h"

NeuralAnalyzer::NeuralAnalyzer(datasets::datasetType type):fType(type) {
    fDatasetGraph=new TMultiGraph();

    fTestGraph = new TGraph();
    fResultsGraph=new TMultiGraph();
    fErrorGraph = new TGraph();

    frandom = new TRandom();
}

void NeuralAnalyzer::Fill() {
    Int_t N = 500;
    Int_t nGraph[2]={0};
    TGraph* classGraph[2];
    classGraph[0] = new TGraph;
    classGraph[0]->SetMarkerSize(1);
    classGraph[0]->SetMarkerStyle(20);
    classGraph[0]->SetMarkerColor(kViolet);
    classGraph[1] = new TGraph;
    classGraph[1]->SetMarkerSize(1);
    classGraph[1]->SetMarkerStyle(20);
    classGraph[1]->SetMarkerColor(kBlue);

    switch (fType) {
        case datasets::kGauss:
            for (auto i = 0; i < N; ++i) {
                std::vector<double> x;
                auto x1=frandom->Gaus(0.2, 0.35);
                auto x2=frandom->Gaus(-0.3, 0.2);
                x.push_back(x1);
                x.push_back(x2);
                fDataset.push_back(x);
                fTarget.push_back(-1);
                classGraph[0]->SetPoint(nGraph[0]++,x1,x2);
            }

            for (auto i = 0; i < N; ++i) {
                std::vector<double> x;
                auto x1=frandom->Gaus(-0.4, 0.2);
                auto x2=frandom->Gaus(0.5, 0.2);
                x.push_back(x1);
                x.push_back(x2);
                fDataset.push_back(x);
                fTarget.push_back(1);
                classGraph[1]->SetPoint(nGraph[1]++,x1,x2);
            }
            break;

        case datasets::kCircle:
            for (auto i = 0; i < 2 * N; ++i) {
                std::vector<double> x;
                auto x1=frandom->Rndm()*2-1;
                auto x2=frandom->Rndm()*2-1;
                x.push_back(x1);
                x.push_back(x2);
                fDataset.push_back(x);
                int target = (x1*x1+x2*x2<0.3?1:-1);
                fTarget.push_back(target);
                classGraph[(target+1)/2]->SetPoint(nGraph[(target+1)/2]++,x1,x2);
            }

            break;
    }

    fDatasetGraph->Add(classGraph[0]);
    fDatasetGraph->Add(classGraph[1]);

}

void NeuralAnalyzer::DatasetToFile(){
    Fill();
    std::ofstream datafile;
    std::ofstream targetfile;
    datafile.open("dataset.csv", std::ios_base::out);
    targetfile.open("target.csv", std::ios_base::out);
    Int_t i=0;
    for(auto &x: fDataset){
        datafile<<x[0]<<","<<x[1]<<"\n";
        targetfile<<fTarget[i++]<<"\n";
    }

    datafile.close();
    targetfile.close();
}


TMultiGraph * NeuralAnalyzer::GetResults() {
    TGraph *g[2];
    g[0]= new TGraph();
    g[0]->SetMarkerColorAlpha(kRed, 0.4);
    g[0]->SetMarkerSize(1.5);
    g[0]->SetMarkerStyle(20);
    g[1]= new TGraph();
    g[1]->SetMarkerColorAlpha(kCyan-3, 0.4);
    g[1]->SetMarkerStyle(20);
    g[1]->SetMarkerSize(1.5);
    ReadFromFile(g, "test.csv", "infered.csv");
    fResultsGraph->Add(g[0]);
    fResultsGraph->Add(g[1]);
    return fResultsGraph;
}

TGraph* NeuralAnalyzer::GenerateTest() {
    Int_t N=1000;
    Int_t nGraph=0;
    std::fstream testfile("test.csv", std::ios::out);

    for(Int_t i=0; i<N; i++){
        auto x1=frandom->Rndm()*2-1;
        auto x2=frandom->Rndm()*2-1;
        fTestGraph->SetPoint(nGraph++,x1,x2);
        testfile<<x1<<","<<x2<<"\n";
    }

    testfile.close();
    return fTestGraph;
}

TGraph *NeuralAnalyzer::GetErrorGraph() {
    fErrorGraph->SetMarkerSize(0.75);
    fErrorGraph->SetMarkerStyle(20);
    fErrorGraph->SetMarkerColor(kBlue);
    std::fstream errorfile("errors.csv", std::ios::in);

    std::string errorline;
    Int_t nGraph = 0;
    while(getline(errorfile, errorline)){
        double data=atof(errorline.c_str());
        fErrorGraph->SetPoint(nGraph,nGraph, data);
        nGraph++;
    }

    return fErrorGraph;
}

TMultiGraph *NeuralAnalyzer::GetDataset() {
    TGraph *g[2];
    g[0]= new TGraph();
    g[0]->SetMarkerColor(kRed);
    g[0]->SetMarkerSize(1.5);
    g[0]->SetMarkerStyle(20);
    g[1]= new TGraph();
    g[1]->SetMarkerColor(kCyan-3);
    g[1]->SetMarkerStyle(20);
    g[1]->SetMarkerSize(1.5);
    ReadFromFile(g, "dataset.csv", "target.csv");

    fDatasetGraph->Add(g[0]);
    fDatasetGraph->Add(g[1]);
    return fDatasetGraph;
}

void NeuralAnalyzer::ReadFromFile(TGraph **g, std::string Xdata, std::string Ydata){
    std::fstream datafile(Xdata, std::ios::in);
    std::fstream targetfile(Ydata, std::ios::in);

    if(!datafile.is_open()||!targetfile.is_open()){
        std::cerr<<"file not opened"<<std::endl;
    }

    std::string line;
    double nGraph[2];
    nGraph[0]=0;
    nGraph[1]=0;

    std::string targetline;
    std::string dataline;
    while(getline(targetfile, targetline)&& getline(datafile, dataline)){
        double x1, x2;
        int y;
        y=std::atoi(targetline.c_str());
        std::stringstream linestream(dataline);
        std::string field;
        getline(linestream, field, ',');
        x1 = atof(field.c_str());
        getline(linestream, field, ',');
        x2 = atof(field.c_str());
        //std::cout<<x1<<y<<std::endl;
        if(y==-1) y=0;
        g[y]->SetPoint(nGraph[y]++,x1,x2);

        if(!datafile.good()) break;
        if(!targetfile.good()) break;
    }

    targetfile.close();
    datafile.close();
}
