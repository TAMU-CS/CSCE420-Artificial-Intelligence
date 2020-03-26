#ifndef LITERAL_H
#define LITERAL_H

#include "term.h"

#include <iostream>
#include <string>

using namespace std;

class Literal
{
public:
  string value;

  Unifiable* root;

  // constructor
  // input: literal string (lisp format)
  // ex: F X (H Y)
  Literal(string);

  friend ostream &operator<<(ostream &os, const Literal &dt);
};

#endif
