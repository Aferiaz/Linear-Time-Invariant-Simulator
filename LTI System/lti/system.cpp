/*
  Andreas Josef C. Diaz
  Marc Jefferson B. Obeles
  Justin Gabriel M. Sy

  ENGG 151.01 - A
  Project 3: Linear Time-Invariant System Simulator
*/

#include <iostream>
#include <sstream>
#include <fstream>

#include "DEBUG.h"

using namespace std;

bool getSystemParameters(ifstream& file, int& Mplus, int& N)
{
  int value;
  string line, arg1, extraTest;
  stringstream ss;

  for(int i = 0; i < 2; i++)
  {
    getline(file, line);

    ss.clear();
    ss.str("");
    ss << line;
    ss >> arg1;

    ss.clear();
    ss.str("");
    ss << arg1;

    if(ss >> value && !(ss >> extraTest) && value > 0)
    {
      if(i == 0) Mplus = value;
      else N = value;
    }
    else return false;
  }
  return true;
}

bool getSystemCoefficients(ifstream& file, int Mplus, int N,
                           double* b, double* a)
{
  int i = -1;
  string line, arg1, extraTest;
  stringstream ss;
  double value;

  while(getline(file, line))
  {
    if(i >= Mplus + N - 1) break;

    i++;

    ss.clear();
    ss.str("");
    ss << line;
    ss >> arg1;

    ss.clear();
    ss.str("");
    ss << arg1;

    if(ss >> value && !(ss >> extraTest))
    {
      if(i >= 0 && i <= Mplus - 1) b[i] = value;
      else a[i - Mplus] = value;
    }
    else break;
  }

  if(i != Mplus + N - 1) return false;
  return true;
}

bool getInitialConditions(ifstream& file, int Mplus, int N,
                          double* x, double* y)
{
  int i = -1;
  string line, arg1, extraTest;
  stringstream ss;
  double value;

  while(getline(file, line))
  {
    if(i >= Mplus + N - 1) break;

    i++;

    ss.clear();
    ss.str("");
    ss << line;
    ss >> arg1;

    ss.clear();
    ss.str("");
    ss << arg1;

    if(ss >> value && !(ss >> extraTest))
    {
      if(i >= 0 && i <= Mplus - 1) x[i] = value;
      else y[i - Mplus] = value;
    }
    else break;
  }

  if(i != Mplus + N - 1) return false;
  return true;
}

void computeSystem(double newValue, int Mplus, int N, double b[],
                   double a[], double* x, double* y)
{
  double yTerms = 0, xTerms = 0;

  for(int i = Mplus - 2; i >= 0; i--)
    x[i + 1] = x[i];

  x[0] = newValue;

  for(int i = 0; i < N; i++)
    yTerms -= a[i] * y[i];

  for(int i = 0; i < Mplus; i++)
    xTerms += b[i] * x[i];

  for(int i = N - 2; i >= 0; i--)
    y[i + 1] = y[i];

  y[0] = yTerms + xTerms;
}
