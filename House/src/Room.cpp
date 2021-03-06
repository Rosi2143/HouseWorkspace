/*
 * Room.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: micha
 */
#include "Room.h"

Room::Room(unsigned int Id, std::string Name, const Floor* pFloor) :
      iRoom(Id, Name, pFloor) {
   _Lights.clear();
   _Heaters.clear();
   _Blinds.clear();
   _Switches.clear();
}

Room::Room(const Room &_Room) :
      iRoom(_Room._Id, _Room._Name, _Room._pFloor) {
   _Lights   = _Room._Lights;
   _Heaters  = _Room._Heaters;
   _Blinds   = _Room._Blinds;
   _Switches = _Room._Switches;
}

Room& Room::operator=(Room other) {
   if (&other == this) {
      return *this;
   }
   _pFloor   = other._pFloor;
   _Lights   = other._Lights;
   _Heaters  = other._Heaters;
   _Blinds   = other._Blinds;
   _Switches = other._Switches;
   return *this;
}

void Room::addSwitchIn(const iSwitchIn& SwitchIn) {
   _Switches.push_back(SwitchIn);
}
