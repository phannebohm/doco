#include "Controller.h"
#include "Parser.h"
#include "Variable.h"

#include <cmath> /* isnan, isinf */
#include <fstream> /* ifstream */
#include <iostream> /* cout, endl */
#include <sstream> /* istringstream */
#include <new> /* bad_alloc */

using namespace std;


// Konstruktor mit Standardwerten ----------------------------------------------
Controller::Controller()
  : arg_color(1),
    iso_abs_style(0), iso_abs_scale(2), iso_abs_int(1),
    iso_arg_count(8), iso_arg_thick(1), iso_arg_int(1),
    use_grid(false), grid_scale(1), grid_int(0.5),
    start(-1, -1), end(1, 1),
    function(new Variable()),
    iterations(1),
    width(128), height(128),
    fname("bild")
{}


// -----------------------------------------------------------------------------
Controller::~Controller()
{
  delete function;
}


// -----------------------------------------------------------------------------
RGBA Controller::CompToRGB(const Complex& z) const
{
  static const double PI = 3.14159265358979323846;

  double r = abs(z);
  if(isnan(r)) {
    return RGBA(0.5, 0.5, 0.5);
    //r = DOUBLE_INF; // infinity
  }

  double phi = arg(z, 0);
  if(isnan(phi)) {
    phi = 0;
  }

  double col[3];

  if(arg_color) { // Standard
    // Hue:
    double h = phi * 3 / PI;
    if(h < 0) {
      h += 6;
    }

    //    Rot: col[0]      Grün: col[1]     Blau: col[2]
    //    ^__        __    ^  ____          ^      ____  .
    //   1|  \      /     1| /    \        1|     /    \ .
    //   0|   \____/      0|/      \____   0|____/      \.
    //   -|------------>  -|------------>  -|------------>
    //   h 0 1 2 3 4 5    h 0 1 2 3 4 5    h 0 1 2 3 4 5

    if(h < 1) {
      col[0] = 1.0;
      col[1] = h;
      col[2] = 0.0;
    } else if(h < 2) {
      col[0] = 2 - h;
      col[1] = 1.0;
      col[2] = 0.0;
    } else if(h < 3) {
      col[0] = 0.0;
      col[1] = 1.0;
      col[2] = h - 2;
    } else if(h < 4) {
      col[0] = 0.0;
      col[1] = 4 - h;
      col[2] = 1.0;
    } else if(h < 5) {
      col[0] = h - 4;
      col[1] = 0.0;
      col[2] = 1.0;
    } else {
      col[0] = 1.0;
      col[1] = 0.0;
      col[2] = 6 - h;
    }
  } else { // grau
    col[0] = col[1] = col[2] = 0.5;
  }

  // Lightness:
  double lightness = 0.5;

  if(iso_arg_count > 0) {
    // Winkel skalieren und verschieben
    phi *= iso_arg_count * 0.5 / PI;
    phi -= floor(phi);
    if(phi > 0.5) phi = 1 - phi;
    phi /= iso_arg_thick;

    //    weiß: w
    //    ^
    //   1|\         /\         /\                       /
    //    | \       /  \       /  \       /     \       /
    //   0|  \_____/    \_____/    \_____/  ...  \_____/
    //   -|--------------------------------     ---------->
    // arg 0        2pi/n     2*2pi/n                  n*2pi/n

    double w = 0;
    if(phi < 1) {
      w = 1 - phi;
      w = 0.5 * iso_arg_int * pow(w, 6);
    }
    lightness += w;
  }

  if(iso_abs_style == 1) {
    if(isinf(r)) {
      lightness = 1;
    } else {
      r = 0.5*(r - 1 / r) * PI * 0.05 * iso_abs_scale;
      lightness += atan(r) / PI * iso_abs_int;
    }
  } else if(iso_abs_style == 2) {
    // Betrag skalieren
    r = log(r) / log(iso_abs_scale);
    r -= floor(r);

    //    schwarz: b
    //    ^
    //   1|\        /
    //    | \     /
    //    |  \  /
    //   0|   v
    //   -|---|------>
    //   r 0 eps    1

    double b;
    double eps = 0.1;
    if(r < eps) {
      b = 1 - r / eps;
    } else {
      b = (r - eps) / (1 - eps);
    }

    b = 0.5 * iso_abs_int * pow(b, 4);
    lightness -= b;
  }

  if(use_grid) { // Schachbrett
    if(int(floor(Re(z) * grid_scale) + floor(Im(z) * grid_scale)) % 2 == 0) {
      col[0] = grid_int + (1 - grid_int) * col[0];
      col[1] = grid_int + (1 - grid_int) * col[1];
      col[2] = grid_int + (1 - grid_int) * col[2];
    } else {
      col[0] = (1 - grid_int) * col[0];
      col[1] = (1 - grid_int) * col[1];
      col[2] = (1 - grid_int) * col[2];
    }
  }

  lightness = (((lightness) > 0) ? (((lightness) < 1) ? (lightness) : 1) : 0);

  // Chroma:
  double chroma = 1 - fabs(2 * lightness - 1);
  double m = lightness - 0.5 * chroma;

  return RGBA(chroma * col[0] + m, chroma * col[1] + m, chroma * col[2] + m);
}


// -----------------------------------------------------------------------------
void Controller::read(const char* input_name)
{
  int n; // muss signed sein wegen des Vergleichs mit string::npos
  string word, line;
  ifstream input;

  cout << "\n" << input_name << " Lesen:\n";
  input.open(input_name);
  cout << " +------------------------------\n"; // Dekoration
  while(!input.eof()) {
    getline(input, word, ':');

    n = word.find_first_not_of(" \t\f\v\n\r");
    if(n != string::npos) {
      word = word.substr(n);
      getline(input, line);

      // Kommentarzeile
      if(word[0] == '%') continue;

      n = line.find_first_not_of(" \t\f\v\n\r");
      if(n != string::npos) {
        line = line.substr(n);

        // hinteren whitespace entfernen
        n = line.find_last_not_of(" \t\f\v\n\r");
        line = line.substr(0, n+1);

        set(word, line);
      }
    }
  }
  cout << " +------------------------------\n"; // Dekoration
  input.close();

  try{
    // Zeichnen
    Bitmap map(width, height);
    draw(map);

    // Speichern
    cout << "Speichern: ";
    map.save((fname + ".bmp").c_str());
    cout << '\a' << "fertig.\n";
  }
  catch(bad_alloc al){
    cout << "Das Bild ist zu gross und konnte nicht erzeugt werden.\nVersuchen Sie es doch bitte etwas kleiner."<<endl;
    throw al;
  }
}

// -----------------------------------------------------------------------------
void Controller::set(string name, string value)
{
  cout << " | "; // Dekoration

  if(name == "color")
  {
    if(value == "on") {
      arg_color = true;
    } else if(value == "off") {
      arg_color = false;
    } else {
      throw "Falsches Format in der Datei";
    }
    cout << "color: " << value << endl;
  }
  else if(name == "abs style")
  {
    istringstream i(value);
    i >> iso_abs_style;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "abs style: " << iso_abs_style << endl;
  }
  else if(name == "abs scale")
  {
    istringstream i(value);
    i >> iso_abs_scale;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "abs scale: " << iso_abs_scale << endl;
  }
  else if(name == "abs int")
  {
    istringstream i(value);
    i >> iso_abs_int;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "abs int: " << iso_abs_int << endl;
  }
  else if(name == "arg count")
  {
    istringstream i(value);
    i >> iso_arg_count;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "arg count: " << iso_arg_count << endl;
  }
  else if(name == "arg thick")
  {
    istringstream i(value);
    i >> iso_arg_thick;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "arg thick: " << iso_arg_thick << endl;
  }
  else if(name == "arg int")
  {
    istringstream i(value);
    i >> iso_arg_int;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "arg int: " << iso_arg_int << endl;
  }
  else if(name == "grid")
  {
    if(value == "on") {
      use_grid = true;
    } else if(value == "off") {
      use_grid = false;
    } else {
      throw "Falsches Format in der Datei";
    }
    cout << "grid: " << value << endl;
  }
  else if(name == "grid scale")
  {
    istringstream i(value);
    i >> grid_scale;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "grid scale: " << grid_scale << endl;
  }
  else if(name == "grid int")
  {
    istringstream i(value);
    i >> grid_int;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "grid int: " << grid_int << endl;
  }
  else if(name == "bounds")
  {
    istringstream i(value);
    i >> start >> end;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "bounds: " << start << " " << end << endl;
  }
  else if(name == "function")
  {
    Parser parser(value);
    parser.parse();

    delete function;
    function = parser.getExpr();
    function->simplify();

    cout << "function: ";
    function->print(cout);
    cout << endl;
  }
  else if(name == "iterations")
  {
    istringstream i(value);
    i >> iterations;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "iterations: " << iterations << endl;
  }
  else if(name == "size")
  {
    istringstream i(value);
    i >> width >> height;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "size: " << width << "px * " << height << "px" << endl;
  }
  else if(name == "name")
  {
    istringstream i(value);
    i >> fname;
    if(i.fail()){
      throw "Falsches Format in der Datei";
    }
    cout << "filename: " << fname << endl;
  }
  else // unbekannter name
  {
    cout << "\b\b\b"; // Dekoration rückgängig machen
    throw "unbekannter Parametername";
  }
}


// -----------------------------------------------------------------------------
void Controller::draw(Bitmap& map)
{
  // Entfehrnung zwischen zwei Pixeln
  double dx = Re(end - start) / width;
  double dy = Im(end - start) / height;

  // gehe mit start in die Mitte des ersten Pixels
  start += 0.5 * Complex(dx, dy);
  Complex z;

  // Bild-Zeilen-Schleife
  for(int x, y = 0; y < height; ++y) {
    // Statusanzeige
    cout << '\r' << "Rendering: " << 100 * y / height << "%";

    // Bild-Spalten-Schleife
    for(x = 0; x < width; ++x) {
      z = start + Complex(x * dx, y * dy);
      for(int i = 0; i < iterations; ++i){
        z = function->eval(z);
      }
      map.set_pixel(x, y, CompToRGB(z));
    }
  }
  cout << '\r' << "Rendering: 100%\n";
}
