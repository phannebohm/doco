#include "Variable.h"

// -----------------------------------------------------------------------------
bool Variable::constant()
{
  return false; // Variable ist nicht konstant
}

// -----------------------------------------------------------------------------
Complex Variable::eval(const Complex& z)
{
  return z;
}

// -----------------------------------------------------------------------------
void Variable::print(std::ostream& out)
{
  out << 'z';
}
