#ifndef LITERAL_H
#define LITERAL_H

#include <iostream>
#include <string>

using namespace std;

class Literal{
  public:
  string value;

  // constructor
  // input: literal string (lisp format)
  // ex: F X (H Y)
  Literal(string);

  // overloading to print out
  friend ostream& operator<<(ostream& os, const Literal& dt);
};

#endif
