/**
 * @file Power.h
 * @brief Hier ist die Klasse Power beschrieben.
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef POWER_H
#define POWER_H

#include "Expr.h"

/**
 * @class Power
 * @date 17/02/2016
 * @brief Potenzierungsknoten
 * hat zwei Unterknoten
 */
class Power: public Expr
{
private:
  Expr* base;     ///< Unterknoten für die Basis
  Expr* exponent; ///< Unterknoten für den Exponenten
public:
  /**
   * @brief Konstruktor
   * @param[in] base  Basis-Knoten
   * @param[in] exponent  Exponent-Knoten
   */
  Power(Expr* base, Expr* exponent);

  ~Power();

  bool constant();
  void simplify();
  Complex eval(const Complex& z);
  void print(std::ostream& out);
};

#endif // POWER_H

