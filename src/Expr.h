/**
 * @file Expr.h
 * @brief Hier ist die Klasse beschrieben, aus der die Expression-Trees bestehen.
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef EXPR_H
#define EXPR_H

#include "Complex.h"

#include <iostream> /* ostream */


/**
 * @class Expr
 * @date 16/02/2016
 * @brief Virtuelle Klasse als Knoten in einem Expression-Tree
 * Die tatsächlichen Knoten erben von Expr.
 */
class Expr
{
public:
  /**
   * @fn ~Expr
   * @brief virtueller dtor
   */
  virtual ~Expr() {}

  /**
   * @fn constant
   * @brief Gibt an, ob der Teilbaum (ab diesem Knoten) "Variable"-Endknoten enthält
   * @return true (falls keine Variable existiert), false (sonst)
   * Wird von der Methode simplify benutzt.
   */
  virtual bool constant() = 0;

  /**
   * @fn simplify
   * @brief vereinfacht den Teilbaum (rekursiv), falls möglich
   */
  virtual void simplify() {}

  /**
   * @fn eval
   * @brief Auswertung an der angegebenen Stelle z
   * @param z  das Funktionsargument
   * @return den Funktionswert bei z
   */
  virtual Complex eval(const Complex& z) = 0;

  /**
   * @fn print
   * @brief schreibt eine Zeichenkette nach out, die den Expression-Tree repräsentiert
   * @param out  Ziel des Schreibvorganges
   */
  virtual void print(std::ostream& out) = 0;
};

#endif // EXPR_H
