#include "clause.h"
using namespace std;

vector<Literal> Clause::get_literals(string info)
{
  vector<Literal> literals;

  if (info == "nil")
  {
    return literals;
  }

  int first = 0;
  int last = 0;

  // iterate through parenthesis and add them to literals
  while (last < info.size())
  {
    // ignore white space, and extra parenthesis
    while (last < info.size() && (isspace(info[last]) || info[last] == '(' || info[last] == ')'))
    {
      last++;
    }
    if (last == info.size())
    {
      break;
    }

    int leftCount = 1;
    int rightCount = 0;
    first = last;

    // isolate the literal substring
    while (leftCount > rightCount)
    {
      if (info[last] == '(')
      {
        leftCount++;
      }
      else if (info[last] == ')')
      {
        rightCount++;
      }
      last++;
    }

    Literal literal(info.substr(first, last - first - 1));
    literals.push_back(literal);
    last++;
  }

  return literals;
}

Clause::Clause(string info)
{
  // create list of strings
  // info takes the format [num, pos, neg]
  vector<string> varList;
  info = info.substr(1, info.size() - 2);

  // parse and divide info string into the three elements
  int first = 0;
  int last = 0;
  while (last < info.size())
  {
    // ignore white space
    while (last < info.size() && isspace(info[last]))
    {
      last++;
    }
    if (last == info.size())
    {
      break;
    }

    first = last;
    if (info[first] == '(')
    {
      int leftCount = 1;
      int rightCount = 0;
      last++;
      while (leftCount > rightCount)
      {
        if (info[last] == '(')
        {
          leftCount++;
        }
        else if (info[last] == ')')
        {
          rightCount++;
        }
        last++;
      }
      varList.push_back(info.substr(first, last - first));
    }
    else
    {
      // ignore white space
      while (last < info.size() && !isspace(info[last]))
      {
        last++;
      }
      varList.push_back(info.substr(first, last - first));
    }

    last++;
  }

  num = stoi(varList[0]);
  pos = get_literals(varList[1]);
  neg = get_literals(varList[2]);
}

ostream& operator<<(ostream& os, const Clause& clause)
{
  os << "num: " << clause.num << endl;

  os << "pos: [";
  for(int i = 0; i < clause.pos.size(); i++){
    if(i == clause.pos.size() - 1){
      os << clause.pos[i];
    }else{
      os << clause.pos[i] << ", ";
    }
  }
  os << "]\n";

  os << "neg: [";
  for(int i = 0; i < clause.neg.size(); i++){
    if(i == clause.neg.size() - 1){
      os << clause.neg[i];
    }else{
      os << clause.neg[i] << ", ";
    }
  }
  os << "]\n";

  return os;
}
