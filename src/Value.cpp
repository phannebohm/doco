#include "Value.h"

#include <cstring> /* strcmp */

// -----------------------------------------------------------------------------
Value::Value(const Complex& val)
  : val(val)
{}

// -----------------------------------------------------------------------------
Value::Value(const char* name)
{
  if(strcmp(name, "i") == 0) {
    val = Complex(0, 1);
  } else if(strcmp(name, "e") == 0) {
    val = 2.71828182845904523536;
  } else if(strcmp(name, "pi") == 0) {
    val = 3.14159265358979323846;
  } else {
    // BAD ERROR!
    throw "unbekannte Konstante";
  }
}

// -----------------------------------------------------------------------------
bool Value::constant()
{
  return true; // Konstante ist konstant
}

// -----------------------------------------------------------------------------
Complex Value::eval(const Complex&)
{
  return val;
}

// -----------------------------------------------------------------------------
void Value::print(std::ostream& out)
{
  out << val;
}
