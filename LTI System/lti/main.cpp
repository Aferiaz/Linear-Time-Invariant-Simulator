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

#include "system.h"
#include "signal.h"
#include "DEBUG.h"

using namespace std;

int main(int argc, char** argv)
{
  ofstream logFile;
  bool skipLine = true, systemActive = false;
  int Mplus = 0, N = 0;

  double* b = new double[Mplus];
  double* a = new double[N];
  double* x = new double[Mplus];
  double* y = new double[N];

  cout << "Project 3: Linear Time-Invariant System Simulator" << endl;
  cout << "ENGG 151.01 - A" << endl;
  cout << "By: Andreas Josef C. Diaz" << endl;
  cout << "    Marc Jefferson B. Obeles" << endl;
  cout << "    Justin Gabriel M. Sy" << endl;
  cout << endl << "Type 'help' for list of commands" << endl;

  logFile.open("ltisim-log.txt", ios_base::app);

  if(!logFile.is_open())
    cout << endl << "Warning: Unable to open log file" << endl;

  while(true)
  {
    if(skipLine) cout << endl;

    skipLine = true;

    ifstream file;
    string line, arg1, arg2, filename;

    getline(cin, line);

    stringstream ss(line);
    ss >> arg1;
    ss >> arg2;

    stringstream ss1(arg1), ss2(arg2);

    if(arg1 == "help")
    {
      cout << endl << "help\t\t\t\tProvides information on "
           << "application use" << endl;
      cout << "system [filename]\t\tExtracts coefficients of LTI "
           << "system from specified filename" << endl;
      cout << "signal [filename]\t\tExtracts signal from specified "
           << "filename" << endl;
      cout << "clear\t\t\t\tClears memory of previous inputs and "
           << "outputs" << endl;
      cout << "exit\t\t\t\tExits application" << endl;
      cout << "[any floating point number]\tTreats specified "
           << "floating point number as next input to the system"
           << endl;
      cout << "cls\t\t\t\tClears screen" << endl;
      cout << "initcond [filename]\t\tExtracts initial conditions "
           << "from specified filename" << endl;
    }
    else if(arg1 == "system")
    {
      if(!(ss2 >> filename))
      {
        cout << "Syntax Error: system [filename]" << endl;
        continue;
      }

      file.open(filename);

      if(!file.is_open())
      {
        cout << "Error: Unable to open system file" << endl;
        continue;
      }

      int Mplus_tmp;
      int N_tmp;

      if(!getSystemParameters(file, Mplus_tmp, N_tmp))
      {
        cout << "Error: Invalid system file parameters" << endl;
        file.close();
        continue;
      }

      double* b_tmp = new double[Mplus_tmp];
      double* a_tmp = new double[N_tmp];

      if(!getSystemCoefficients(file, Mplus_tmp, N_tmp, b_tmp, a_tmp))
      {
        cout << "Error: Invalid system file coefficients" << endl;
        file.close();
        continue;
      }

      file.close();

      Mplus = Mplus_tmp;
      N = N_tmp;

      delete[] b;
      b = b_tmp;

      delete[] a;
      a = a_tmp;

      double* x_tmp = new double[Mplus];
      delete[] x;
      x = x_tmp;

      double* y_tmp = new double[Mplus];
      delete[] y;
      y = y_tmp;

      logFile << "new system" << endl;
      logFile << Mplus << endl;
      logFile << N << endl;

      for(int i = 0; i < Mplus; i++)
      {
        x[i] = 0.0;
        logFile << b[i] << endl;
      }

      for(int i = 0; i < N; i++)
      {
        y[i] = 0.0;
        logFile << a[i] << endl;
      }

      logFile << "ready" << endl;

      systemActive = true;

      cout << endl << "Mplus:\t" << Mplus << endl;
      cout << "N:\t" << N << endl;

      #ifdef DEBUG
        cout << endl;

        for(int i = 0; i < Mplus; i++)
          cout << "b[" << i << "]:\t" << b[i] << endl;

        cout << endl;

        for(int i = 0; i < N; i++)
          cout << "a[" << i + 1 << "]:\t" << a[i] << endl;
      #endif
    }
    else if(arg1 == "signal")
    {
      if(!systemActive)
      {
        cout << "Error: System not yet specified" << endl;
        continue;
      }

      if(!(ss2 >> filename))
      {
        cout << "Syntax Error: signal [filename]" << endl;
        continue;
      }

      file.open(filename);

      if(!file.is_open())
      {
        cout << "Error: Unable to open signal file" << endl;
        continue;
      }

      vector<double> s;

      if(!getSignalValues(file, s))
      {
        cout << "Error: Invalid signal file" << endl;
        file.close();
        continue;
      }

      file.close();

      cout << endl;

      if(s.size() > 30) cout << "Signals extracted" << endl;

      for(int i = 0; i < s.size(); i++)
      {
        computeSystem(s[i], Mplus, N, b, a, x, y);

        logFile << x[0] << " \t" << y[0] << endl;

        if(s.size() <= 30)
          cout << x[0] << " \t" << y[0] << endl;
      }
    }
    else if(arg1 == "clear")
    {
      if(!systemActive)
      {
        cout << "Error: System not yet specified" << endl;
        continue;
      }

      for(int i = 0; i < Mplus; i++) x[i] = 0.0;
      for(int i = 0; i < N; i++) y[i] = 0.0;

      logFile << "clear" << endl;

      cout << endl << "Memory cleared of previous inputs and outputs"
           << endl;

     #ifdef DEBUG
        cout << endl;

        for(int i = 0; i < Mplus; i++)
          cout << "x[" << -i - 1 << "]:\t" << x[i] << endl;

        cout << endl;

        for(int i = 0; i < N; i++)
          cout << "y[" << -i - 1 << "]:\t" << y[i] << endl;
      #endif
    }
    else if(arg1 == "exit")
    {
      logFile.close();
      return 0;
    }
    else if(arg1 == "cls")
    {
      system("CLS");

      skipLine = false;
    }
    else if(arg1 == "initcond")
    {
      if(!systemActive)
      {
        cout << "Error: System not yet specified" << endl;
        continue;
      }

      if(!(ss2 >> filename))
      {
        cout << "Syntax Error: initcond [filename]" << endl;
        continue;
      }

      file.open(filename);

      if(!file.is_open())
      {
        cout << "Error: Unable to open initial conditions file"
             << endl;
        continue;
      }

      double* x_tmp = new double[Mplus];
      double* y_tmp = new double[N];

      if(!getInitialConditions(file, Mplus, N, x_tmp, y_tmp))
      {
        cout << "Error: Invalid initial conditions file values"
             << endl;
        file.close();
        continue;
      }

      file.close();

      delete[] x;
      x = x_tmp;

      delete[] y;
      y = y_tmp;

      logFile << "initial conditions reset" << endl;

      for(int i = 0; i < Mplus; i++)
        logFile << x[i] << endl;

      for(int i = 0; i < N; i++)
        logFile << y[i] << endl;

      logFile << "ready" << endl;

      cout << endl << "Initial conditions extracted" << endl;

      #ifdef DEBUG
        cout << endl;

        for(int i = 0; i < Mplus; i++)
          cout << "x[" << -i - 1 << "]:\t" << x[i] << endl;

        cout << endl;

        for(int i = 0; i < N; i++)
          cout << "y[" << -i - 1 << "]:\t" << y[i] << endl;
      #endif
    }
    else
    {
      double number;
      string extraTest;

      if(!(ss1 >> number && !(ss1 >> extraTest)))
      {
        cout << "Error: Unknown command. Type 'help' for list of "
                << "commands" << endl;
        continue;
      }

      if(!systemActive)
      {
        cout << "Error: System not yet specified" << endl;
        continue;
      }

      computeSystem(number, Mplus, N, b, a, x, y);

      logFile << x[0] << " \t" << y[0] << endl;

      cout << endl << y[0] << endl;
    }
  }
  return 0;
}
