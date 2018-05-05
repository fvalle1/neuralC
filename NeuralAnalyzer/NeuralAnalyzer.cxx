#include <sstream>
#include "NeuralAnalyzer.h"

NeuralAnalyzer::NeuralAnalyzer(){
    fDatasetGraph=new TMultiGraph();

    fTestGraph = new TGraph();
    fResultsGraph=new TMultiGraph();
    frandom = new TRandom();
    Fill();
}

void NeuralAnalyzer::Fill() {
    Int_t N = 100;
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

    for (auto i = 0; i < N; ++i) {
        std::vector<double> x;
        auto x1=frandom->Gaus(0.2, 0.35);
        auto x2=frandom->Gaus(-0.3, 0.2);
        x.push_back(x1);
        x.push_back(x2);
        fDataset.push_back(x);
        fTarget.push_back(1);
        classGraph[0]->SetPoint(nGraph[0]++,x1,x2);
    }

    for (auto i = 0; i < N; ++i) {
        std::vector<double> x;
        auto x1=frandom->Gaus(-0.4, 0.2);
        auto x2=frandom->Gaus(0.5, 0.2);
        x.push_back(x1);
        x.push_back(x2);
        fDataset.push_back(x);
        fTarget.push_back(-1);
        classGraph[1]->SetPoint(nGraph[1]++,x1,x2);
    }

//    for (auto i = 0; i < N; ++i) {
//        std::vector<double> x;
//        auto x1=frandom->Rndm()*2-1;
//        auto x2=frandom->Rndm()*2-1;
//        x.push_back(x1);
//        x.push_back(x2);
//        fDataset.push_back(x);
//    }
//
//
//
//    for(auto &x : fDataset){
//        auto x1 = x[0];
//        auto x2 =x[1];
//        int pointclass = 0;
//
//        if((x2>0&x1>0)){
//            pointclass=1;
//        }else{
//            pointclass=0;
//        }
//
//        classGraph[pointclass]->SetPoint(nGraph[pointclass]++,x1,x2);
//        fTarget.push_back(pointclass*2-1);

//    }

    fDatasetGraph->Add(classGraph[0]);
    fDatasetGraph->Add(classGraph[1]);

}

void NeuralAnalyzer::GenerateDataset(){
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
    std::fstream datafile("test.csv", std::ios::in);
    std::fstream targetfile("infered.csv", std::ios::in);

    if(!datafile.is_open()||!targetfile.is_open()){
        std::cerr<<"file not opened"<<std::endl;
    }

    std::string line;
    TGraph *g[2];
    g[0]= new TGraph();
    g[0]->SetMarkerColor(kRed);
    g[0]->SetMarkerSize(1.5);
    g[0]->SetMarkerStyle(20);
    g[1]= new TGraph();
    g[1]->SetMarkerColor(kCyan-3);
    g[1]->SetMarkerStyle(20);
    g[1]->SetMarkerSize(1.5);
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

    fResultsGraph->Add(g[0]);
    fResultsGraph->Add(g[1]);
    fResultsGraph->Draw("AP");
    targetfile.close();
    datafile.close();

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
