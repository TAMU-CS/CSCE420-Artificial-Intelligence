#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <numeric>
using namespace std;

double info_gain(const vector<int> &parent, const vector<vector<int>> &attrib);
double entropy(const vector<int> &set);

int main()
{
  vector<vector<int>> input;

  string temp;
  while (getline(cin, temp))
  {
    stringstream ss(temp);
    int entry;
    vector<int> arr;
    while (ss >> entry)
    {
      arr.push_back(entry);
    }

    input.push_back(arr);
  }

  vector<int> parent = input[0];
  input.erase(input.begin());
  double result = info_gain(parent, input);

  cout << result << endl;
  return 0;
}

double info_gain(const vector<int> &parent, const vector<vector<int>> &attrib)
{
  // info_gain(E, A) = Entropy(E) - sum for all v [|Ev|Entropy(Ev)/|E|]
  double info_gain = entropy(parent);
  double eAmnt = accumulate(parent.begin(), parent.end(), 0.0);
  for (auto it : attrib)
  {
    double entropyEv = entropy(it);
    double evAmnt = accumulate(it.begin(), it.end(), 0.0);
    double val = (entropyEv * evAmnt) / eAmnt;
    info_gain -= val;
  }

  return info_gain;
}

double entropy(const vector<int> &set)
{
  double sum = accumulate(set.begin(), set.end(), 0.0);

  double entropy = 0;
  for (auto it : set)
  {
    if (it > 0.0)
    { // prevent case of log2(0.0)
      double prob = ((double)it) / sum;
      entropy -= prob * log2(prob);
    }
  }

  return entropy;
}
