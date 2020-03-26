#ifndef CLAUSE_H
#define CLAUSE_H

#include "literal.h"

#include <vector>
#include <string>

using namespace std;

class Clause{
  public:
  vector<Literal> pos;
  vector<Literal> neg;
  int num;

  // input is lisp representation:
  // ex: (1 ( (P X Y) (R (F X)) ) ( (Q X (A)) )  )
  Clause(string);
};

#endif