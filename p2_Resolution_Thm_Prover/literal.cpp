#include "literal.h"

Literal::Literal(string info){
  value = info;
}

ostream& operator<<(ostream& os, const Literal& literal)
{
  os << literal.value;
  return os;
}
