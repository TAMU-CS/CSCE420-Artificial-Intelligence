#ifndef CLAUSE_H
#define CLAUSE_H

#include "literal.h"
#include "parser.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Clause
{
private:
  vector<Literal> get_literals(string);

public:
  vector<Literal> pos;
  vector<Literal> neg;
  int num;

  // input is lisp representation:
  // ex: (1 ( (P X Y) (R (F X)) ) ( (Q X (A)) )  )
  Clause(string);

  // override ostream operator<< for printing out
  friend ostream &operator<<(ostream &, const Clause &);
};

#endif
