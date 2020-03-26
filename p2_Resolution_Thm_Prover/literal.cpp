#include "literal.h"

Literal::Literal(string info){
  value = info.substr(1, info.size() - 2);

  root = Unifiable::get_unifiable(value);
}

ostream& operator<<(ostream& os, const Literal& literal)
{
  os << *(literal.root);
  return os;
}
