/**
 * @file Product.h
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include "Sequence.h"

/**
 * @class Product
 * @date 17/02/2016
 * @brief Produktknoten
 * hat eine Liste an Unterknoten
 */
class Product: public Sequence
{
protected:
  void addtok(Element* elem);
public:
  Product();
  Complex eval(const Complex& z);
  void print(std::ostream& out);
};

#endif // PRODUCT_H
