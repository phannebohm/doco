#include "Lexer.h"
#include <cstring> /* strcmp */

// Token-ctor ------------------------------------------------------------------
Token::Token(Type type, string str)
  : type(type), str(str)
{}

// Lexer-ctor ------------------------------------------------------------------
Lexer::Lexer(string input)
  : input(input), pos(0)
{}


// Liste an bekannten Konstanten -----------------------------------------------
static inline bool isconst(const char* str)
{
  return strcmp(str, "i") == 0
         || strcmp(str, "e") == 0
         || strcmp(str, "pi") == 0;
}

// Liste an bekannten Funktionen -----------------------------------------------
static inline bool isfun(const char* str)
{
  return strcmp(str, "Re") == 0
         || strcmp(str, "Im") == 0
         || strcmp(str, "abs") == 0
         || strcmp(str, "arg") == 0
         || strcmp(str, "conj") == 0
         || strcmp(str, "cos") == 0
         || strcmp(str, "sin") == 0
         || strcmp(str, "tan") == 0
         || strcmp(str, "acos") == 0
         || strcmp(str, "asin") == 0
         || strcmp(str, "atan") == 0
         || strcmp(str, "cosh") == 0
         || strcmp(str, "sinh") == 0
         || strcmp(str, "tanh") == 0
         || strcmp(str, "acosh") == 0
         || strcmp(str, "asinh") == 0
         || strcmp(str, "atanh") == 0
         || strcmp(str, "exp") == 0
         || strcmp(str, "ln") == 0
         || strcmp(str, "pow") == 0
         || strcmp(str, "sqrt") == 0
         || strcmp(str, "gamma") == 0
         || strcmp(str, "zeta") == 0
         || strcmp(str, "pe") == 0;
}


// nextToken -------------------------------------------------------------------
Token* Lexer::nextToken()
{
  // Diese Schleife wird ziemlich oft von nextToken benutzt, daher bietet sich
  // ein Makro an. Es wird das Symbol an der derzeitigen Position zu str hinzu-
  // gefügt und dann wird in input eine Stelle weiter nach rechts gegangen, so-
  // lange die Bedingung cond gilt und wir noch nicht am Ende sind.
#define STEP(cond) do { str += *c; ++i; ++c; } while(c != input.end() && (cond));

  Token::Type type;  // für den
  string str;      // Rückgabewert

  // Zeiger auf die derzeitige Position im Input-string
  string::iterator c = input.begin();

  // Derzeitige Position. Gibt an, wie weit wir im string vorangeschritten sind
  int i = 0;

  // alle Leerzeichen werden übersprungen
  while(c != input.end() && isspace(*c)) {
    ++i;
    ++c;
  }

  if(c != input.end()) { // sind wir noch nicht am Ende?
    if(*c == '+' || *c == '-') { // Addition?
      type = Token::ADD;
      str = *c;
      ++i;
    } else if(*c == '*' || *c == '/') { // Multiplikation?
      type = Token::MUL;
      str = *c;
      ++i;
    } else if(*c == '^') { // Potenzierung?
      type = Token::RAISE;
      str = *c;
      ++i;
    } else if(*c == '(') { // öffnende Klammer?
      type = Token::OPEN;
      str = *c;
      ++i;
    } else if(*c == ')') { // schließende Klammer?
      type = Token::CLOSE;
      str = *c;
      ++i;
    } else if(isalpha(*c)) { // Bezeichner (Variable, Konstante, Funktion)?
      STEP(islower(*c));

      if(str == "z") {
        type = Token::VAR;
      } else if(isconst(str.c_str())) {
        type = Token::CONST;
      } else if(isfun(str.c_str())) {
        type = Token::FUN;
      } else {
        throw "Lexer-Error: unbekannter Bezeichner";
      }
    } else if(isdigit(*c)) { // Zahl?
      type = Token::NUM;
      STEP(isdigit(*c));
      if(c != input.end() && *c == '.' && (c + 1) != input.end() && isdigit(*(c + 1))) {
        STEP(isdigit(*c));
      }
      if(c != input.end() && (*c == 'e' || *c == 'E') && (c + 1) != input.end()) {
        if(isdigit(*(c + 1))) {
          STEP(isdigit(*c));
        } else if((*(c + 1) == '+' || *(c + 1) == '-') && (c + 2) != input.end() && isdigit(*(c + 2))) {
          str += *c;               // da die ersten beiden! Symbole keine Ziffern sind,
          ++i;                     // muss das 'e' manuell hinzugefügt werden
          ++c;
          STEP(isdigit(*c));
        }
      }
    } else { // Unbekannt!
      throw "Lexer-Error: unbekanntes Symbol";
    }
  } else { // wir sind am Ende des Input-strings
    type = Token::END;
    str = "";
  }

  pos += i; // position wird nach rechts geschoben
  input = input.substr(i);    // das gerade gelesene Token wird aus dem Input-string gestrichen
  return new Token(type, str);  // und zurückgegeben

  // Jetzt wird STEP nicht mehr gebraucht
#undef STEP

}
