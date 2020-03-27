#include "literal.h"

Literal::Literal(string info, unordered_map<string, Unifiable*> &vars)
{
  value = info.substr(1, info.size() - 2);

  root = Unifiable::get_unifiable(value, vars);
}

unordered_map<string, Unifiable *> Literal::unify(Unifiable *e1, Unifiable *e2)
{
  if (typeid(*e1) == typeid(Constant) || typeid(*e1) == typeid(Variable) 
  || typeid(*e2) == typeid(Constant) || typeid(*e2) == typeid(Variable))
  { // e1 or e2 is a variable or constant:
    if (typeid(*e1) == typeid(*e2) && e1->name == e2->name)
    { // e1 and e2 are identical:
      return unordered_map<string, Unifiable *>();
    }
    else if (typeid(*e1) == typeid(Variable))
    { // e1 is a variable:
      if (e2->occurs(e1))
      { // e1 occurs in e2:
        throw 0;
      }
      else
      {
        unordered_map<string, Unifiable *> sub;
        sub[e1->name] = e2;
        return sub;
      }
    }
    else if (typeid(*e2) == typeid(Variable))
    { // e2 is a variable:
      if (e1->occurs(e2))
      { // e2 occurs in e1:
        throw 1;
      }
      else
      {
        unordered_map<string, Unifiable *> sub;
        sub[e2->name] = e1;
        return sub;
      }
    }
    else
    {
      throw 2;
    }
  }

  if (!(typeid(*e1) == typeid(Function) && typeid(*e2) == typeid(Function)))
  { // e1 and e2 are not functions:
    throw 3;
  }

  if (e1->name != e2->name)
  { // predicate symbol (function name) must be same
    throw 4;
  }

  if (e1->args.size() != e2->args.size())
  { // different number of function arguments
    throw 5;
  }

  unordered_map<string, Unifiable *> subAll;
  for (int i = 0; i < e1->args.size(); i++)
  { // for all arguments in e1 and e2
    unordered_map<string, Unifiable *> sub = unify(e1->args[i], e2->args[i]);

    for (auto it : sub)
    { // for all substitutions in substituation set "sub"

      // apply substituion to remainder of e1 and e2
      e1->substitute(it.first, it.second, i);
      e2->substitute(it.first, it.second, i);

      // append substitution to subAll
      subAll[it.first] = it.second;
    }
  }

  return subAll;
}

ostream &operator<<(ostream &os, const Literal &literal)
{
  os << *(literal.root);
  return os;
}
