/**
 * @file Parser.h
 * @brief Der Parser macht mithilfe des Lexers einen Expr-Tree aus ener Zeichenkennt
 * @author Philip Hannebohm
 * @date 16/02/2016
 */

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Expr.h"

/**
 * @class Parser
 * @date 16/02/2016
 * @brief Diese Klasse parst einen string und erzeugt den dazugehörigen "Expression-Tree".
 */
class Parser
{
private:
  std::string input; ///< zu parsender Text
  Lexer lexer;       ///< mein eigener Lexer
  Token* current;    ///< Token an der derzeitigen Position
  Expr* expr;        ///< Zeiger auf den (unfertig) gebauten Expression-Tree

public:
  /**
   * @fn Parser
   * @brief ctor initialisiert den Parser
   * @param[in] line  der zu parsende string
   */
  Parser(std::string line);

  /**
   * @fn parse
   * @brief parst den string und erzeugt den Expression-Tree
   * @throws falls der Text kein gültiger "Satz" im Sinne der unten beschriebenen Grammatik ist
   */
  void parse();

  /**
   * @fn getExpr
   * @brief gibt einen Zeiger auf den Expression-Tree zurück
   * @return this->expr
   */
  Expr* getExpr() const;

private:
  /**
   * @fn next
   * @brief fragt den Lexer nach dem nächsten Token und speichert es in current
   */
  void next();

  /**
   * @name Regeln
   * @brief Methoden, die die Regeln der formalen Grammaitk mathematischer Ausdrücke implementieren
   * @return Sie geben jeweils den bis dahin generierten Expression-Tree zurück
   *
   * Die Methoden rufen sich gegenseitig auf, entsprechend den Regeln. Die Regeln wurden von
   * mir selbst aufgestellt und erheben keinen Anspruch auf Korrektheit! Allerdings haben
   * einige Tests gezeigt, dass sie recht gut funktioniert und ich konnte keine ungültigen
   * "Sätze" formulieren, die von der Grammatik (falsch positiv) akzeptiert wurden.
   * Das Weglassen des Malpunktes ist nicht gestattet. Aber bei Funktionsaufrufen wird die
   * Schreibweise "sin z" (ohne Klammern) akzeptiert. Aber Vorsicht! Z.B.: "exp 1/z" wird als
   * "(exp(1)/z)" interprätiert und nicht als "exp(1/z)".
   */
  ///@{
  Expr* sum();      ///< sum      -> [ADD] product [ADD product]*
  Expr* product();  ///< product  -> factor [MUL factor]*
  Expr* factor();   ///< factor   -> argument [RAISE factor]
  Expr* argument(); ///< argument -> FUN argument | OPEN sum CLOSE | value
  Expr* value();    ///< value    -> NUM | CONST | VAR
  ///@}
};

#endif // PARSER_H
