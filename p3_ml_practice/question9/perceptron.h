#ifndef PERCEPTRON_H
#define PERCEPTRON_H

// implementation outlined by https://riptutorial.com/machine-learning/example/22618/implementing-a-perceptron-model-in-cplusplus
#include <vector>

using namespace std;

class perceptron
{
public:
  perceptron(float eta, int epochs);
  float netInput(vector<float> X);
  int predict(vector<float> X);

  // X is a training dataset or matrix of inputs
  void fit(vector<vector<float>> X, vector<float> y);

private:
  float bias;        // perceptron bias
  float m_eta;       // learning rate
  int m_epochs;      // number of epochs
  vector<float> m_w; // weights
};

#endif