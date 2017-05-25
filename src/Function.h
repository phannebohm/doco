/**
 * @file Function.h
 * @brief Hier ist die Klasse Function beschrieben.
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#include "Expr.h"

/**
 * @class Function
 * @date 17/02/2016
 * @brief Funktionsknoten
 * hat einen Unterknoten
 */
class Function: public Expr
{
private:
  int id;      ///< Code für den Funktionsnamen
  Expr* argum; ///< Unterknoten für das Funktionsargument
public:
  /**
   * @brief Konstruktor
   * @param[in] name  Funktionsname
   * @param[in] argum  Argument-Knoten
   * @throws falls name nicht in der Liste der bekannten Funktionen ist
   */
  Function(const char* name, Expr* argum);

  ~Function();

  bool constant();
  void simplify();
  Complex eval(const Complex& z);
  void print(std::ostream& out);
};

#endif // FUNCTION_H

