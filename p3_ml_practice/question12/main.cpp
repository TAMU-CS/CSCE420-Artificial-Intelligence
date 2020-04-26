#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

//#include "../matplotlibcpp.h"
using namespace std;

//namespace plt = matplotlibcpp;

float deltaW(float w, float alpha);
void gradientDescent(float w, float alpha);
float functionW(float w);

int main()
{
  // simulate the gradient descent steps for E(w) = (w + 1)(w − 1)(w − 3)(w − 4)
  // with varying w values between -2 and 6
  srand(time(nullptr));
  float w = 6.0; //8 * ((float)rand() / RAND_MAX) - 2;
  vector<float> alphaVals = {0.001, 0.002, 0.005, 0.01, 0.05};

  for (auto it : alphaVals)
  { // for all alpha values
    string plotCmd = "gnuplot -p -e \"set title 'XOR results'; set xlabel 'Input0'; set ylabel 'Input1'; ";

    // generate data points
    gradientDescent(w, it);
  }

  return 0;
}

void gradientDescent(float w, float alpha)
{ // output data points

  ofstream pointsData;
  pointsData.open("points.dat");

  string plotCmd = "gnuplot -p -e \"set title 'Gradient Descent of E(w)=(x+1)*(x-1)*(x-3)*(x-4) and alpha=";
  plotCmd += to_string(alpha) + " w=" + to_string(w) + "'; ";
  plotCmd += "set xlabel 'w'; set ylabel 'E(w)'; set xrange [] writeback; ";
  plotCmd += "set yrange [] writeback; plot 'points.dat' title 'w points', ";
  plotCmd += "(x+1)*(x-1)*(x-3)*(x-4) title 'E(w)'; ";
  plotCmd += "set yrange restore; set xrange restore;\"";

  // output first point
  pointsData << w << " " << functionW(w) << endl;
  for (int i = 0; i < 10; i++)
  {
    w += deltaW(w, alpha);
    pointsData << w << " " << functionW(w) << endl;
  }

  pointsData.close();

  system(plotCmd.c_str());
}

float functionW(float w)
{ // returns actual value of function E(w) = (w + 1)(w − 1)(w − 3)(w − 4)
  return (w + 1.0) * (w - 1.0) * (w - 3.0) * (w - 4.0);
}

float deltaW(float w, float alpha)
{ // deltaW = -alpha * dE/dw = -alpha * 4w^3 - 21w^2 + 22w + 7; alpha is learning rate
  return -1.0 * alpha * (4.0 * w * w * w - 21.0 * w * w + 22.0 * w + 7.0);
}
