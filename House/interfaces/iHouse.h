/*
 * iHouse.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#pragma once

#include "Base.h"

class iFloor;
class iRoom;
class iSwitch;

struct ptree {
      std::string data;     // data associated with the node
      std::list<std::pair<std::string, ptree> > children; // ordered list of named children
};


class iHouse: public Base {
public:
      iHouse();
      ~iHouse();
      virtual void readHouseXml(const std::string &filename) = 0;

      // access functions
      virtual unsigned int getVersion() const = 0;
      virtual std::string  getName() const = 0;

      // handling floors
      virtual unsigned int getNumberOfFloors() const = 0;
      virtual const iFloor& getFloor(std::string name) const = 0;

      // handling rooms
      virtual unsigned int getNumberOfRooms() const = 0;
      virtual const iRoom& getRoom(std::string name) const = 0;

      // handling Switches
      virtual unsigned int getNumberOfSwitches() const = 0;
      virtual const iSwitch& getSwitch(std::string name) const = 0;

      // construction functions
      virtual void addFloor(const iFloor& _Floor) = 0;
};

