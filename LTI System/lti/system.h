#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

bool getSystemParameters(ifstream& file, int& Mplus, int& N);

bool getSystemCoefficients(ifstream& file, int Mplus, int N,
                           double* b, double* a);

bool getInitialConditions(ifstream& file, int Mplus, int N,
                          double* x, double* y);

void computeSystem(double newValue, int Mplus, int N, double b[],
                   double a[], double* x, double* y);

#endif // SYSTEM_H_INCLUDED
