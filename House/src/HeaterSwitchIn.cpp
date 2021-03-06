/*
 * HeaterSwitchIn.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: micha
 */

#include <iostream>

#include "../include/HeaterSwitchIn.h"
#include "Room.h"

/*!
 *
 * @param Id
 * @param Name
 * @param pRoom
 */
HeaterSwitchIn::HeaterSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom):
iHeaterSwitchIn(Id, Name, pRoom), _State(HeaterOff)
{
   if (_pRoom != nullptr) {
      _Name = _pRoom->getName() + "_" + Name;
   }
}

/*!
 * CopyConstructor
 * @param heater
 */
HeaterSwitchIn::HeaterSwitchIn(const HeaterSwitchIn& heater) :
      iHeaterSwitchIn(heater), _State(heater.getState()){
}

HeaterSwitchIn& HeaterSwitchIn::operator=(const HeaterSwitchIn& other) {
   if (&other == this) {
      return *this;
   }
   Base::operator=(other);
   _State = other._State;
   return *this;
}
/*!
 * toggle the state of the HeaterSwitch
 * @return
 */
HeaterSwitchInState HeaterSwitchIn::toggleState(){
   if(HeaterOff == _State) {
      _State = HeaterOn;
      _BaseState = true;
   }
   else {
      _State = HeaterOff;
      _BaseState = false;
   }
   return _State;
}

