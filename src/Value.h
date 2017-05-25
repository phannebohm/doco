/**
 * @file Value.h
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef VALUE_H
#define VALUE_H

#include "Expr.h"

/**
 * @class Value
 * @date 17/02/2016
 * @brief Endknoten für Konstanten
 * hat keine Unterknoten
 */
class Value: public Expr
{
private:
  Complex val; ///< konstanter Wert des Knoten
public:
  Value(const Complex& val);
  /**
   * @brief Konstruktor für mathematische Konstanten per Name
   * @param[in] name  Name der Konstanten
   * @throws "unbekannte Konstante"
   */
  Value(const char* name);

  bool constant();
  Complex eval(const Complex&z);
  void print(std::ostream& out);
};

#endif // VALUE_H
