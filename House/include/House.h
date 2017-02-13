/*
 * House.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#pragma once

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <list>
#include <exception>

#include "iHouse.h"

typedef boost::gregorian::date Date;
typedef std::vector<iFloor*> FloorsPtr;


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
      const iFloor& getFloor(std::string name) const;

      // handling rooms
      unsigned int getNumberOfRooms() const;
      const iRoom& getRoom(std::string name) const;

      // handling Switches
      unsigned int getNumberOfSwitches() const;
      const iSwitch& getSwitch(std::string name) const;

      // construction functions
      void addFloor(const iFloor& _Floor);
protected:
      unsigned int Version;
      std::string Name;
      FloorsPtr FloorList;
};

