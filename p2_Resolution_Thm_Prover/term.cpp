#include "term.h"
using namespace std;

Unifiable::Unifiable(string _name)
{
  name = _name;
}

Unifiable *Unifiable::get_unifiable(string info)
{
  vector<string> varList = Parser::parse_terms(info);

  if (varList.size() > 1)
  {
    return new Function(varList);
  }
  else
  {
    if (info[0] == '(')
    {
      return new Constant(info.substr(1, info.size() - 2));
    }
    else
    {
      return new Variable(info);
    }
  }
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

Variable::Variable(string _name) : Unifiable(_name)
{
}

Function::Function(vector<string> varList) : Unifiable(varList[0])
{
  for (int i = 1; i < varList.size(); i++)
  {
    Unifiable *unifiable = Unifiable::get_unifiable(varList[i]);
    args.push_back(unifiable);
  }
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
      cout << *(args[i]);
    }
    else
    {
      cout << *(args[i]) << " ";
    }
  }

  os << ")";
}
