/*
 * iHouse.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IHOUSE_H_
#define IHOUSE_H_

#include "Base.h"

class Floor;
class Room;
class Switch;

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
      virtual const Floor& getFloor(std::string name) const = 0;

      // handling rooms
      virtual unsigned int getNumberOfRooms() const = 0;
      virtual const Room& getRoom(std::string name) const = 0;

      // handling Switches
      virtual unsigned int getNumberOfSwitches() const = 0;
      virtual const Switch& getSwitch(unsigned int ID) const = 0;

      // construction functions
      virtual void addFloor(const Floor& _Floor) = 0;
};

#endif /* IHOUSE_H_ */
