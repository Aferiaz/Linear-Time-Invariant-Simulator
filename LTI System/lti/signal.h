#ifndef SIGNAL_H_INCLUDED
#define SIGNAL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isValidLine(string line, double& signalValue,
                 bool firstLine = false);

bool getSignalValues(ifstream& file, vector<double>& s);

#endif // SIGNAL_H_INCLUDED
