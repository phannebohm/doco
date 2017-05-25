/**
 * @file Lexer.h
 * @brief Mithilfe der hier beschriebenen Klassen wird der Input-String in eine Liste von Tokens verwandelt
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef LEXER_H
#define LEXER_H

#include <string> /* string */
using std::string;

/**
 * @class Token
 * @date 13/02/2016
 * @brief Diese Klasse beschreibt ein Symbol
 * @details Sie ist so klein, dass sie keine eigene Datei bekam
 */
class Token
{
public:
  enum Type { ADD, MUL, RAISE, OPEN, CLOSE, CONST, VAR, FUN, NUM, END};
  const Type type;
  const string str;

  /**
   * @brief Konstruktor
   * @param[in] type  Tokentyp
   * @param[in] str  Zeichenkette
   */
  Token(Type type, string str);
};

/**
 * @class Lexer
 * @date 13/02/2016
 * @brief Diese Klasse bekommt einen std::string und gibt die darin
 * enthaltenene Symbole nacheinander aus
 */
class Lexer
{
private:
  string input; ///< der Input-string
  int pos;      ///< derzeitige Position im Text
public:
  /**
   * @fn Lexer
   * @brief ctor setzt den initialen Input-string
   * @param[in] input  zu verarbeitender Input-string
   */
  Lexer(string input);

  /**
   * @fn nextToken
   * @brief geht im Input-string ein Token weiter
   * @return Das nächste Token
   * @throws falls der Benutzer etwas falsches schreibt
   *
   * @detalis Diese Methode ist das Arbeitspferd der Klasse Lexer.
   * Sie identifiziert den Typ und die Zeichenkette des nächsten Tokens und
   * gibt es als neues Token Objekt aus. Dabei folgt sie diesen Regeln:
   *
   *    ADD   <- '+' | '-'
   *    MUL   <- '*' | '/'
   *    RAISE <- '^'
   *    OPEN  <- '('
   *    CLOSE <- ')'
   *    VAR   <- 'z'
   *    CONST <- 'i' | 'e' | 'pi'
   *    FUN   <- 'Re' | 'Im' | 'abs' | 'arg' | 'conj' | 'cos' | 'sin' | 'tan' | 'acos'
   *           | 'asin' | 'atan' | 'cosh' | 'sinh' | 'tanh' | 'acosh' | 'asinh' | 'atanh'
   *           | 'exp' | 'ln' | 'pow' | 'sqrt' | 'gamma' | 'zeta' | 'pe'
   *    NUM   <- ('0'-'9')+ [ '.' ('0'-'9')+ ] [ 'e' [ '+' | '-' ] ('0'-'9')+ ]
   *    END   <- ''
   */
  Token* nextToken();
};

#endif // LEXER_H

