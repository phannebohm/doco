/**
 * @file Variable.h
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef VARIABLE_H
#define VARIABLE_H

#include "Expr.h"

/**
 * @class Variable
 * @date 17/02/2016
 * @brief Endknoten für Variable
 * hat keine Unterknoten
 */
class Variable: public Expr
{
public:
  bool constant();
  Complex eval(const Complex& z);
  void print(std::ostream& out);
};

#endif // VARIABLE_H
