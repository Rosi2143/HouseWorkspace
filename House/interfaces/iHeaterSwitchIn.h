/*
 * iHeaterSwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IHEATERSWITCHIN_H
#define IHEATERSWITCHIN_H

#include <string>
#include <list>
#include <iostream>

#include "Base.h"

typedef enum HeaterSwitchInState
{
   HeaterOn,
   HeaterOff
}HeaterSwitchInState;

class iRoom;

class iHeaterSwitchIn: public Base {
public:
      // Constructors
      iHeaterSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom):Base(Id, Name, pRoom){};
      iHeaterSwitchIn(const iHeaterSwitchIn& heater);  // copy constructor
      virtual ~iHeaterSwitchIn(){}

      // Operators
      virtual iHeaterSwitchIn& operator=(const iHeaterSwitchIn& other) = 0;

      // access functions
      virtual HeaterSwitchInState  getState() const = 0;
      virtual HeaterSwitchInState  toggleState() = 0;

      // construction functions
protected:
      iHeaterSwitchIn(): Base(0, "", nullptr){
         std::cout << "Wrong default constructor iHeaterSwitchIn";
      }
};

#endif /* IHEATERSWITCHIN_H */
