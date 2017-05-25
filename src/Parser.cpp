#include "Parser.h"
#include "Sequence.h"
#include "Sum.h"
#include "Product.h"
#include "Power.h"
#include "Function.h"
#include "Value.h"
#include "Variable.h"

#include <cstdlib> /* strtod */

// -----------------------------------------------------------------------------
Parser::Parser(std::string line)
  : input(line), lexer(input), current(lexer.nextToken()), expr(NULL)
{}

// -----------------------------------------------------------------------------
void Parser::next()
{
  delete current;
  current = lexer.nextToken();
}

// -----------------------------------------------------------------------------
void Parser::parse()
{
  delete expr;
  expr = sum();
  if(current->type != Token::END) {
    //delete expr;
    throw "Parser-Error: Das Ende wurde erwartet aber nicht erreicht.";
  }
}

// -----------------------------------------------------------------------------
Expr* Parser::getExpr() const
{
  return expr;
}


// -----------------------------------------------------------------------------
// sum -> [ADD] product [ADD product]*
Expr* Parser::sum()
{
  Sequence* result = new Sum;
  bool neg = false;
  if(current->type == Token::ADD) {
    neg = current->str == "-";
    next();
  }
  result->add(product(), neg);
  while(current->type == Token::ADD) {
    neg = current->str == "-";
    next();
    result->add(product(), neg);
  }
  return result;
}

// -----------------------------------------------------------------------------
// product -> factor [MUL factor]*
Expr* Parser::product()
{
  Sequence* result = new Product;
  bool inv = false;
  result->add(factor(), inv);
  while(current->type == Token::MUL) {
    inv = current->str == "/";
    next();
    result->add(factor(), inv);
  }
  return result;
}

// -----------------------------------------------------------------------------
// factor -> argument [RAISE factor]
Expr* Parser::factor()
{
  Expr* result = argument();
  if(current->type == Token::RAISE) {
    next();
    result = new Power(result, factor());
  }
  return result;
}

// -----------------------------------------------------------------------------
// argument -> FUN argument | OPEN sum CLOSE | value
Expr* Parser::argument()
{
  Expr* result = NULL;
  if(current->type == Token::FUN) {
    std::string name = current->str;
    next();
    result = new Function(name.c_str(), argument());
  } else if(current->type == Token::OPEN) {
    next();
    result = sum();
    if(current->type == Token::CLOSE) {
      next();
    } else {
      //delete expr;
      throw "Parser-Error: Es fehlt eine schliessende Klammer.";
    }
  } else {
    result = value();
  }
  return result;
}

// -----------------------------------------------------------------------------
// value -> NUM | CONST | VAR
Expr* Parser::value()
{
  Expr* result = NULL;
  if(current->type == Token::NUM) {
    result = new Value(strtod(current->str.c_str(), NULL));
    next();
  } else if(current->type == Token::CONST) {
    result = new Value(current->str.c_str());
    next();
  } else if(current->type == Token::VAR) {
    result = new Variable;
    next();
  } else {
    //delete expr;
    throw "Parser-Error: unbekannter Name entdeckt.";
  }
  return result;
}
