/*
 * blink.c:
 *	Simple "blink" test for the PiFace interface board.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <piFace.h>

#include <boost/program_options.hpp>
#include <vector>

enum _WhatToDo{
  none,
  blink,
  rotate,
  inout,
  randomly,
  swipe
};

enum _Direction{
   left = true,
   right = false
};
// Use 200 as the pin-base for the PiFace board, and pick a pin
//	for the Led that's not connected to a relay

#define  PIFACE      200
#define  FIRST_LED   10
#define  MAX_LEDS    6
int Led;
int Delay;

/**
 * blink a single LED
 */
void Blink(void) {
   digitalWrite (Led, HIGH) ;   // On
   delay (Delay) ;    // mS
   digitalWrite (Led, LOW) ; // Off
   delay (Delay) ;
}

/**
 * rotate a single LED
 * @param direction left or right
 */
void Rotate(_Direction direction, int NumOfLeds = 5) {
   // use 8..15 to make it easier to turn OFF the last LED after "overrun"
   if (NumOfLeds > ( MAX_LEDS - 1 ) ) {
      NumOfLeds = ( MAX_LEDS - 1 );
   }
   if(direction == left)
   {
      int i;
//      for (i=8 ; i<16; i++)
      for (i=FIRST_LED ; i<=FIRST_LED+NumOfLeds; i++) // no relays
      {
         digitalWrite(PIFACE + ((i-1)%8), LOW);
         digitalWrite(PIFACE + (i%8), HIGH);
         delay(Delay);
      }
      digitalWrite(PIFACE + ((i-1)%8), LOW);
   }
   else
   {
      int i;
//      for (i=15 ; i>7; i--)
      for (i=FIRST_LED+NumOfLeds ; i>=FIRST_LED; i--) // no relays
      {
         digitalWrite(PIFACE + ((i+1)%8), LOW);
         digitalWrite(PIFACE + (i%8), HIGH);
         delay(Delay);
      }
      digitalWrite(PIFACE + ((i+1)%8), LOW);
   }
}

/**
 * swipe a single LED
 * @param number of LED's to swipe
 */
void Swipe(int NumOfLeds = 5) {
   // use 8..15 to make it easier to turn OFF the last LED after "overrun"
   NumOfLeds--;
   if (NumOfLeds > ( MAX_LEDS - 2 ) ) {
      NumOfLeds = ( MAX_LEDS - 2 );
   }
   int i;
//      for (i=8 ; i<16; i++)
   for (i=FIRST_LED ; i<=FIRST_LED+NumOfLeds; i++) // no relays
   {
      digitalWrite(PIFACE + ((i-1)%8), LOW);
      digitalWrite(PIFACE + (i%8), HIGH);
      delay(Delay);
   }
   digitalWrite(PIFACE + ((i-1)%8), LOW);
//      for (i=15 ; i>7; i--)
   for (i=FIRST_LED + 1 +NumOfLeds ; i>=FIRST_LED + 1; i--) // no relays
   {
      digitalWrite(PIFACE + ((i+1)%8), LOW);
      digitalWrite(PIFACE + (i%8), HIGH);
      delay(Delay);
   }
   digitalWrite(PIFACE + ((i+1)%8), LOW);
}

/**
 * move 2 leds across
 */
void Inout(void) {
   // use 8..15 to make it easier to turn OFF the last LED after "overrun"
//      for (int i=8 ; i<16; i++)
   for (int i=10 ; i<16; i++) // no relays
   {
      digitalWrite(PIFACE + ((i-1)%8), LOW);
      digitalWrite(PIFACE + 8 - ((i-1)%8), LOW);
      digitalWrite(PIFACE + (i%8), HIGH);
      digitalWrite(PIFACE + 8 - (i%8), HIGH);
      delay(Delay);
   }
}

int main (int argc, char *argv [])
{
  printf ("Raspberry Pi PiFace Blink\n") ;
  printf ("=========================\n") ;

  // Declare the supported options.
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
      ("help", "produce help message")
      ("single", boost::program_options::value<int>(), "blink a single Led 0..7")
      ("rotate", boost::program_options::value<std::string >(), "rotate left or right")
      ("swipe","rotate left and right")
      ("inout",  "move in and out")
      ("random", "change randomly between modes")
      ("delay", boost::program_options::value<int>()->default_value(500), "delay between changes")
  ;

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
     std::cout << desc << "\n";
     return 1;
  }

  Delay = vm["delay"].as<int>();

  _WhatToDo WhatToDo = none;
  if (vm.count("rotate")) {
     std::cout << "Rotating Led.\n";
     if (WhatToDo == none){
        WhatToDo = rotate;
     }
     else
     {
        std::cout << "Only one option is allowed" << ".\n";
        std::cout << desc << "\n";
        return 1;
     }
  }
  if (vm.count("swipe")) {
     std::cout << "Rotating Led left and right.\n";
     if (WhatToDo == none){
        WhatToDo = swipe;
     }
     else
     {
        std::cout << "Only one option is allowed" << ".\n";
        std::cout << desc << "\n";
        return 1;
     }
  }
  if (vm.count("inout")) {
     std::cout << "Led is moving in and out.\n";
     if (WhatToDo == none){
        WhatToDo = inout;
     }
     else
     {
        std::cout << "Only one option is allowed" << ".\n";
        std::cout << desc << "\n";
        return 1;
     }
  }
  if (vm.count("random")) {
     std::cout << "Randomly change pattern.\n";
     Led = PIFACE + vm["single"].as<int>();
     if (WhatToDo == none){
        WhatToDo = randomly;
     }
     else
     {
        std::cout << "Only one option is allowed" << ".\n";
        std::cout << desc << "\n";
        return 1;
     }
  }
  if (vm.count("single")) {
     Led = PIFACE + vm["single"].as<int>();
     std::cout << "One Led is blinking - " << vm["single"].as<int>() << "/" << Led << ".\n";
     if (WhatToDo == none){
        WhatToDo = blink;
     }
     else
     {
        std::cout << "Only one option is allowed" << ".\n";
        std::cout << desc << "\n";
        return 1;
     }
  }
  if (WhatToDo == none){
     WhatToDo = blink;
     Led = PIFACE + 3;
  }
  // Always initialize wiringPi. Use wiringPiSys() if you don't need
//	(or want) to run as root

  if ( -1 == wiringPiSetupSys () )
  {
    printf ("wiringPiSetupSys has failed\n");
    exit(-1);
  }

// Setup the PiFace board

  printf ("piFaceSetup\n");
  piFaceSetup (PIFACE) ;

  if(WhatToDo == blink){
     for (;;)
     {
        Blink();
     }
  }

  if(WhatToDo == rotate){

     for (;;)
     {
        if (vm["rotate"].as<std::string>() == "left")
        {
           Rotate(left);
        }
        else
        {
           Rotate(right);
        }
     }
  }

  if(WhatToDo == swipe){

     for (;;)
     {
        Swipe();
     }
  }

  if(WhatToDo == inout){
     for (;;)
     {
        Inout();
     }
  }

  if(WhatToDo == randomly){
     for (;;)
     {
        _WhatToDo v = (_WhatToDo)(rand() % randomly);
        for (int i=0;i<10;i++)
        {
           switch(v){
           case blink:
              Blink();
              break;
           case rotate:
              Rotate(left);
              break;
           case swipe:
              Swipe();
              break;
           case inout:
              Inout();
              break;
           default:
              std::cout << "Wrong random number\n";
           }
        }
     }
  }

  return 0 ;
}
