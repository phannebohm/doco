/**
 * @file Controller.h
 * @brief Diese Datei enthält eine Klasse zur Steuerung des Programmablaufs.
 * @author Philip Hannebohm
 * @date 10/02/2016
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Bitmap.h"
#include "Complex.h"
#include "Expr.h"

#include <string> /* string */


/**
 * @class Controller
 * @date 10/02/2016
 * @brief Diese Klasse speichert alle wichtigen Daten und steuert den Programmablauf
 */
class Controller
{
private:
  ///@{
  bool   arg_color;      ///< gibt an, ob das Argument eingefärbt wird

  int    iso_abs_style;  ///< Darstellung des Betrags (0=keine, 1=Helligkeit, 2=Isolinien)
  double iso_abs_scale;  ///< größer als 1, je größer desto mehr Abstand zwischen zwei Isolinien
  double iso_abs_int;    ///< Intensität/Farbstärke

  int    iso_arg_count;  ///< Anzahl an Isolinien für das Argument (0=keine Isolinien)
  double iso_arg_thick;  ///< Liniendicke
  double iso_arg_int;    ///< Intensität/Farbstärke

  bool   use_grid;       ///< gibt an, ob ein Schachbrettmuster gezeichnet werden soll
  double grid_scale;     ///< die Kantenlänge der Kästchen
  double grid_int;       ///< Intensität/Farbstärke
  ///@}

  ///@{
  Complex start;  ///< Startpunkt (unten links)
  Complex end;    ///< Zielpunkt (oben rechts)

  Expr* function; ///< Die zu zeichnende Funktion
  int iterations; ///< Anzahl an Iterationen

  int width;      ///< Bildbreite
  int height;     ///< Bildhöhe

  std::string fname; ///< Name der zu erzeugenden Datei
  ///@}


  /**
   * @fn set
   * @brief Die Eigenschaft name wird auf den/die Wert/e in value gesetzt
   * @param[in] name  Der Name der zu setzenden Eigenschaft
   * @param[in] value  string der die Daten enthält
   */
  void set(std::string name, std::string value);

  /**
   * @fn draw
   * @brief Hier befindet sich die Schleife, die die Pixelwerte berechnet.
   * @param[in] map Bitmap-Objekt in das gezeichnet wird
   */
  void draw(Bitmap& map);

  /**
   * @fn CompToRGB
   * @brief komplexe Zahl in Farbe umwandeln
   * @param[in] z  komplexe Zahl
   * @return die erzeugte Farbe
   */
  RGBA CompToRGB(const Complex& z) const;

public:
  // Konstruktor mit Standardwerten
  Controller();
  ~Controller();

  /**
   * @fn read
   * @brief liest die Infos aus der Datei in dieses Objekt, ruft draw auf, und speichert das Bild
   * @param[in] input_name  Name der Datei
   */
  void read(const char* input_name);
};

#endif // CONTROLLER_H
