/*
 * iBlindSwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IBLINDSWITCHIN_H
#define IBLINDSWITCHIN_H

#include <string>
#include <list>

#include "Base.h"

typedef enum BlindSwitchInState
{
   BlindUp,
   BlindMovingDown,
   BlindDown,
   BlindMovingUp,
   BlindSomeWhere
}BlindSwitchInState;

class iRoom;

class iBlindSwitchIn : public Base{
public:
      // Constructors
      iBlindSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom):Base(Id, Name, pRoom){};
      iBlindSwitchIn(const iBlindSwitchIn& light);  // copy constructor
      virtual ~iBlindSwitchIn();

      // Operators
      //virtual iBlindSwitchIn& operator=(const iBlindSwitchIn& other) = 0;

      // access functions
      virtual BlindSwitchInState  getState() const = 0;
      virtual BlindSwitchInState  moveUp() = 0;
      virtual BlindSwitchInState  moveDown() = 0;

      // construction functions
protected:
      iBlindSwitchIn(): Base(0, "", nullptr){
         std::cout << "Wrong default constructor iLight";
      }
};

#endif /* IBLINDSWITCHIN_H */