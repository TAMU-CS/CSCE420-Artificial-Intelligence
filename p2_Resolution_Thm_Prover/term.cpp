#include "term.h"

Unifiable::Unifiable(string _name)
{
  name = _name;
}

void Unifiable::serialize(ostream& os) const {
  os << name;
}

Constant::Constant(string _name) : Unifiable(_name)
{
}

Variable::Variable(string _name) : Unifiable(_name)
{
}

Function::Function(string _name) : Unifiable(_name)
{
}

void Function::serialize(ostream& os) const {
  Unifiable::serialize(os);
}
