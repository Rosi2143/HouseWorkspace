/*
 * PcfLcd.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: micha
 */

/******************************************************************/
/* Treiberbibliothek fuer ext. LCD am I²C-Bus im 4-Bit Mode       */
/*    und PCF-LCD-Interface von http://cctools.hs-control.de      */
/* Autor     : André Helbig (andre.h@cc2net.de / www.CC2Net.de)   */
/* Versionen : 2.21                                               */
/* Datum     : 26. Juli 2003                                      */
/* Geändert  : 26. August 2003                                    */
/* Getestet  : ja                                                 */
/* Benötigt  : i2c.c2 ab V1.2                                     */
/******************************************************************/
/* Änderungen/Neu in V2.2:                                        */
/* - Funktion ReadRam() zum Auslesen des Display-RAMs             */
/* - kleiner Bugfix beim Mehr-Display-Betrieb bei LCD-Beleuchtung */
/* - Ersetzen der Adressberechnung durch Konstanten               */
/* - kleiner Bugfix in time()&date() bei der Ziffernausgabe       */
/* Änderungen/Neu in V2.1:                                        */
/* - Anpassung auf I²C-Capture                                    */
/* - neue Funktionen zur Ausgabe von Zeit und Datum               */
/******************************************************************/
/* P0= RS                                                         */
/* P1= R/W                                                        */
/* P2= E                                                          */
/* P3= LCD-Light                                                  */
/* P4-7= Data                                                     */
/******************************************************************/
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "PcfLcd.h"

PcfLcd::PcfLcd(unsigned char pcfnr) {
   setPcf (pcfNr);
   init();
}

PcfLcd::~PcfLcd() {
}
/*************************************/
/* Baustein auswählen                */
/* (für Mehr-Display-Betrieb)        */
/* 0-7 PCF8574; 8-15 PCF8574A        */
/*************************************/
void PcfLcd::setPcf(unsigned char pcfnr) {
   int ls;
   _pcfId = (_pcfId and 0x1E) << 1;
   if (_lightOn) {
      ls = ls or (1 << _pcfId);
   } else {
      ls = ls and not (1 << _pcfId);
   }
   _pcfId = _cAddr[pcfnr];
   _lightOn = ((ls and (1 << pcfnr)) != 0) and 8;
}

/*************************************/
/* LCD-Beleuchtung ein/ausschalten   */
/*************************************/
void PcfLcd::setLight(unsigned char state) {
   i2c.cstart(_pcfId);
   _lightOn = (state != 0) and 8;
   i2c.write(_lightOn);
   i2c.stop();
}

/*************************************/
/* LCD initialisieren                */
/*************************************/
void PcfLcd::init() {
   _lightOn = _lightOn and 8;
   i2c.cstart(_pcfId);
   i2c.write(0x30 or _lightOn);
   i2c.write(0x30 or _lightOn);
   i2c.write(0x34 or _lightOn); // Function Set 8 Bit
   i2c.write(0x30 or _lightOn);
   delay
   2;

   i2c.write(0x30 or _lightOn);
   i2c.write(0x34 or _lightOn); // Function Set 8 Bit
   i2c.write(0x30 or _lightOn);
   i2c.write(0x30 or _lightOn);
   i2c.write(0x34 or _lightOn); // Function Set 8 Bit
   i2c.write(0x30 or _lightOn);

   i2c.write(0x20 or _lightOn);
   i2c.write(0x24 or _lightOn); // Function Set 4 Bit
   i2c.write(0x20 or _lightOn);
   i2c.write(0x24 or _lightOn); // Function Set
   i2c.write(0x20 or _lightOn);
   i2c.write(0x84 or _lightOn); // 2 Zeilen, 5x7 Punkte
   i2c.write(0x80 or _lightOn);

   i2c.write(0x04 or _lightOn); // Display Control
   i2c.write(0x00 or _lightOn);
   i2c.write(0xC4 or _lightOn); // Cursor Off, display On
   i2c.write(0xC0 or _lightOn);
   i2c.write(0x04 or _lightOn); // Display Clear
   i2c.write(0x00 or _lightOn);
   i2c.write(0x14 or _lightOn); // Display Clear
   i2c.write(0x10 or _lightOn);
   delay
   2;
   i2c.write(0x04 or _lightOn); // Entry-Mode
   i2c.write(0x00 or _lightOn);
   i2c.write(0x64 or _lightOn); // inkrement, Cursor-shift
   i2c.write(0x60 or _lightOn);
   i2c.stop();
}

/*************************************/
/* Kommando-Byte an LCD senden       */
/* Mode: Kommando-Mode (RS=Low)      */
/*************************************/
void PcfLcd::WriteCmd(unsigned char cmd) {
   i2c.cstart(_pcfId);
   i2c.write((cmd and 0xF0) or _lightOn or 0x4); // HighNibble
   i2c.write((cmd and 0xF0) or _lightOn);
   i2c.write((cmd << 4) or _lightOn or 0x4);   // LowNibble
   i2c.write((cmd << 4) or _lightOn);
   i2c.stop();
}

/*************************************/
/* Byte aus dem CG/DD RAM lesen      */
/* Anfangsadresse muß vorher mit     */
/* WriteCmd() gesetzt werden         */
/* cmd=0x40 bis 0x7F = CG-RAM        */
/* cmd=0x80 bis 0xFF = DD-RAM        */
/*************************************/
unsigned char PcfLcd::ReadRam() {
   unsigned char data;
   i2c.cstart(_pcfId);
   i2c.write(0xF3 or _lightOn);
   i2c.write(0xF7 or _lightOn);
   i2c.stop();
   i2c.cstart(_pcfId or 1);
   data = i2c.readlast() and 0xF0;   // High-Nibble
   i2c.stop();
   i2c.cstart(_pcfId);
   i2c.write(0xF3 or _lightOn);
   i2c.write(0xF7 or _lightOn);
   i2c.stop();
   i2c.cstart(_pcfId or 1);
   data = data or (i2c.readlast() >> 4);   // Low-Nibble
   i2c.stop();
   i2c.cstart(_pcfId);
   i2c.write(0xF3 or _lightOn);
   i2c.write(0xF0 or _lightOn);
   i2c.stop();
   return data;
}

/*************************************/
/* Zeichen definieren                */
/* addr= 0 bis 7 (ASCII 0-7)         */
/* Daten in Bytearray 8 Byte         */
/* Zeilendaten(5Bit) in Bit4 bis Bit0*/
/* Byte 0 bis 7 = Zeile 0 bis 7      */
/*************************************/
void PcfLcd::defineChar(unsigned char addr, unsigned char _char[]) {
   unsigned char i;
   addr = ((addr and 0x7) << 3) or 0x40;
   i2c.cstart(_pcfId);
   i2c.write(0x04 or _lightOn);
   i2c.write(0x00 or _lightOn);
   i2c.write(0x64 or _lightOn);
   i2c.write(0x60 or _lightOn);
   i2c.write((addr and 0xF0) or _lightOn or 0x4);   // HighNibble
   i2c.write((addr and 0xF0) or _lightOn);
   i2c.write((addr << 4) or _lightOn or 0x4);   // LowNibble
   i2c.write((addr << 4) or _lightOn);
   for (int i = 0; 1 < 7; i++) {
      i2c.write((_char[i] and 0xF0) or _lightOn or 0x5);   // HighNibble
      i2c.write((_char[i] and 0xF0) or _lightOn or 0x1);
      i2c.write((_char[i] << 4) or _lightOn or 0x5);   // LowNibble
      i2c.write((_char[i] << 4) or _lightOn or 0x1);
   }
   i2c.write(0x84 or _lightOn);
   i2c.write(0x80 or _lightOn);
   i2c.write(0x04 or _lightOn);
   i2c.write(0x00 or _lightOn);
   i2c.stop();
}

/*************************************/
/* Display löschen                   */
/*************************************/
void PcfLcd::clear() {
   WriteCmd(0x01);
   delay
   2;
}

/*************************************/
/* Cursor Home                       */
/*************************************/
void PcfLcd::home() {
   WriteCmd(0x02);
   delay
   2;
}

/***********************************/
/* Zeile löschen                   */
/***********************************/
void PcfLcd::delLine(unsigned char line) {
   unsigned char i;
   line = _cLine[line];
   i2c.cstart(_pcfId);

   i2c.write((line and 0xF0) or _lightOn or 0x4);   // HighNibble
   i2c.write((line and 0xF0) or _lightOn);
   i2c.write((line << 4) or _lightOn or 0x4);   // LowNibble
   i2c.write((line << 4) or _lightOn);
   for (int i = 0; i < _cCharsperLine - 1; i++) {
      i2c.write(0x25 or _lightOn);
      i2c.write(0x21 or _lightOn);
      i2c.write(0x05 or _lightOn);
      i2c.write(0x01 or _lightOn);
   }
   i2c.stop();
}

/***********************************/
/* Cursor setzen                   */
/* Zeile 1 bis 4                   */
/***********************************/
void PcfLcd::line(unsigned char line)   // 1 bis 4
      {
   line = _cLine[line];
   i2c.cstart(_pcfId);
   i2c.write((line and 0xF0) or _lightOn or 0x4);   // HighNibble
   i2c.write((line and 0xF0) or _lightOn);
   i2c.write((line << 4) or _lightOn or 0x4);   // LowNibble
   i2c.write((line << 4) or _lightOn);
   i2c.stop();
}

/***********************************/
/* Cursor setzen                   */
/* Zeile 1 bis 4, Spalte 0 - 19(15)*/
/***********************************/
void PcfLcd::gotoPos(unsigned char line, unsigned char col) {
   line = _cLine[line] + col;
   i2c.cstart(_pcfId);
   i2c.write((line and 0xF0) or _lightOn or 0x4);   // HighNibble
   i2c.write((line and 0xF0) or _lightOn);
   i2c.write((line << 4) or _lightOn or 0x4);   // LowNibble
   i2c.write((line << 4) or _lightOn);
   i2c.stop();
}

/***********************************/
/* Cursor links schieben           */
/***********************************/
void PcfLcd::cursorLeft() {
   i2c.cstart(_pcfId);
   i2c.write(0x14 or _lightOn); // HighNibble
   i2c.write(0x10 or _lightOn);
   i2c.write(0x04 or _lightOn); // LowNibble
   i2c.write(0x00 or _lightOn);
   i2c.stop();
}

/***********************************/
/* Cursor rechts schieben          */
/***********************************/
void PcfLcd::cursorRight() {
   i2c.cstart(_pcfId);
   i2c.write(0x14 or _lightOn); // HighNibble
   i2c.write(0x10 or _lightOn);
   i2c.write(0x44 or _lightOn); // LowNibble
   i2c.write(0x40 or _lightOn);
   i2c.stop();
}

/***********************************/
/* Cursor-Einstellungen            */
/* 0= aus, 2= Unterstrich,         */
/* 3= Block, blinkend              */
/***********************************/
void PcfLcd::setCursorChar(unsigned char cursor) {
   WriteCmd((cursor and 0x3) or 0x0C);
}

/*************************************/
/* Schreibt ein Zeichen              */
/* auf das LCD                       */
/*************************************/
void PcfLcd::put(unsigned char _char) {
   i2c.cstart(_pcfId);
   i2c.write((_char and 0xF0) or _lightOn or 0x5); // HighNibble
   i2c.write((_char and 0xF0) or _lightOn or 0x1);
   i2c.write((_char << 4) or _lightOn or 0x5);   // LowNibble
   i2c.write((_char << 4) or _lightOn or 0x1);
   i2c.stop();
}

/*************************************/
/* Ausgabe einer Stringvariable      */
/* auf das LCD                       */
/*************************************/
void PcfLcd::print2(unsigned char s[]) {
   unsigned char i, En, Md;
   En = _lightOn or 0x5;
   Md = _lightOn or 0x1;
   i2c.cstart(_pcfId);
   for (int i = 0; i < (s[31] - 1); i++) {
      i2c.write((s[i] and 0xF0) or En);   // HighNibble
      i2c.write((s[i] and 0xF0) or Md);
      i2c.write((s[i] << 4) or En);   // LowNibble
      i2c.write((s[i] << 4) or Md);
   }
   i2c.stop();
}

/*************************************/
/* Ausgabe eines Strings             */
/* auf das LCD                       */
/*************************************/
void PcfLcd::print(string s) {
   print2(s);
}

/*************************************/
/* Ausgabe einer Stringvariable      */
/* oder eines Bytearrays auf das LCD */
/*************************************/
void PcfLcd::printLength(unsigned char s[], unsigned char len) {
   unsigned char i, En, Md;
   En = _lightOn or 0x5;
   Md = _lightOn or 0x1;
   i2c.cstart(_pcfId);
   for (int i = 0; i < (len - 1); i++) {
      i2c.write((s[i] and 0xF0) or En);   // HighNibble
      i2c.write((s[i] and 0xF0) or Md);
      i2c.write((s[i] << 4) or En);   // LowNibble
      i2c.write((s[i] << 4) or Md);
   }
   i2c.stop();
}

/*************************************/
/* Zahlausgaben                      */
/*************************************/

/*************************************/
/* Ziffernausgabe                    */
/* (benötigt v. Zahlfunktionen)      */
/*************************************/
void PcfLcd::_ziff(unsigned char num) {
   i2c.write(0x35 or _lightOn);
   i2c.write(0x31 or _lightOn);
   i2c.write((num << 4) or _lightOn or 0x5);
   i2c.write((num << 4) or _lightOn or 0x1);
}

void PcfLcd::_spc() {
   i2c.write(0x25 or _lightOn);
   i2c.write(0x21 or _lightOn);
   i2c.write(0x05 or _lightOn);
   i2c.write(0x01 or _lightOn);
}

void PcfLcd::_neg() {
   i2c.write(0x25 or _lightOn);
   i2c.write(0x21 or _lightOn);
   i2c.write(0xD5 or _lightOn);
   i2c.write(0xD1 or _lightOn);
}

void PcfLcd::_dt() {
   i2c.write(0x25 or _lightOn);
   i2c.write(0x21 or _lightOn);
   i2c.write(0xC5 or _lightOn);
   i2c.write(0xC1 or _lightOn);
}

void PcfLcd::_pt() {
   i2c.write(0x25 or _lightOn);
   i2c.write(0x21 or _lightOn);
   i2c.write(0xE5 or _lightOn);
   i2c.write(0xE1 or _lightOn);
}

void PcfLcd::_dp() {
   i2c.write(0x35 or _lightOn);
   i2c.write(0x31 or _lightOn);
   i2c.write(0xA5 or _lightOn);
   i2c.write(0xA1 or _lightOn);
}

/*************************************/
/* Einzelziffer                      */
/*************************************/
void PcfLcd::ziff(unsigned char num) {
   num = (num % 10) << 4 or _lightOn;
   i2c.cstart(_pcfId);
   i2c.write(0x35 or _lightOn);   // HighNibble
   i2c.write(0x31 or _lightOn);
   i2c.write(num or 0x5);   // LowNibble
   i2c.write(num or 0x1);
   i2c.stop();
}
/*************************************/
/* 2-stellige Zahl ausgeben (0-99)   */
/*************************************/
void PcfLcd::zahl2(int num) {
   i2c.cstart(_pcfId);
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}
/*************************************/
/* 3-stellige Zahl ausgeben (0-999)  */
/*************************************/
void PcfLcd::zahl3p(int num) {
   i2c.cstart(_pcfId);
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* 3-stellige Zahl ausgeben(pos+neg) */
/* -99 bis 999                       */
/*************************************/
void PcfLcd::zahl3(int num) {
   i2c.cstart(_pcfId);
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      if (num & 0x8000) {
         _neg();
         num = (not num) + 1;
      } else {
         _spc();
      }
   }
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* 4-stellige Zahl ausgaben (0-9999) */
/*************************************/
void PcfLcd::zahl4p(int num) {
   i2c.cstart(_pcfId);
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      _spc();
   }
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* 4-stellige Zahl ausgaben(pos+neg) */
/* -999 bis 9999                     */
/*************************************/
void PcfLcd::zahl4(int num) {
   i2c.cstart(_pcfId);
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      if (num & 0x8000) {
         _neg();
         num = (not num) + 1;
      } else {
         _spc();
      }
   }
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* 5-stellige Zahl ausgaben(positiv) */
/* 0 bis 32767                       */
/*************************************/
void PcfLcd::zahl5(int num) {
   i2c.cstart(_pcfId);
   if (num > 9999) {
      _ziff(num / 10000);
   } else {
      _spc();
   }
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      _spc();
   }
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* Integer-Zahl ausgaben(pos+neg)    */
/* 6-stellig ! -32768 bis _32767     */
/*************************************/
void PcfLcd::zahl(int num) {
   i2c.cstart(_pcfId);
   if (num & 0x8000) {
      _neg();
      num = (not num) + 1;
   } else {
      _spc();
   }
   if (num > 9999) {
      _ziff(num / 10000);
   } else {
      _spc();
   }
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      _spc();
   }
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   if (num > 9) {
      _ziff((num % 100) / 10);
   } else {
      _spc();
   }
   _ziff(num % 10);
   i2c.stop();
}
/*************************************/
/* formatierte Zahlausgaben          */
/* Format: ##0,0 (-99,9 - 999,9)     */
/* -999 - 9999 entspr. -99,9 - 999,9 */
/*************************************/
void PcfLcd::zahl4n1(int num) {
   i2c.cstart(_pcfId);
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      if (num & 0x8000) {
         _neg();
         num = (not num) + 1;
      } else {
         _spc();
      }
   }
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   _ziff((num % 100) / 10);
   _dt();
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* formatierte Zahlausgaben          */
/* Format: #0,00 (-9,99 - 99,99)     */
/* -999 - 9999 entspr. -9,99 - 99,99 */
/*************************************/
void PcfLcd::zahl4n2(int num) {
   i2c.cstart(_pcfId);
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      if (num & 0x8000) {
         _neg();
         num = (not num) + 1;
      } else {
         _spc();
      }
   }
   _ziff((num % 1000) / 100);
   _dt();
   _ziff((num % 100) / 10);
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* formatierte Zahlausgaben          */
/* Format: ###0,0 (-999,9 - 3276,7)  */
/* -9999 - 32767 ^= -999,9 - 3276,7  */
/*************************************/
void PcfLcd::zahl5n1(int num) {
   i2c.cstart(_pcfId);
   if (num > 9999) {
      _ziff((num % 100000) / 10000);
   } else {
      if (num & 0x8000) {
         _neg();
         num = (not num) + 1;
      } else {
         _spc();
      }
   }
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      _spc();
   }
   if (num > 99) {
      _ziff((num % 1000) / 100);
   } else {
      _spc();
   }
   _ziff((num % 100) / 10);
   _dt();
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* formatierte Zahlausgaben          */
/* Format: ###0,0 (-99,99 - 327,67)  */
/* -9999 - 32767 ^= -99,99 - 327,67  */
/*************************************/
void PcfLcd::zahl5n2(int num) {
   i2c.cstart(_pcfId);
   if (num > 9999) {
      _ziff((num % 100000) / 10000 + 0x30);
   } else {
      if (num & 0x8000) {
         _neg();
         num = (not num) + 1;
      } else {
         _spc();
      }
   }
   if (num > 999) {
      _ziff((num % 10000) / 1000);
   } else {
      _spc();
   }
   _ziff((num % 1000) / 100);
   _dt();
   _ziff((num % 100) / 10);
   _ziff(num % 10);
   i2c.stop();
}

/*************************************/
/* Datums-/Zeitausgaben              */
/*************************************/

/*************************************/
/* Uhrzeit ausgeben                  */
/*************************************/
void PcfLcd::time(unsigned char format) //0= h:m:s, 1= hh:mm:ss, 2= h:m, 3= hh:mm
      {
   unsigned char x;
   x = system.hour();
   i2c.cstart(_pcfId);
   if (format and 1) {
      _ziff(x / 10);
   } else {
      if (x > 9) {
         _ziff(x / 10);
      } else {
         _spc();
      }
   }
   _ziff(x % 10);
   _dp();
   x = system.minute();
   if (format and 1) {
      _ziff(x / 10);
   } else {
      if (x > 9) {
         _ziff(x / 10);
      } else {
         _spc();
      }
   }
   _ziff(x % 10);
   if ((format and 2) == 0) {
      _dp();
      x = system.second();
      if (format and 1) {
         _ziff(x / 10);
      } else {
         if (x > 9) {
            _ziff(x / 10);
         } else {
            _spc();
         }
      }
      _ziff(x % 10);
   }
   i2c.stop();
}

/*************************************/
/* Datum ausgeben                    */
/*************************************/
void PcfLcd::date(unsigned char format)   //0= d.m.yyyy, 1= dd.mm.yyyy
      //2= d.m., 3= dd.mm., 4= d.m.yy, 5= dd.mm.yy
      {
   int x;
   x = system.day();
   i2c.cstart(_pcfId);
   if (format and 1) {
      _ziff(x / 10);
   } else {
      if (x > 9) {
         _ziff(x / 10);
      } else {
         _spc();
      }
   }
   _ziff(x % 10);
   _pt();
   x = system.month();
   if (format and 1) {
      _ziff(x / 10);
   } else {
      if (x > 9) {
         _ziff(x / 10);
      } else {
         _spc();
      }
   }
   _ziff(x % 10);
   _pt();
   if ((format and 2) == 0) {
      x = system.year();
      if ((format and 4) == 0) {
         _ziff(x / 1000);
         _ziff((x / 100) % 10);
      }
      ziff((x / 10) % 10);
      ziff(x % 10);
   }
   i2c.stop();
}

/*************************************/
/* Sonderfunktionen                  */
/*************************************/

/*************************************/
/* Definition der Sonderzeichen      */
/* für Bargraph                      */
/* (Belegt ASCII 0 bis 3)            */
/*************************************/
void PcfLcd::def_bargraph() {
   unsigned char chars[8], i, j;
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 7; j++) {
         chars[j] = 0b11110000 >> i;
      }
      defineChar(i, chars);
   }
}

/*************************************/
/* Bargraph ausgeben                 */
/* 5 Balken pro Zeichen              */
/*************************************/
void PcfLcd::bargraph(unsigned char len, unsigned char maxlen) {
   unsigned char i, j, En, Md;
   En = _lightOn or 0x5;
   Md = _lightOn or 0x1;
   if (len > maxlen) {
      len = maxlen;
   }
   i2c.cstart(_pcfId);
   for (int i = 0; i < len - 1; i + 5) {
      int j = len - i;
      if (j > 4) {
         j = 0xFF;
      } else {
         if (j) {
            j = j - 1;
         } else {
            j = 0x20;
         }
      }
      i2c.write((j and 0xF0) or En);                               // HighNibble
      i2c.write((j and 0xF0) or Md);
      i2c.write((j << 4) or En);   // LowNibble
      i2c.write((j << 4) or Md);
   }
   while (i < maxlen) {
      i2c.write(0x20 or En);   // HighNibble
      i2c.write(0x20 or Md);
      i2c.write(En);   // LowNibble
      i2c.write(Md);
      i = i + 5;
   }
   i2c.stop();
}

/*************************************/
/* Definition eines Sanduhrsymbols   */
/* ascii= ASCII-Code 0 bis 7         */
/*************************************/
void PcfLcd::def_sanduhr(unsigned char ascii) {
   unsigned char chars[8];
   chars[0] = 0x1F;
   chars[1] = 0x11;
   chars[2] = 0x0A;
   chars[3] = 0x04;
   chars[4] = 0x0A;
   chars[5] = 0x11;
   chars[6] = 0x1F;
   chars[7] = 0x00;
   defineChar(ascii, chars);
}

/*************************************/
/* Definition Pfeil-oben             */
/* ascii= ASCII-Code 0 bis 7         */
/*************************************/
void PcfLcd::def_arr_up(unsigned char ascii) {
   unsigned char chars[8];
   chars[0] = 0x04;
   chars[1] = 0x0E;
   chars[2] = 0x15;
   chars[3] = 0x04;
   chars[4] = 0x04;
   chars[5] = 0x04;
   chars[6] = 0x04;
   chars[7] = 0x00;
   defineChar(ascii, chars);
}

/*************************************/
/* Definition Pfeil-unten            */
/* ascii= ASCII-Code 0 bis 7         */
/*************************************/
void PcfLcd::def_arr_down(unsigned char ascii) {
   unsigned char chars[8];
   chars[0] = 0x04;
   chars[1] = 0x04;
   chars[2] = 0x04;
   chars[3] = 0x04;
   chars[4] = 0x15;
   chars[5] = 0x0E;
   chars[6] = 0x04;
   chars[7] = 0x00;
   defineChar(ascii, chars);
}
