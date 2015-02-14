/*
 * Switch.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: micha
 */

#include "Switch.h"
#include "House.h"
#include "Room.h"

Switch::Switch(unsigned int _Id, std::string _Name, const Room* _pRoom) :
      Base(_Id, _Name), State(Unknown), pRoom(_pRoom) {
   if (pRoom != nullptr) {
      Name = _pRoom->getName() + Name;
   }
   switchActionMap.clear();
}

Switch::Switch(const Switch &_switch) :
      Base(_switch.getId(), _switch.getName()), State(_switch.getState()), pRoom(
            _switch.getRoom()), switchActionMap(_switch.getActionMap()) {

}