#include "gtest/gtest.h"
#include "NeuralNet.h"
#include <iostream>

using std::vector;

void initdata(std::vector<std::vector<double>> &X, std::vector<double> &y) {
    for(size_t i=0; i<10; i++){
        std::vector<double> x;
        for (int j = 0; j < 5; ++j) {
            x.push_back(j*i);
        }
        X.push_back(x);
        y.push_back(i<5);
    }
}

TEST(net_Test, net_test_createNet) {
    NeuralNet net;

    std::vector<std::vector<double>> X;
    std::vector<double> y;
    initdata(X,y);

    net.firstLayer(4, X).addLayer(3).addLayer(3).addLayer(6).lastLayer(y).toOstream();

    ASSERT_EQ(0, 0);
}

TEST(net_Test, net_test_train) {
    NeuralNet net;

    std::vector<std::vector<double>> X;
    std::vector<double> y;

    for(size_t i=0; i<10; i++){
        std::vector<double> x;
        for (int j = 0; j < 5; ++j) {
            x.push_back(j*i);
        }

        X.push_back(x);
        y.push_back(i<5);
    }
    net.firstLayer(3,X).addLayer(2).lastLayer(y).toOstream();
    net.train();

    EXPECT_EQ(0, 0);
}

std::function<double (std::vector<double>)> targetf =  [](std::vector<double> x){return (x[0] - x[1] >0?-1:1);};
NeuralNet createandtrain(){
    std::vector<std::vector<double>> X;
    std::vector<double> y;
    for(int i=-10; i<10; i+=1) {
        for (int j = -10; j < 10; j+=1) {
            std::vector<double> x;
            x.push_back(i);
            x.push_back(j);
            X.push_back(x);
            y.push_back(targetf(x));
        }
    }
    NeuralNet net;
    net.firstLayer(4, X).addLayer(3).lastLayer(y);
    net.train();
    printf("\nAccuracy of the net: %1.2f", net.getAccurancy());
    return net;
}

TEST(net_Test, net_test_graphics) {
    NeuralNet net = createandtrain();

    printf("\n*********************\n\n");
    for (int i = -10; i < 10; i+=2) {
        for (int j = -10; j < 10; j+=2) {
            std::vector<double> x;
            x.push_back(i);
            x.push_back(j);
            printf("%d", targetf(x) == 1 ? 1 : 0);
        }
        printf("\n");
    }

    printf("\n\n\n");

    for (int i = -10; i < 10; i+=2) {
        for (int j = -10; j < 10; j+=2) {
            std::vector<double> x;
            x.push_back(i);
            x.push_back(j);
            printf("%d", net.infere(x, false) ==1 ? 1 : 0);
//          printf("%f", net.infere(x, true));

        }
        printf("\n");
    }

    std::vector<double> x_test = {3,3};

    double output = net.infere(x_test, false);
    EXPECT_EQ(output, targetf(x_test));
}

TEST(net_Test, net_test_full_positive){
    NeuralNet net = createandtrain();

    std::vector<double> x_test = {3,3};
    double output = net.infere(x_test, true);
//    std::cout<<output<<std::endl;
    output=output>0?-1:1;
    EXPECT_EQ(output, targetf(x_test));
}

TEST(net_Test, net_test_full_negative){
    NeuralNet net = createandtrain();

    std::vector<double> x_test = {-3,-5};
    double output = net.infere(x_test, true);
//    std::cout<<output<<std::endl;
    output=output>0?-1:1;
    EXPECT_EQ(output, targetf(x_test));
}