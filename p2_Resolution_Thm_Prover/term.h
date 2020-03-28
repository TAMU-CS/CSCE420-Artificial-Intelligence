#ifndef TERM_H
#define TERM_H

#include "parser.h"

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <unordered_map>

using namespace std;

class Unifiable
{
public:
  string name;
  vector<Unifiable *> args;

  Unifiable(string);

  static Unifiable* get_unifiable(string, unordered_map<string, Unifiable*>&);
  static bool Comparator(Unifiable*, Unifiable*);

  virtual void substitute(string, Unifiable*, int) = 0;
  virtual bool occurs(Unifiable *) const;
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

  void substitute(string, Unifiable*, int){};
  void serialize(ostream &) const;
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
  static int varNum;

  void substitute(string, Unifiable*, int){};
  friend ostream &operator<<(ostream &os, const Variable &variable)
  {
    variable.serialize(os);
    return os;
  }
};

class Function : public Unifiable
{
public:

  Function(vector<string>, unordered_map<string, Unifiable*>&);

  void substitute(string, Unifiable*, int);
  bool occurs(Unifiable *v) const;
  void serialize(ostream &) const;
  friend ostream &operator<<(ostream &os, const Function &function)
  {
    function.serialize(os);
    return os;
  }
};

#endif
