#include "perceptron.h"

perceptron::perceptron(float eta, int epochs)
{
  // set private variables
  m_epochs = epochs;
  m_eta = eta;
}

int perceptron::predict(vector<float> X)
{
  return netInput(X) > 0 ? 1 : -1; // Step function
}

float perceptron::netInput(vector<float> X)
{
  // p = X * wT + bias
  float prob = bias;

  // matrix mutliplication X * wT
  for (int i = 0; i < X.size(); i++)
  {
    prob += X[i] * m_w[i];
  }

  return prob;
}

void perceptron::fit(vector<vector<float>> X, vector<float> y)
{
  // Initialize bias to 0, and weights to 0
  bias = 0;
  for (int i = 0; i < X[0].size(); i++)
  {
    m_w.push_back(0);
  }

  for (int i = 0; i < m_epochs; i++)
  { // for each epoch
    for (int j = 0; j < X.size(); j++)
    { // for each vector in training matrix

      // calculate change to add to weightsg=
      float update = m_eta * (y[j] - predict(X[j]));
      for (int w = 0; w < m_w.size(); w++)
      { // update each weight
        m_w[w] += update * X[j][w];
      }
      bias = update; // update the bias term
    }
  }
}
