/*
 * iFloor.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IFLOOR_H
#define IFLOOR_H

#include "Base.h"

class iRoom;
class iSwitchIn;

class iFloor: public Base {
public:
      iFloor(unsigned int Id, std::string Name, iRoom* pRoom=nullptr):Base(Id, Name, pRoom){};
      iFloor(const iFloor& floor);  // copy constructor
      virtual ~iFloor(){}

      // access functions
      //virtual unsigned int getVersion() const = 0;

      virtual unsigned int getNumberOfRooms() const = 0;

      // handling Switches
      virtual unsigned int getNumberOfSwitches() const = 0;
      virtual const iSwitchIn* getSwitch(std::string name) const = 0;

      // construction functions
      virtual unsigned int addRoom(iRoom& room) = 0;
protected:
      iFloor(): Base(0, "", nullptr){
         std::cout << "Wrong default constructor iFloor";
      }
};

#endif /* IFLOOR_H */
