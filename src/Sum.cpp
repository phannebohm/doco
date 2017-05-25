#include "Sum.h"

// -----------------------------------------------------------------------------
Sum::Sum()
  : Sequence(0.0)
{}

// -----------------------------------------------------------------------------
void Sum::addtok(Element* elem)
{
  if(elem->inv) {
    k -= elem->term->eval(0);
  } else {
    k += elem->term->eval(0);
  }
}

// -----------------------------------------------------------------------------
Complex Sum::eval(const Complex& z)
{
  Complex result = k;
  Element* elem = list;
  while(elem != NULL) {
    if(elem->inv) {
      result -= elem->term->eval(z);
    } else {
      result += elem->term->eval(z);
    }
    elem = elem->next;
  }
  return result;
}

// -----------------------------------------------------------------------------
void Sum::print(std::ostream& out)
{
  if(list == NULL) {
    out << k;
    return;
  }

  Element* elem = list;

  out << '(';
  if(k != 0.0) {
    out << k;
  } else {
    // Das erste Element muss gesondert behandelt werden
    if(elem->inv) {
      out << '-';
    }
    elem->term->print(out);
    elem = elem->next;
  }
  while(elem != NULL) {
    out << ((elem->inv) ? (" - ") : (" + "));
    elem->term->print(out);
    elem = elem->next;
  }
  out << ')';
}
