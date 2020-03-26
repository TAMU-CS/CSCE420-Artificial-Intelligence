#include "clause.h"
using namespace std;

vector<Literal> Clause::get_literals(string info)
{
  vector<Literal> literals;

  if (info == "nil")
  {
    return literals;
  }

  vector<string> parsedInfo = Parser::parse_terms(info.substr(1, info.size() - 2));
  for(int i = 0; i < parsedInfo.size(); i++){
    Literal literal(parsedInfo[i]);
    literals.push_back(literal);
  }

  return literals;
}

Clause::Clause(string info)
{
  // create list of strings
  // info takes the format [num, pos, neg]
  info = info.substr(1, info.size() - 2);
  vector<string> varList = Parser::parse_terms(info);

  num = stoi(varList[0]);
  pos = get_literals(varList[1]);
  neg = get_literals(varList[2]);
}

ostream &operator<<(ostream &os, const Clause &clause)
{
  os << "num: " << clause.num << endl;

  os << "pos: [";
  for (int i = 0; i < clause.pos.size(); i++)
  {
    if (i == clause.pos.size() - 1)
    {
      os << clause.pos[i];
    }
    else
    {
      os << clause.pos[i] << ", ";
    }
  }
  os << "]\n";

  os << "neg: [";
  for (int i = 0; i < clause.neg.size(); i++)
  {
    if (i == clause.neg.size() - 1)
    {
      os << clause.neg[i];
    }
    else
    {
      os << clause.neg[i] << ", ";
    }
  }
  os << "]\n";

  return os;
}
