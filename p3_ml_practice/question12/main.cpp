#include <iostream>
#include <vector>

//#include "../matplotlibcpp.h"
using namespace std;

//namespace plt = matplotlibcpp;

float deltaW(float w, float alpha);
void gradientDescent(float w, float alpha);

int main()
{
  // simulate the gradient descent steps for E(w) = (w + 1)(w − 1)(w − 3)(w − 4)
  // with varying w values between -2 and 6
  vector<float> wVals = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
  vector<float> alphaVals = {0.01, 0.02, 0.03, 0.04, 0.05};
  gradientDescent(wVals[0], alphaVals[0]);

  return 0;
}

void gradientDescent(float w, float alpha)
{
  for (int i = 0; i < 10; i++)
  {
    float changeW = deltaW(w, alpha);
    w += changeW;
    cout << w << " " << changeW << endl;
  }
}

float deltaW(float w, float alpha)
{ // deltaW = -alpha * dE/dw = -alpha * 4w^3 - 21w^2 + 22w + 7; alpha is learning rate
  return -1.0 * alpha * (4.0 * w * w * w - 21.0 * w * w + 22.0 * w + 7.0);
}
