#include <iostream>
#include <vector>
#include "perceptron.h"
using namespace std;

void runAND();
void runOR();
void runXOR();

int main()
{
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
  perceptron p(0.1);
  p.train(trainingData, trainingOutput, 100);
  p.print();
  cout << "results for AND:" << endl;
  for (int i = 0; i < trainingData.size(); i++)
  {
    cout << p.output(trainingData[i]) << " ";
  }
  cout << endl
       << endl;
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
  perceptron p(0.1);
  p.train(trainingData, trainingOutput, 100);
  p.print();
  cout << "results for OR:" << endl;
  for (int i = 0; i < trainingData.size(); i++)
  {
    cout << p.output(trainingData[i]) << " ";
  }
  cout << endl
       << endl;
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
  perceptron p(0.1);
  p.train(trainingData, trainingOutput, 100);
  p.print();
  cout << "results for XOR:" << endl;
  for (int i = 0; i < trainingData.size(); i++)
  {
    cout << p.output(trainingData[i]) << " ";
  }
  cout << endl
       << endl;
}