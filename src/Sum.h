/**
 * @file Sum.h
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef SUM_H
#define SUM_H

#include "Sequence.h"

/**
 * @class Sum
 * @date 17/02/2016
 * @brief Summenknoten
 * hat eine Liste an Unterknoten
 */
class Sum: public Sequence
{
protected:
  void addtok(Element* elem);
public:
  Sum();
  Complex eval(const Complex& z);
  void print(std::ostream& out);
};

#endif // SUM_H
