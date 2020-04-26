#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <utility>
#include <string>
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
  std::string getLineEquation();

private:
  float alpha;                // learning rate
  float bias;                 // bias (threshold unit)
  std::vector<float> weights; // weight of inputs
  float getRandomWeight();    // return float between -0.5 and 0.5
};

#endif
