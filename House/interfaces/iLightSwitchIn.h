/*
 * iLightSwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef ILIGHTSWITCHIN_H_
#define ILIGHTSWITCHIN_H_

#include <string>
#include <list>
#include <iostream>

#include "Base.h"

typedef enum LightSwitchInState {
   LightOn, LightOff
} LightSwitchInState;

class iRoom;

class iLightSwitchIn: public Base {
   public:
      // Constructors
      iLightSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom) :
            Base(Id, Name, pRoom) {
      }
      ;
      iLightSwitchIn(const iLightSwitchIn& light) :
            Base(light) { // copy constructor
      }
      virtual ~iLightSwitchIn() {
      }

      // Operators
      virtual iLightSwitchIn& operator=(const iLightSwitchIn& other) { // assignment operator
         Base::operator=(other);
         return *this;
      }

      // access functions
      virtual LightSwitchInState getState() const = 0;
      virtual LightSwitchInState toggleState() = 0;

      // construction functions
   protected:
      iLightSwitchIn() :
            Base(0, "", nullptr) {
         std::cout << "Wrong default constructor iLightSwitchIn";
      }
};

#endif /* ILIGHTSWITCHIN_H_ */
