/*
 * LightSwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef LIGHTSWITCHIN_H_
#define LIGHTSWITCHIN_H_

#include <string>
#include <list>
#include <iostream>

#include "iLightSwitchIn.h"

class iRoom;

class LightSwitchIn: public iLightSwitchIn {
   public:
      // Constructors
      LightSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom);
      LightSwitchIn(const LightSwitchIn& light);  // copy constructor
      virtual ~LightSwitchIn() {
      }

      // Operators
      LightSwitchIn& operator=(const LightSwitchIn& other);

      // access functions
      LightSwitchInState getState() const {
         return _State;
      }
      LightSwitchInState toggleState();

      // construction functions
   protected:
      LightSwitchIn(): iLightSwitchIn(), _State(LightOff){
         std::cout << "Wrong default constructor LightSwitchIn";
      }
      LightSwitchInState _State;
};

#endif /* LIGHTSWITCHIN_H_ */
