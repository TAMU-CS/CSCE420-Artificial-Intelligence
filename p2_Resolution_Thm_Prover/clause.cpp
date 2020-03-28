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
  for (int i = 0; i < parsedInfo.size(); i++)
  {
    Literal literal(parsedInfo[i], vars);
    literals.push_back(literal);
  }

  return literals;
}

Clause::Clause(string info)
{
  value = info;

  // create list of strings
  // info takes the format [num, pos, neg]
  info = info.substr(1, info.size() - 2);
  vector<string> varList = Parser::parse_terms(info);

  num = stoi(varList[0]);
  pos = get_literals(varList[1]);
  neg = get_literals(varList[2]);
}

void Clause::substitute(unordered_map<string, Unifiable *> sub)
{
  for (auto it : sub)
  {
    for (auto literal : pos)
    {
      literal.root->substitute(it.first, it.second, 0);
    }

    for (auto literal : neg)
    {
      literal.root->substitute(it.first, it.second, 0);
    }
  }
}

void Clause::add(Clause &c2)
{
  for (auto Literal : c2.pos)
  {
    pos.push_back(Literal);
  }

  for (auto Literal : c2.neg)
  {
    neg.push_back(Literal);
  }

  stringstream ss;
  ss << (*this);
  getline(ss, value);
}

string Clause::toStringNoNum()
{

  // proper variable output
  int oldVarNum = Variable::varNum;
  Variable::varNum = 0;
  Clause temp(value);
  Variable::varNum = oldVarNum;

  // make clause generic
  // sort literals;
  temp.num = 0;
  sort(temp.pos.begin(), temp.pos.end(), Literal::Comparator);
  sort(temp.neg.begin(), temp.neg.end(), Literal::Comparator);

  string tempValue;
  stringstream ss;
  ss << temp;
  getline(ss, tempValue);
  return tempValue;
}

ostream &operator<<(ostream &os, const Clause &clause)
{
  os << "(" << clause.num << " ";

  if (clause.pos.size() == 0)
  {
    os << "nil ";
  }
  else
  {
    os << "(";
    for (int i = 0; i < clause.pos.size(); i++)
    {
      if (i == clause.pos.size() - 1)
      {
        os << clause.pos[i];
      }
      else
      {
        os << clause.pos[i] << " ";
      }
    }
    os << ") ";
  }

  if (clause.neg.size() == 0)
  {
    os << "nil";
  }
  else
  {
    os << "(";
    for (int i = 0; i < clause.neg.size(); i++)
    {
      if (i == clause.neg.size() - 1)
      {
        os << clause.neg[i];
      }
      else
      {
        os << clause.neg[i] << " ";
      }
    }

    os << ")";
  }
  os << ")";

  return os;
}
