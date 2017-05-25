#include "Sequence.h"
#include "Value.h"

// -----------------------------------------------------------------------------
Sequence::Sequence(const Complex& c)
  : list(NULL), k(c)
{}

// -----------------------------------------------------------------------------
Sequence::~Sequence()
{
  // Lösche Listenkopf bis alles weg ist
  Element* elem = NULL;
  while(list != NULL) {
    elem = list->next;
    delete list->term;
    delete list;
    list = elem;
  }
}

// -----------------------------------------------------------------------------
bool Sequence::constant()
{
  Element* elem = list;
  while(elem != NULL) {
    if(!elem->term->constant()) { // Sobald ein Element nicht konstant ist,
      return false;               // ist die ganze Verknüpfung nicht konstant.
    }
    elem = elem->next;
  }
  return true; // Sonst konstant
}

// -----------------------------------------------------------------------------
void Sequence::simplify()
{
  Element* elem = list; // gerade untersuchtes Element
  Element* prev = NULL; // Vorgänger

  while(elem != NULL) {
    if(elem->term->constant()) {
      addtok(elem);
      delete elem->term;
      if(prev == NULL) {   // kein Vorgänger -> wir sind am Anfang
        list = elem->next; // also wird der Nachfolger zum neuen Anfang
        delete elem;
        elem = list;       // weiter am Anfang
      } else {
        // Schließe die Lücke zwischen Vorgänger und Nachfolger
        prev->next = elem->next;
        delete elem;
        elem = prev->next;
      }
    } else { // elem ist nich konstant
      elem->term->simplify(); // versuche zu vereinfachen

      // gehe einen weiter
      prev = elem;
      elem = elem->next;
    }
  }
}

// -----------------------------------------------------------------------------
void Sequence::add(Expr* term, bool inv)
{
  if(list == NULL) { // Liste leer
    // neues Element am Anfang
    list = new Element;
    list->next = NULL;
    list->term = term;
    list->inv = inv;
    return; // fertig
  }

  Element* elem = list;
  // Gehe zum Ende der Liste!
  // Dadurch wird bei der Ausgabe nicht der Input verkehrt ausgegeben (Ästetik!)
  while(elem->next != NULL) {
    elem = elem->next;
  }
  // Füge das neue Element hinzu!
  elem->next = new Element;
  elem = elem->next;
  elem->next = NULL;
  elem->term = term;
  elem->inv = inv;
}
