/**
 * @file Complex.h
 * @brief Diese Datei beinhaltet eine Klasse Complex für das Rechnen mit
 * komplexen Zahlen.
 * @author Philip Hannebohm
 * @date 06/12/2015
 */

#ifndef COMPLEX_H
#define COMPLEX_H

#include "Bitmap.h"

#include <iostream> /* istream, ostream */

/**
 * @class Complex
 * @date 06/12/2015
 * @brief Klasse für Arithmetik mit komplexen Zahlen
 */
class Complex
{
private:
  double real;  ///< Realteil
  double imag;  ///< Imaginärteil
public:
  /**
   * @fn Complex
   * @brief einfacher ctor setzt Real- und Imaginärteil (auf 0)
   * @param a  Realteil
   * @param b  Imaginärteil
   */
  Complex(const double a = 0, const double b = 0);
  /**
   * @brief Copy-ctor
   */
  Complex(const Complex&);

  /**
   * @name Zuweisungsoperatoren
   * @brief Die Operatoren tun das, was man erwartet.
   */
  ///@{
  Complex& operator= (const Complex& z);
  Complex& operator+=(const Complex& z);
  Complex& operator-=(const Complex& z);
  Complex& operator*=(const Complex& z);
  Complex& operator/=(const Complex& z);

  Complex& operator= (const double x);
  Complex& operator+=(const double x);
  Complex& operator-=(const double x);
  Complex& operator*=(const double x);
  Complex& operator/=(const double x);
  ///@}

  /**
   * @name Arithmetische Operatoren
   * @brief Die Operatoren tun, was man erwartet.
   */
  ///@{
  Complex operator-() const; // Vorzeichen

  Complex operator+(const Complex& z) const;
  Complex operator-(const Complex& z) const;
  Complex operator*(const Complex& z) const;
  Complex operator/(const Complex& z) const;

  Complex operator+(const double x) const;
  Complex operator-(const double x) const;
  Complex operator*(const double x) const;
  Complex operator/(const double x) const;

  friend Complex operator+(const double x, const Complex& z);
  friend Complex operator-(const double x, const Complex& z);
  friend Complex operator*(const double x, const Complex& z);
  friend Complex operator/(const double x, const Complex& z);
  ///@}

  /**
   * @name Vergleichsoperatoren
   * @brief Die Operatoren tun das, was man erwartet.
   * @details Komplexe Zahlen sind nicht geordnet, also kein < <= > >=.
   */
  ///@{
  bool operator==(const Complex& z) const;
  bool operator!=(const Complex& z) const;
  bool operator==(const double x) const;
  bool operator!=(const double x) const;
  friend bool operator==(const double x, const Complex& z);
  friend bool operator!=(const double x, const Complex& z);
  ///@}

  /**
   * @name Mathematische Funktionen
   * @brief Die meisten Funktionen sind selbsterklärend
   */
  ///@{
  friend double Re(const Complex& z);
  friend double Im(const Complex& z);
  friend double abs(const Complex& z);
  /**
   * @fn arg
   * @brief Das Argument (die Phase/der Winkel) einer komplexen Zahl ist
   * mehrdeutug. Daher gibt es mehrere 'Zweige'.
   * @param z  eine komplexe Zahl
   * @param branch  der Zweig der zurückgegeben werden soll
   * @return das Argument von z im Intervall (-pi + 2pi*branch; pi + 2pi*branch]
   */
  friend double arg(const Complex& z, const int branch);
  friend Complex conj(const Complex& z);

  friend Complex cos(const Complex& z);
  friend Complex sin(const Complex& z);
  friend Complex tan(const Complex& z);

  friend Complex acos(const Complex& z, const int branch);
  friend Complex asin(const Complex& z, const int branch);
  friend Complex atan(const Complex& z, const int branch);

  friend Complex cosh(const Complex& z);
  friend Complex sinh(const Complex& z);
  friend Complex tanh(const Complex& z);

  friend Complex acosh(const Complex& z, const int branch);
  friend Complex asinh(const Complex& z, const int branch);
  friend Complex atanh(const Complex& z, const int branch);

  friend Complex exp(const Complex& z);
  friend Complex ln(const Complex& z, const int branch);
  friend Complex pow(const Complex& z, const Complex& w, const int branch);
  friend Complex sqrt(const Complex& z, const int branch);

  friend Complex gamma(const Complex& z);
  friend Complex zeta(const Complex& z);
  /**
   * @fn pe = Weierstrass' elliptische Funktion
   * @param z  das normale Funktionsargument
   * @return den Wert von pe an der Stelle z
   */
  friend Complex pe(const Complex& z);
  ///@}

  /**
   * @name I/O-Operatoren
   */
  ///@{
  friend std::ostream& operator<<(std::ostream&, const Complex&);
  /**
   * @brief muss in der Form '(' a  ','  b  ')' eingegeben werden
   */
  friend std::istream& operator>>(std::istream&, Complex&);
  ///@}
};

#endif // COMPLEX_H
