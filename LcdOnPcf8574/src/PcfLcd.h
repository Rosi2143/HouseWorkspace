/*
 * PcfLcd.h
 *
 *  Created on: Dec 31, 2014
 *      Author: micha
 */

#ifndef SRC_PCFLCD_H_
#define SRC_PCFLCD_H_


class PcfLcd : public INode{
public:
   PcfLcd(unsigned char pcfnr          = 0);
   virtual ~PcfLcd(){}

   void init();
   void setLight(unsigned char state);

protected:
   void setPcf(unsigned char pcfnr);
   void WriteCmd(unsigned char cmd);
   unsigned char ReadRam();

   // display functions
   void clear();
   void home();
   void delLine(unsigned char line);
   void line(unsigned char line);
   void gotoPos(unsigned char line, unsigned char col);
   void cursorLeft();
   void cursorRight();
   void setCursorChar(unsigned char cursor);

   // print functions
   void put(unsigned char _char);
   void print2(unsigned char s[]);
   void print(string s);
   void printLength(unsigned char s[], unsigned char len);

   // char functions
   void defineChar(unsigned char addr, unsigned char _char[])
   void _ziff(unsigned char num);
   void _spc();
   void _neg();
   void _dt();
   void _pt();
   void _dp();
   void ziff(unsigned char num);
   void zahl2(int num);
   void zahl3p(int num);
   void zahl3(int num);
   void zahl4p(int num);
   void zahl4(int num);
   void zahl5(int num);
   void zahl(int num);
   void zahl4n1(int num);
   void zahl4n2(int num);
   void zahl5n1(int num);
   void zahl5n2(int num);
   void time(unsigned char format);
   void date(unsigned char format);

   // special functions
   void bargraph(unsigned char len, unsigned char maxlen);
   void def_bargraph();
   void def_sanduhr(unsigned char ascii);
   void def_arr_up(unsigned char ascii);
   void def_arr_down(unsigned char ascii);

   const unsigned char _cLine[]= {0x80,0x80,0xC0,0x94,0xD4}; // for 4x20 & LCD with two lines
   const unsigned char _cCharsperLine=20;                  // for 4x20 & LCD with two lines
   //const Line[]= {0x80,0x80,0xC0,0x90,0xD0}; // for 4x16 LCD
   //const CharsperLine=16;                  // for 4x16 LCD

   const unsigned char _cAddr[] = {0x40,0x42,0x44,0x46,0x48,0x4A,0x4C,0x4E, //PCF8574-addresses
                                0x70,0x72,0x74,0x76,0x78,0x7A,0x7C,0x7E};
   unsigned char _pcfId;
   unsigned char _lightOn;
}

#endif /* SRC_PCFLCD_H_ */
