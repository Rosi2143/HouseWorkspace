/*
 * BlindSwitchIn.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: micha
 */

#include <iostream>

#include "BlindSwitchIn.h"
#include "Room.h"

/*!
 *
 * @param Id
 * @param Name
 * @param pRoom
 */
BlindSwitchIn::BlindSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom):
iBlindSwitchIn(Id, Name, pRoom), _State(BlindSomeWhere)
{
   if (_pRoom != nullptr) {
      _Name = _pRoom->getName() + "_" + Name;
   }
}

/*!
 * CopyConstructor
 * @param Blind
 */
BlindSwitchIn::BlindSwitchIn(const BlindSwitchIn& Blind) :
      iBlindSwitchIn(Blind), _State(Blind.getState()){
}

BlindSwitchIn& BlindSwitchIn::operator=(const BlindSwitchIn& other) {
   if (&other == this) {
      return *this;
   }
   Base::operator=(other);
   _State = other._State;
   return *this;
}

// ################
// up
// ################
/*!
 * Key for UP was pressed
 */
void BlindSwitchIn::OnPressUp(){
   switch (_State) {
   case BlindMovingDown:
      _State = BlindSomeWhere;
      moveStop();
      break;
   default:
      _State = BlindMovingUp;
      moveUp();
   }
}

/*!
 * Key for UP was released after ShortPressTime
 */
void BlindSwitchIn::OnShortPressUp(){
}

/*!
 * Key for UP was released after LongPressTime
 */
void BlindSwitchIn::OnLongPressUp(){
}

/*!
 * Key for UP was released after VeryLongPressTime
 */
void BlindSwitchIn::OnVeryLongPressUp(){
}

// ################
// down
// ################
/*!
 * Key for DOWN was pressed
 */
void BlindSwitchIn::OnPressDown(){
}

/*!
 * Key for DOWN was released after ShortPressTime
 */
void BlindSwitchIn::OnShortPressDown(){
}

/*!
 * Key for DOWN was released after LongPressTime
 */
void BlindSwitchIn::OnLongPressDown(){
}

/*!
 * Key for DOWN was released after VeryLongPressTime
 */
void BlindSwitchIn::OnVeryLongPressDown(){
}

// ################
// move
// ################
BlindSwitchInState  BlindSwitchIn::moveUp() {
   return _State;
}

BlindSwitchInState  BlindSwitchIn::moveDown() {
   return _State;
}
BlindSwitchInState  BlindSwitchIn::moveStop() {
   return _State;
}
