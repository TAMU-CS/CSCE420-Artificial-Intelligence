#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Unifiable
{
public:
  string name;

  Unifiable(string);

  virtual void serialize(ostream &) const;
  friend ostream &operator<<(ostream &os, const Unifiable &unifiable)
  {
    unifiable.serialize(os);
    return os;
  }
};

class Constant : public Unifiable
{
public:
  Constant(string);
  
  friend ostream &operator<<(ostream &os, const Constant &constant)
  {
    constant.serialize(os);
    return os;
  }
};

class Variable : public Unifiable
{
public:
  Variable(string);

  friend ostream &operator<<(ostream &os, const Variable &variable)
  {
    variable.serialize(os);
    return os;
  }
};

class Function : public Unifiable
{
public:
  vector<Unifiable> args;

  Function(string);

  void serialize(ostream &) const;
  friend ostream &operator<<(ostream &os, const Function &function)
  {
    function.serialize(os);
    return os;
  }  
};

#endif
