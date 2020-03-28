#include "term.h"
using namespace std;

Unifiable::Unifiable(string _name)
{
  name = _name;
}

Unifiable *Unifiable::get_unifiable(string info, unordered_map<string, Unifiable *> &vars)
{
  vector<string> varList = Parser::parse_terms(info);
  if (varList.size() > 1)
  {
    return new Function(varList, vars);
  }
  else
  {
    if (info[0] == '(')
    {
      string infoNoParenthesis = info.substr(1, info.size() - 2);
      vector<string> testList = Parser::parse_terms(infoNoParenthesis);
      if (testList.size() == 1)
      {
        return new Constant(infoNoParenthesis);
      }
      else
      {
        return new Function(testList, vars);
      }
    }
    else
    {
      if (vars.find(info) == vars.end())
      {
        vars[info] = new Variable(info);
        return vars[info];
      }
      else
      {
        return vars[info];
      }
    }
  }
}

bool Unifiable::Comparator(Unifiable*, Unifiable*){
  
}

bool Unifiable::occurs(Unifiable *v) const
{
  return typeid(*this) == typeid(Variable) && typeid(*v) == typeid(Variable) && v->name == name;
}

void Unifiable::serialize(ostream &os) const
{
  os << name;
}

Constant::Constant(string _name) : Unifiable(_name)
{
}

void Constant::serialize(ostream &os) const
{
  os << "(" << name << ")";
}

int Variable::varNum = 0;

Variable::Variable(string _name) : Unifiable(to_string(varNum))
{
  varNum++;
}

void Function::substitute(string key, Unifiable *rep, int start)
{
  for (int i = start; i < args.size(); i++)
  {
    if (typeid(*args[i]) == typeid(Variable) && args[i]->name == key)
    {
      args[i] = rep;
    }
    else if (typeid(*args[i]) == typeid(Function))
    {
      args[i]->substitute(key, rep, 0);
    }
  }
}

Function::Function(vector<string> varList, unordered_map<string, Unifiable *> &vars) : Unifiable(varList[0])
{
  for (int i = 1; i < varList.size(); i++)
  {
    Unifiable *unifiable = Unifiable::get_unifiable(varList[i], vars);
    args.push_back(unifiable);
  }
}

bool Function::occurs(Unifiable *v) const
{
  bool occurs = false;
  for (int i = 0; i < args.size(); i++)
  {
    occurs = occurs || args[i]->occurs(v);
  }

  return occurs;
}

void Function::serialize(ostream &os) const
{
  os << "(";
  Unifiable::serialize(os);
  os << " ";

  for (int i = 0; i < args.size(); i++)
  {
    if (i == args.size() - 1)
    {
      os << *(args[i]);
    }
    else
    {
      os << *(args[i]) << " ";
    }
  }

  os << ")";
}
