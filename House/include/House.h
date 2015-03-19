/*
 * House.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef HOUSE_H_
#define HOUSE_H_

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <list>
#include <exception>

#include "iHouse.h"

class Floor;

typedef boost::gregorian::date Date;
typedef std::vector<Floor*> FloorsPtr;


struct ptree {
      std::string data;     // data associated with the node
      std::list<std::pair<std::string, ptree> > children; // ordered list of named children
};


class House: public iHouse {
public:
      House();
      ~House();
      void readHouseXml(const std::string &filename);

      // Operators
      House& operator=(const House& other);    // assignment operator

      // access functions
      unsigned int getVersion() {return Version;}
      std::string  getName() const {return Name;}

      // handling floors
      unsigned int getNumberOfFloors() const;
      const Floor& getFloor(std::string name) const;

      // handling rooms
      unsigned int getNumberOfRooms() const;
      const Room& getRoom(std::string name) const;

      // handling Switches
      unsigned int getNumberOfSwitches() const;
      const Switch& getSwitch(unsigned int ID) const;

      // construction functions
      void addFloor(const Floor& _Floor);
protected:
      unsigned int Version;
      std::string Name;
      FloorsPtr FloorList;
};

#endif /* HOUSE_H_ */