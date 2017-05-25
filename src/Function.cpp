#include "Function.h"
#include "Value.h"

#include <cstring> /* strcmp */

// -----------------------------------------------------------------------------
static const char* fun[23] = {
  "Re",   "Im",   "abs",  "arg",   "conj",
  "cos",  "sin",  "tan",  "acos",  "asin",  "atan",
  "cosh", "sinh", "tanh", "acosh", "asinh", "atanh",
  "exp",  "ln",   "sqrt", "gamma", "zeta",  "pe"
};

// -----------------------------------------------------------------------------
Function::Function(const char* name, Expr* argum): argum(argum)
{
  for(int i = 0; i < 23; ++i) {
    if(strcmp(name, fun[i]) == 0) {
      id = i;
      return;
    }
  }
  // doesn't happen...
  throw "unbekannter Funktionsname";
}

// -----------------------------------------------------------------------------
Function::~Function()
{
  delete argum;
}

// -----------------------------------------------------------------------------
bool Function::constant()
{
  return argum->constant();  // Der Funktionswert ist konstant, wenn das Funktionsargument konstannt ist...
}

// -----------------------------------------------------------------------------
void Function::simplify()
{
  //if(argum->constant()) {
  //  // FIXME dieser Fall ist Schwachsinn, weil der Funktionsknoten selbst ersetzt werden könnte...
  //  Complex z = argum->eval(0);
  //  delete argum;
  //  argum = new Value(z);
  //} else {
    argum->simplify();
  //}
}

// -----------------------------------------------------------------------------
Complex Function::eval(const Complex& z)
{
  const double branch = 0; // FIXME branch sollte ein einstellbarer Parameter sein...

  switch(id) {
  case  0:// Re
    return Re(argum->eval(z));
  case  1:// Im
    return Im(argum->eval(z));
  case  2:// abs
    return abs(argum->eval(z));
  case  3:// arg
    return arg(argum->eval(z), branch);
  case  4:// conj
    return conj(argum->eval(z));
  case  5:// cos
    return cos(argum->eval(z));
  case  6:// sin
    return sin(argum->eval(z));
  case  7:// tan
    return tan(argum->eval(z));
  case  8:// acos
    return acos(argum->eval(z), branch);
  case  9:// asin
    return asin(argum->eval(z), branch);
  case 10:// atan
    return atan(argum->eval(z), branch);
  case 11:// cosh
    return cosh(argum->eval(z));
  case 12:// sinh
    return sinh(argum->eval(z));
  case 13:// tanh
    return tanh(argum->eval(z));
  case 14:// acosh
    return acosh(argum->eval(z), branch);
  case 15:// asinh
    return asinh(argum->eval(z), branch);
  case 16:// atanh
    return atanh(argum->eval(z), branch);
  case 17:// exp
    return exp(argum->eval(z));
  case 18:// ln
    return ln(argum->eval(z), branch);
  case 19:// sqrt
    return sqrt(argum->eval(z), branch);
  case 20:// gamma
    return gamma(argum->eval(z));
  case 21:// zeta
    return zeta(argum->eval(z));
  case 22:// pe
    return pe(argum->eval(z));
  default:// doesn't happen...
    throw "Funktionsaufruf mit unbekannter id";
  }
  // doesn't happen...
  throw "Fehler beim Auswerten der Funktion";
}

// -----------------------------------------------------------------------------
void Function::print(std::ostream& out)
{
  out << fun[id] << "(";
  argum->print(out);
  out << ")";
}
