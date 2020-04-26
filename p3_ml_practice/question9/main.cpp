#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "perceptron.h"
using namespace std;

void runAND();
void runOR();
void runXOR();

int main()
{
  // random seed
  srand(time(nullptr));

  // create file with basic data points for plotting
  ofstream pointsData;
  pointsData.open("points.dat");
  pointsData << "1 1\n0 1\n1 0\n0 0\n";
  pointsData.close();

  runAND();
  runOR();
  runXOR();

  return 0;
}

void runAND()
{
  vector<vector<float>> trainingData = {
      {1, 1},
      {1, 0},
      {0, 1},
      {0, 0},
  };
  vector<float> trainingOutput = {1, 0, 0, 0};
  string plotCmd = "gnuplot -p -e \"set title 'AND results'; set xlabel 'Input0'; set ylabel 'Input1'; ";
  plotCmd += "set xrange [-0.4:1.4]; set yrange [-0.4:1.4]; plot 'points.dat' title 'Training Input'";

  for (int i = 0; i < 5; i++)
  {
    perceptron p(0.1);
    p.train(trainingData, trainingOutput, 100);
    plotCmd += ", " + p.getLineEquation();
  }

  // close off command
  plotCmd += ";\"";

  system(plotCmd.c_str());
}

void runOR()
{
  vector<vector<float>> trainingData = {
      {1, 1},
      {1, 0},
      {0, 1},
      {0, 0},
  };
  vector<float> trainingOutput = {1, 1, 1, 0};
  string plotCmd = "gnuplot -p -e \"set title 'OR results'; set xlabel 'Input0'; set ylabel 'Input1'; ";
  plotCmd += "set xrange [-0.4:1.4]; set yrange [-0.4:1.4]; plot 'points.dat' title 'Training Input'";

  for (int i = 0; i < 5; i++)
  {
    perceptron p(0.1);
    p.train(trainingData, trainingOutput, 100);
    plotCmd += ", " + p.getLineEquation();
  }

  // close off command
  plotCmd += ";\"";

  system(plotCmd.c_str());
}

void runXOR()
{
  vector<vector<float>> trainingData = {
      {1, 1},
      {1, 0},
      {0, 1},
      {0, 0},
  };
  vector<float> trainingOutput = {0, 1, 1, 0};
  string plotCmd = "gnuplot -p -e \"set title 'XOR results'; set xlabel 'Input0'; set ylabel 'Input1'; ";
  plotCmd += "set xrange [-0.4:1.4]; set yrange [-0.4:1.4]; plot 'points.dat' title 'Training Input'";

  for (int i = 0; i < 5; i++)
  {
    perceptron p(0.1);
    p.train(trainingData, trainingOutput, 100);
    plotCmd += ", " + p.getLineEquation();
  }

  // close off command
  plotCmd += ";\"";

  system(plotCmd.c_str());
}