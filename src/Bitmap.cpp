#include "Bitmap.h"

#include <cstring> /* memset */
#include <fstream> /* ofstream */

// -----------------------------------------------------------------------------
// Der RGBA-ctor wandelt Werte zwischen 0 und 1(=100%) in ganze Zahlen zwischen 0 und 255 um.
// Aus Effizienzgründen wird darauf verzichtet zu prüfen, ob die Parameter in den Grenzen liegen.
RGBA::RGBA(double r, double g, double b)
  : blue(b * 255.0), green(g * 255.0), red(r * 255.0), alpha(0)
{}


// -----------------------------------------------------------------------------
// Der Bitmap-ctor
//  - allokiert den Speicher für die Bildpunkte und
//  - initialisiert den Datei-Header und setzt die nötigen Werte.
// (Quelle) Für Details zum Dateiaufbau siehe:
// https://de.wikipedia.org/wiki/Windows_Bitmap
Bitmap::Bitmap(unsigned int w, unsigned int h)
  : pixels(NULL)
{
  pixels = new RGBA[w * h];  // throws bad_alloc

  memset(&file_header, 0, sizeof(file_header));
  memset(&info_header, 0, sizeof(info_header));

  info_header.size = sizeof(BITMAP_INFOHEADER);
  info_header.width = w;
  info_header.height = h;
  info_header.planes = 1;
  info_header.bitcount = 8 * sizeof(RGBA);
  //info_header.compression = 0;
  info_header.sizeimage = w * h * sizeof(RGBA);

  file_header.type = 0x4D42;
  file_header.offbits = sizeof(BITMAP_FILEHEADER) + sizeof(BITMAP_INFOHEADER);
  file_header.size = info_header.sizeimage + file_header.offbits;
}


// -----------------------------------------------------------------------------
Bitmap::~Bitmap()
{
  delete[] pixels;
}


// -----------------------------------------------------------------------------
// Es wird die passende Position berechnet und auf den gewünschten Wert gesetzt
// Aus Effizienzgründen wird darauf verzichtet zu prüfen, ob die Parameter in den Grenzen liegen.
// Da diese Methode niemals direkt vom End-User benutzt wird, besteht auch eigentlich keine Gefahr.
void Bitmap::set_pixel(int x, int y, const RGBA& color)
{
  if(x < 0 || x >= info_header.width || y < 0 || y >= info_header.height) {
    // doesn't happen...
    throw "Zugriff ausserhalb des Speicherbereichs";
  }

  pixels[info_header.width * y + x] = color;
}


// -----------------------------------------------------------------------------
// Die Datei filename wird geöffnet und die Daten werden direkt als Byteblöcke
// aus dem Arbeitsspeicher in die Datei geschrieben.
void Bitmap::save(const char* filename)
{
  std::ofstream file(filename, std::ios::out | std::ios::binary);
  if(!file.is_open()) {
    // BAD ERROR!
    throw "Datei konnte nicht geoeffnet werden";
  }

  file.write((char*) &file_header, sizeof(BITMAP_FILEHEADER));
  file.write((char*) &info_header, sizeof(BITMAP_INFOHEADER));
  file.write((char*) pixels, info_header.sizeimage);

  file.close();
}
