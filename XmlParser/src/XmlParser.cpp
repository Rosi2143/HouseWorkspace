/*
 * XmlParser.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */
#include "XmlParser.h"
#include <boost/foreach.hpp>
#include <boost/algorithm/string/predicate.hpp>

#define XML_NAME_TAG    "Name"
#define XML_VERSION_TAG "Version"
#define XML_HOUSE_TAG   "House"
#define XML_ROOMS_TAG   "Rooms"
#define XML_ROOM_TAG    "Room"
#define XML_FLOORS_TAG  "Floors"
#define XML_FLOOR_TAG   "Floor"
#define XML_LIGHT_TAG   "Light"
#define XML_BLIND_TAG   "Blind"
#define XML_HEATER_TAG  "Heater"
#define XML_SWITCH_TAG  "Switch"

House readxml(const std::string &filename) {
   // populate tree structure pt
   using boost::property_tree::ptree;
   ptree pt;
   Floor* pFloor = nullptr;
   Room*  pRoom  = nullptr;
   read_xml(filename, pt);

   // traverse pt
   House house;
   // loop through all floors
   BOOST_FOREACH( ptree::value_type const& xmlSubHouse, pt.get_child(XML_HOUSE_TAG) ) {
      if (boost::algorithm::iequals(xmlSubHouse.first, XML_NAME_TAG)) {
         house.Name = xmlSubHouse.second.data();
      }
      if (boost::algorithm::iequals(xmlSubHouse.first, XML_VERSION_TAG)) {
         house.Version = std::stoi(xmlSubHouse.second.data().c_str());
      }
      if (boost::algorithm::iequals(xmlSubHouse.first, XML_FLOORS_TAG)) {
         BOOST_FOREACH( ptree::value_type const& xmlSubFloor, xmlSubHouse.second.get_child(XML_FLOOR_TAG) ) {
            if (boost::algorithm::iequals(xmlSubFloor.first, XML_NAME_TAG)) {
               pFloor = new Floor;
               pFloor->Name = xmlSubFloor.second.data();
            }
            if(pFloor == nullptr)
            {
               throw "No pFloor pointer defined";
            }
            // loop through all rooms
            if (boost::algorithm::iequals(xmlSubFloor.first, XML_ROOMS_TAG)) {
               BOOST_FOREACH( ptree::value_type const& xmlSubRoom, xmlSubFloor.second.get_child(XML_ROOM_TAG) ) {
                  if (boost::algorithm::iequals(xmlSubRoom.first, XML_NAME_TAG)) {
                     pRoom = new Room;;
                     pRoom->Name = xmlSubRoom.second.data();
                  }
                  if(pRoom == nullptr)
                  {
                     throw "No pRoom pointer defined";
                  }
                  // loop through all items in room
                  if (boost::algorithm::iequals(xmlSubRoom.first, XML_LIGHT_TAG)) {
                     pRoom->Lights.push_back(std::stoi(xmlSubRoom.second.data()));
                  }
                  else if (boost::algorithm::iequals(xmlSubRoom.first, XML_HEATER_TAG)) {
                     pRoom->Heaters.push_back(std::stoi(xmlSubRoom.second.data()));
                  }
                  else if (boost::algorithm::iequals(xmlSubRoom.first, XML_BLIND_TAG)) {
                     pRoom->Blinds.push_back(std::stoi(xmlSubRoom.second.data()));
                  }
                  if (boost::algorithm::iequals(xmlSubRoom.first, XML_SWITCH_TAG)) {
                     Switch _Switch;
                     _Switch.switchId    = xmlSubRoom.second.get<unsigned int>("ID");
                     _Switch.shortAction     = xmlSubRoom.second.get_child("Short").get<std::string>("Action", "none");
                     _Switch.shortId         = xmlSubRoom.second.get_child("Short").get<unsigned int>("ID", 0);
                     _Switch.longAction      = xmlSubRoom.second.get_child("Long").get<std::string>("Action", "none");
                     _Switch.longId          = xmlSubRoom.second.get_child("Long").get<unsigned int>("ID", 0);
                     _Switch.extraLongAction = xmlSubRoom.second.get_child("ExtraLong").get<std::string>("Action", "none");
                     _Switch.extraLongId     = xmlSubRoom.second.get_child("ExtraLong").get<unsigned int>("ID", 0);
                     pRoom->Switches.push_back(_Switch);
                  }
               }
               pFloor->RoomList.push_back(*pRoom);
            }
         }
         house.FloorList.push_back(*pFloor);
         pFloor = nullptr;
      }
   }

   return house;
}
