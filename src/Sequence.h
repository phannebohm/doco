/**
 * @file Sequence.h
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Expr.h"

/**
 * @class Element
 * @date 17/02/2016
 * @brief Hilfsstruktur
 * speichert Informationen für Operanden
 * ist zugleich Listen-Container
 */
struct Element
{
public:
  Element* next; ///< nächstes Listenelement
  Expr* term;    ///< der Ausdruck des Operanden
  bool inv;      ///< wird das Inverse genommen?
};

/**
 * @class Sequence
 * @date 17/02/2016
 * @brief Virtuelle Klasse für Links-assoziative Verknüpfungen (Addition, Multiplikation)
 */
class Sequence: public Expr 
{
protected:
  Element* list; ///< Listenkopf einer Liste von Operanden
  Complex k;     ///< konstanter Operand

  /**
   * @brief verknüpft elem mit der Konstanten k
   * @param[in] elem  Der anzuhängende Operand
   * Die Funktion ist virtuell, weil die Implementierung von der Verknüpfung abhängt
   */
  virtual void addtok(Element* elem) =0;
public:
  /**
   * @brief Der konstante Operand muss (hier) initialisiert werden
   * @param[in] c  Anfangswert (Neutrales Element der Verknüpfung)
   */
  Sequence(const Complex& c);

  /**
   * @brief löscht die Liste
   */
  ~Sequence();

  bool constant();
  void simplify();
  void add(Expr*, bool);
};

#endif // SEQUENCE_H

