/**
 * @file main.cpp
 * @brief Hier startet das Hauptprogramm
 * @author Philip Hannebohm
 * @date 06/02/2016
 */

#include "Controller.h"

#include <iostream> /* cout */
#include <cstring> /* strcmp */

using std::cout;

int main(int argc, char **argv)
{
  cout << "==== doco - Domain Coloring ====\n";

  if(argc == 2 && strcmp(argv[1], "--help") == 0 ) { // Hilfetext
    cout << "\nVerwendung:\n"
         << "  doco [Dateiname...]+         Geben Sie eine Liste von Dateien an. Die darin enthaltene Parameterliste wird zum Erstellen der Bilder verwendet.\n"
         << "  doco --help                  Ruft diesen Hilfetext auf\n"
         << "\nAllgemeine Parameter:\n"
         << "  function:   <funktionsterm>  Funktionsterm der zu zeichnenden Funktion (Variable z)\n"
         << "  bounds:     <start> <ende>   Zwei komplexe Zahlen (x1,y1) (x2,y2) für den darzustellenden Bereich\n"
         << "\nErweitere Parameter:\n"
         << "  abs int:    <intensitaet>    Intensitaet des Betrags (zwischen 0 und 1)\n"
         << "  abs scale:  <skalierung>     Verhältnis zwischen zwei Isolinien (z.B. 2 = Linie bei jeder Betragsverdoppelung)\n"
         << "  abs style:  <style>          Darstellung des Betrags (0=keine, 1=Helligkeitsverlauf, 2=Isolinien)\n"
         << "  arg count:  <anzahl>         Anzahl an Strahlen mit konstantem Argument (0=keine)\n"
         << "  arg int:    <intensitaet>    Intensitaet der Strahlen (zwischen 0 und 1)\n"
         << "  arg thick:  <dicke>          Dicke der Strahlen (zwischen 0 und 1)\n"
         << "  color:      <on | off>       Gibt an, ob das Argument eingefaerbt wird\n"
         << "  grid:       <on | off>       Schaltet das Koordinatengitter ein/aus\n"
         << "  grid int:   <intensitaet>    Intensitaet des Gitters (zwischen 0 und 1)\n"
         << "  grid scale: <skalierung>     Gibt die Groesse der Kaestchen an\n"
         << "  iterations: <anzahl>         Anzahl an Iterationen der Funktion (default 1)\n"
         << "  name:       <name>           Die erzeugte Bilddatei bekommt diesen Namen\n"
         << "  size:       <breite> <hoehe> Gibt an wie gross das Bild werden soll\n";
    return 0;
  }

  for(int i = 1; i < argc; ++i) { // gehe alle Input-Dateien durch
    try{
      Controller ctrl;
      ctrl.read(argv[i]); // Eingabedaten einlesen und verarbeiten
    }
    catch (const char* err){
      cout << err;
      cout << "\nDas Programm wird abgebrochen!\n";
    }
  }

  return 0;
}
