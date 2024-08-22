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
#include <vector>

#include "DEBUG.h"

using namespace std;

bool isValidLine(string line, double& signalValue,
                 bool firstLine = false)
{
  stringstream ss(line);

  string arg1, arg2;
  ss >> arg1;
  ss >> arg2;

  int start;
  string extraTest;
  stringstream ss1(arg1), ss2(arg2);

  if(ss1 >> signalValue && !(ss1 >> extraTest))
  {
    if(firstLine)
    {
      ss1.clear();
      ss1.str("");
      ss1 << arg1;

      if(ss1 >> start && !(ss1 >> extraTest) && ss2 >> signalValue &&
         !(ss2 >> extraTest)) return true;

      ss1.clear();
      ss1.str("");
      ss1 << arg1;

      ss1 >> signalValue;
    }
    return true;
  }
  return false;
}

bool getSignalValues(ifstream& file, vector<double>& s)
{
  int i = -1;
  string line;
  double signalValue;

  while(getline(file, line))
  {
    i++;

    if(i == 0 && !isValidLine(line, signalValue, true)) return false;
    if(i > 0 && !isValidLine(line, signalValue)) break;

    s.push_back(signalValue);
  }
  return true;
}
