#include "Power.h"
#include "Value.h"

// -----------------------------------------------------------------------------
Power::Power(Expr* base, Expr* exponent)
  : base(base), exponent(exponent)
{}

// -----------------------------------------------------------------------------
Power::~Power()
{
  delete base;
  delete exponent;
}

// -----------------------------------------------------------------------------
bool Power::constant()
{
  return base->constant() && exponent->constant();
}

// -----------------------------------------------------------------------------
void Power::simplify()
{
  if(base->constant()) {
    Complex z = base->eval(0);
    delete base;
    base = new Value(z);
  } else {
    base->simplify();
  }
  if(exponent->constant()) {
    Complex z = exponent->eval(0);
    delete exponent;
    exponent = new Value(z);
  } else {
    exponent->simplify();
  }
}

// -----------------------------------------------------------------------------
Complex Power::eval(const Complex& z)
{
  const double branch = 0; // FIXME das muss von außen gegeben sein!?!
  return pow(base->eval(z), exponent->eval(z), branch);
}

// -----------------------------------------------------------------------------
void Power::print(std::ostream& out)
{
  base->print(out);
  out << '^';
  exponent->print(out);
}
