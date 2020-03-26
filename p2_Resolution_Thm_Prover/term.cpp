#include "term.h"

Unifiable::Unifiable(string _name)
{
  name = _name;
}

Unifiable* get_unifiable(string info){
/**
Unifiable* ProcessTerm(x = (F x y)){
  varList = [F x y];
  if(varList.size() > 1){ its a function
    return new Function(x)
  }else{
    if(x[0] === '(')){
      return new Constant(x.substr(1, x.size() - 2));
    }else{
      return new Variable(x);
    }
  }
} 
*/  
}

void Unifiable::serialize(ostream &os) const
{
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

void Function::serialize(ostream &os) const
{
  Unifiable::serialize(os);
}
