# neuralC
<img src="https://github.com/gabrielefronze/neuralC/raw/master/nn.png" height="250"></img>
## Neural Net
```cpp
  NeuralNet net;
  net.firstLayer(15,"dataset.csv").addLayer(5).lastLayer("target.csv");
  net.train();
  net.infere("test.csv");
```
### files
- *dataset.csv*: contains the data in the form of one N-dimensional point per row
- *target.csv*: contains the class (**+1** or **-1**) of points in dataset
- *test.csv*: has some points to test the data

## NeuralAnalyzer
*NeuralAnalyzer* is able to generate dataset, test file and to plot all the data.

You can copile it in *root* running
```cpp
.x compile.C
```

An example is in [run_plot.cxx](run_plot.cxx)

## XRayMachine
*XRayMachine* plots the architecture design of the net simply
Example of usage is:
```cpp
auto cx =  XRayMachine(net).fCanvas;
```

An example is in [run_xray.cxx](run_xray.cxx)
