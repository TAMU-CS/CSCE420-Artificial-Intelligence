#ifndef CLAUSE_H
#define CLAUSE_H

#include "literal.h"
#include "parser.h"

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Clause
{
private:
  vector<Literal> get_literals(string);

public:
  unordered_map<string, Unifiable *> vars;
  vector<Literal> pos;
  vector<Literal> neg;
  int num;
  string value;

  // input is lisp representation:
  // ex: (1 ( (P X Y) (R (F X)) ) ( (Q X (A)) )  )
  Clause(string);

  void substitute(unordered_map<string, Unifiable *>);
  void add(Clause &);

  // override ostream operator<< for printing out
  string toStringNoNum();
  friend ostream &operator<<(ostream &, const Clause &);
};

#endif
