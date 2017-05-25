#include "Product.h"

// -----------------------------------------------------------------------------
Product::Product()
  : Sequence(1.0)
{}

// -----------------------------------------------------------------------------
void Product::addtok(Element* elem)
{
  if(elem->inv) {
    k /= elem->term->eval(0);
  } else {
    k *= elem->term->eval(0);
  }
}

// -----------------------------------------------------------------------------
Complex Product::eval(const Complex& z)
{
  Complex result = k;
  Element* elem = list;
  while(elem != NULL) {
    // Abkürzung: Das Produkt ist Null, wenn ein Faktor Null ist...
    //if(result == 0.0) {
    //  return result;
    //}
    // AUSSER es wird durch Null geteilt... also doch nicht.
    // TODO: da kann man vielleicht irgendwas machen...
    if(elem->inv) {
      result /= elem->term->eval(z);
    } else {
      result *= elem->term->eval(z);
    }
    elem = elem->next;
  }
  return result;
}

// -----------------------------------------------------------------------------
void Product::print(std::ostream& out)
{
  if(list == NULL) {
    out << k;
    return;
  }

  Element* elem = list;

  if(k != 1.0 && k != -1.0) {
    out << k;
  } else {
    // Das erste Element muss gesondert behandelt werden
    if(k == -1.0) {
      out << "(-"; // Klammer auf, und am Ende...
    }
    if(elem->inv) {
      out << "1/";
    }

    elem->term->print(out);
    elem = elem->next;
  }

  // Der Rest
  while(elem != NULL) {
    out << ((elem->inv) ? ('/') : ('*'));
    elem->term->print(out);
    elem = elem->next;
  }

  if(k == -1.0) {
    out << ")"; // ... Klammer zu
  }
}
