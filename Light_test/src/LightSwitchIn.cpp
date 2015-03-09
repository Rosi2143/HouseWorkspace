/*
 * LightSwitchIn.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: micha
 */

#include <iostream>

#include "../include/LightSwitchIn.h"
#include "Room.h"

/*!
 *
 * @param Id
 * @param Name
 * @param pRoom
 */
LightSwitchIn::LightSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom):
iLightSwitchIn(Id, Name, pRoom), _State(LightOff)
{
   if (_pRoom != nullptr) {
      _Name = _pRoom->getName() + "_" + Name;
   }
}

/*!
 *
 * @param light
 */
LightSwitchIn::LightSwitchIn(const LightSwitchIn& light) :
      iLightSwitchIn(light), _State(light.getState()){
}

LightSwitchInState LightSwitchIn::toggleState(){
   if(LightOff == _State) {
      _State = LightOn;
      _BaseState = true;
   }
   else {
      _State = LightOff;
      _BaseState = false;
   }
   return _State;
}
