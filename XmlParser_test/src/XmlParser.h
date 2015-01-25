/*
 * XmlParser.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef SRC_XMLPARSER_H_
#define SRC_XMLPARSER_H_

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <list>

typedef boost::gregorian::date Date;

struct ptree {
      std::string data;     // data associated with the node
      std::list<std::pair<std::string, ptree> > children; // ordered list of named children
};

struct Switch {
      unsigned int switchId;
      std::string shortAction;
      unsigned int shortId;
      std::string longAction;
      unsigned int longId;
      std::string extraLongAction;
      unsigned int extraLongId;
};

struct Room {
      std::string Name;
      std::vector<unsigned int> Lights;
      std::vector<unsigned int> Heaters;
      std::vector<unsigned int> Blinds;
      std::vector<Switch>       Switches;
};

typedef std::vector<Room> Rooms;

struct Floor {
      std::string Name;
      Rooms RoomList;
};

typedef std::vector<Floor> Floors;

struct House {
      unsigned int Version;
      std::string Name;
      Floors FloorList;
};

House readxml(const std::string &filename);

#endif /* SRC_XMLPARSER_H_ */