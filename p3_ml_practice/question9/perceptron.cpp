#include "perceptron.h"
using namespace std;

perceptron::perceptron(float _alpha)
{
  alpha = _alpha;
}

float perceptron::calcProb(const vector<float> &input)
{
  float prob = bias;
  for (int i = 0; i < input.size(); i++)
  {
    prob += (input[i] * weights[i]);
  }

  return prob;
}

int perceptron::output(const vector<float> &input)
{ // if prob is greater than or equal to 0, then return 1, else return 0
  return calcProb(input) >= 0.0 ? 1 : 0;
}

void perceptron::learn(const vector<float> &tInput, float tOutput)
{ // adjust weights based off Err = desiredOutput - NetworkOutput
  float networkOutput = output(tInput);
  float error = tOutput - networkOutput;

  // first weight adjustment
  bias += alpha * error;

  for (int i = 0; i < tInput.size(); i++)
  { // adjust weights: Wij = Wij + alpha * Ij * Err
    weights[i] += alpha * tInput[i] * error;
  }
}

void perceptron::train(const vector<vector<float>> &tInput, const vector<float> &tOutput, int numCycles)
{ // train on a set of input
  // initialize the weight array
  weights = vector<float>(tInput[0].size(), 0.0);
  bias = 0;

  for (int j = 0; j < numCycles; j++)
  {
    for (int i = 0; i < tInput.size(); i++)
    {
      learn(tInput[i], tOutput[i]);
    }
  }
}

void perceptron::print()
{
  cout << "P: " << bias << " ";
  for (auto it : weights)
  {
    cout << it << " ";
  }
  cout << endl;
}
