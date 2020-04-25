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
  int numExamples, numAttribs;
  string goalName;
  vector<string> attribNames;
  vector<vector<string>> attribVals;
  vector<string> examples;
  string temp;
  cin >> numExamples >> numAttribs >> goalName;

  for (int i = 0; i < numExamples; i++)
  { // get examples
    cin >> temp;
    examples.push_back(temp);
  }

  for (int i = 0; i < numAttribs; i++)
  { // get attributes names
    cin >> temp;
    attribNames.push_back(temp);
  }

  for (int i = 0; i < numExamples; i++)
  { // get attribute values
    vector<string> tempArr;
    for (int j = 0; j < numAttribs; j++)
    {
      cin >> temp;
      tempArr.push_back(temp);
    }
    attribVals.push_back(tempArr);
  }

  unordered_map<string, int> goalValuesIndex; // track id for each goal value
  vector<int> parent;                         // count for each different example result
  int count = 0;
  for (int i = 0; i < examples.size(); i++)
  { // for all example goal values
    string exRes = examples[i];
    if (goalValuesIndex.find(exRes) == goalValuesIndex.end())
    { // example goal value does not exist
      goalValuesIndex[exRes] = count;
      parent.push_back(1);
      count++;
    }
    else
    {
      parent[goalValuesIndex[exRes]]++;
    }
  }

  for (int i = 0; i < attribNames.size(); i++)
  { // for all attributes
    unordered_map<string, vector<int>> attribValToGoalCount;
    for (int j = 0; j < examples.size(); j++)
    { // for all example values for that attribute
      string attribVal = attribVals[j][i];
      if (attribValToGoalCount.find(attribVal) == attribValToGoalCount.end())
      { // attribute value isn't recorded
        int goalValueIndex = goalValuesIndex[examples[j]];
        attribValToGoalCount[attribVal] = vector<int>(parent.size(), 0); // set to empty goal count
        attribValToGoalCount[attribVal][goalValueIndex]++;               // increment proper goal value recording
      }
      else
      {
        int goalValueIndex = goalValuesIndex[examples[j]];
        attribValToGoalCount[attribVal][goalValueIndex]++; // increment proper goal value recording
      }
    }

    vector<vector<int>> attribGoalCount;
    for (auto it : attribValToGoalCount)
    { // for all possible attrib values
      attribGoalCount.push_back(it.second);
    }

    cout << attribNames[i] << " " << info_gain(parent, attribGoalCount) << endl;
  }

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
