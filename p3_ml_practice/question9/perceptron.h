#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <utility>
#include <iostream>

class perceptron
{
public:
  perceptron(float _alpha);
  float calcProb(const std::vector<float> &input);
  int output(const std::vector<float> &input);
  void learn(const std::vector<float> &tInput, float tOutput);
  void train(const std::vector<std::vector<float>> &tInput, const std::vector<float> &tOutput, int numCycles);
  void print();

private:
  float alpha;                // learning rate
  float bias;                 // bias (threshold unit)
  std::vector<float> weights; // weight of inputs
};

#endif
