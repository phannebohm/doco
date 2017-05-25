/**
 * @file Bitmap.h
 * @brief Diese Datei beinhaltet eine Klasse Bitmap (zusammen mit Hilfsklassen)
 * für die Erzeugung einer BMP-Datei.
 * @author Philip Hannebohm
 * @date 06/12/2015
 */

#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h> /* uint_8, uint_16, uint_32, int_32 */


// Damit die Daten in der richtigen Ausrichtung und ohne Füll-Bytes abgespeichert
// werden, wird der Präprozessor-Befehl pragma pack benötigt. Ansonsten könnte die
// Datei nicht richtig gespeichert werden.
//
// Beispiel:
//                   normal                       pragma pack(2)   pragma pack(1)
//   struct foo      (3*4=12 Bytes)               (4*2=8 Bytes)    (7*1=7 Bytes)
//   {
//     char a;       |  1  |  2  |  3  |  4  |    |  1  |  2  |    |  1  |
//     int b;        -------------------------    -------------    -------
//     short c;      | a_1 | ... füllen  ... |    | a_1 | ... |    | a_1 |
//   };              | b_1 | b_2 | b_3 | b_4 |    | b_1 | b_2 |    | b_1 |
//                   | c_1 | c_2 | ...   ... |    | b_3 | b_4 |    | b_2 |
//                                                | c_1 | c_2 |    | b_3 |
//                                                                 | b_4 |
//                                                                 | c_1 |
//                                                                 | c_2 |
// Da wir überhaupt gar keine Füll-Bytes haben wollen, benutzen wir:
#pragma pack(push, 1)


/**
 * @struct BITMAP_FILEHEADER
 * @date 06/12/2015
 * @brief Hilfsstruktur
 */
struct BITMAP_FILEHEADER
{
  uint16_t type;      ///< magic number ("BM" = 0x4D42)
  uint32_t size;      ///< Größe der Bitmap-Datei in Byte
  uint32_t reserved;    ///< ungenutzt (0)
  uint32_t offbits;    ///< Offset der Bilddaten in Byte vom Beginn der Datei (54)
};


/**
 * @struct BITMAP_INFOHEADER
 * @date 06/12/2015
 * @brief Hilfsstruktur
 */
struct BITMAP_INFOHEADER
{
  uint32_t size;      ///< Größe der Struktur INFOHEADER in Byte (40)
  int32_t  width;      ///< Breite der Bitmap in Pixel
  int32_t  height;    ///< Höhe der Bitmap in Pixel (hier immer positiv)
  uint16_t planes;    ///< ungenutzt (1)
  uint16_t bitcount;    ///< Farbtiefe in BitsPerPixel (32)
  uint32_t compression;  ///< Art der Kompression: unkomprimiert (0 = BI_RGB)
  uint32_t sizeimage;    ///< Größe der Bilddaten in Byte
  int32_t  xppm;      ///< ungenutzt (0)
  int32_t  yppm;      ///< ungenutzt (0)
  uint32_t clrused;    ///< Anzahl Einträge in Farbtabelle (0 = keine Farbtabelle)
  uint32_t clrimportant;  ///< ungenutzt (0)
};


/**
 * @class RGBA
 * @date 10/12/2015
 * @brief Hilfsklasse zum halten von Farbinformation
 */
class RGBA
{
private:
  uint8_t blue;      ///< Blauanteil
  uint8_t green;      ///< Grünanteil
  uint8_t red;      ///< Rotanteil
  uint8_t alpha;      ///< Transparenz, ungenutzt
public:
  /**
   * @fn RGBA
   * @brief setzt die Farbwerte
   * @param[in] red  Rotanteil zwischen 0 und 1
   * @param[in] green  Grünanteil zwischen 0 und 1
   * @param[in] blue  Blauanteil zwischen 0 und 1
   */
  RGBA(double red = 0, double green = 0, double blue = 0);
};

#pragma pack(pop)


/**
 * @class Bitmap
 * @date 06/12/2015
 * @brief Diese Klasse hält alle Daten und Methoden für die Erzeugung einer Bitmap-Datei
 */
class Bitmap
{
private:
  BITMAP_FILEHEADER file_header;
  BITMAP_INFOHEADER info_header;
  RGBA* pixels;
public:
  /**
   * @fn Bitmap
   * @brief allokiert den benötigten Speicher für pixels
   * @param[in] width  Breite des zu erzeugenden Bildes
   * @param[in] height  Höhe des zu erzeugenden Bildes
   * @throws bad_alloc falls der Speicher nicht reserviert werden kann
   */
  Bitmap(unsigned int width, unsigned int height);

  /**
   * @fn ~Bitmap
   * @brief gibt den belegten Speicher für pixels wieder frei
   */
  ~Bitmap();

  /**
   * @fn set_pixel
   * @brief setzt den Pixel an der angegebenen Position auf die angegebene Farbe
   * @param[in] x  Spalte
   * @param[in] y  Zeile
   * @param[in] color  eine Farbe
   */
  void set_pixel(int x, int y, const RGBA& color);

  /**
   * @fn save
   * @brief speichert die Pixeldaten in eine Datei
   * @param[in] filename  Der Name der Datei
   * @throws falls die Datei nicht gespeichert werden konnte
   */
  void save(const char* filename);
};

#endif // BITMAP_H
