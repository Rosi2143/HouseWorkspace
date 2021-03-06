/*
 * House.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */
#include "House.h"
#include "Floor.h"
#include "Room.h"
#include "exceptions.h"
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

NoFloorException HouseNoFloorEx;
NoRoomException  HouseNoRoomEx;

/*****************************************************
 *****************************************************
 *  House
 *****************************************************
 ****************************************************/
/*!
 * house is a class that represents the complete house
 * it consists of floors
 */
House::House()
:Version(0),
 Name("")
{

}

House::~House()
{

}

/*!
 * read the configuration xml file and construct the house.
 * boost::property_tree is used to read the xml
 * @param filename: file that contains the xml description
 */
void House::readHouseXml(const std::string &filename)
{
   // populate tree structure pt
   using boost::property_tree::ptree;
   ptree pt;
   Floor* pFloor = nullptr;
   Room*  pRoom  = nullptr;
   read_xml(filename, pt);

   // traverse pt
   // loop through all floors
   BOOST_FOREACH( ptree::value_type const& xmlSubHouse, pt.get_child(XML_HOUSE_TAG) ) {
      if (boost::algorithm::iequals(xmlSubHouse.first, XML_NAME_TAG)) {
         Name = xmlSubHouse.second.data();
      }
      if (boost::algorithm::iequals(xmlSubHouse.first, XML_VERSION_TAG)) {
         Version = std::stoi(xmlSubHouse.second.data().c_str());
      }
      if (boost::algorithm::iequals(xmlSubHouse.first, XML_FLOORS_TAG)) {
         BOOST_FOREACH( ptree::value_type const& xmlSubFloors, xmlSubHouse.second.get_child("") ) {
            BOOST_FOREACH( ptree::value_type const& xmlSubFloor, xmlSubFloors.second.get_child("") ) {
               if (boost::algorithm::iequals(xmlSubFloor.first, XML_NAME_TAG)) {
                  pFloor = new Floor(xmlSubFloor.second.data());
               }
               if(pFloor == nullptr)
               {
                  throw "No pFloor pointer defined";
               }
               // loop through all rooms
               if (boost::algorithm::iequals(xmlSubFloor.first, XML_ROOMS_TAG)) {
                  BOOST_FOREACH( ptree::value_type const& xmlSubRooms, xmlSubFloor.second.get_child("") ) {
                     BOOST_FOREACH( ptree::value_type const& xmlSubRoom, xmlSubRooms.second.get_child("") ) {
                        if (boost::algorithm::iequals(xmlSubRoom.first, XML_NAME_TAG)) {
                           pRoom = new Room(0, xmlSubRoom.second.data(), pFloor);
                        }
                        if(pRoom == nullptr)
                        {
                           continue;
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
                     pFloor->addRoom(pRoom);
                  }
               }
            }
            addFloor(*pFloor);
            pFloor = nullptr;
         }
      }
   }
}

/*****************************************************
 * Floor handling
*****************************************************/
/*!
* @return
 */
/*!
 * get the number of floors in the house
 * @return number of floors
 */
unsigned int House::getNumberOfFloors() const
{
   return FloorList.size();
}

/*!
 * get the floor by its name
 * @param name
 * @return reference to the floor
 */

const Floor& House::getFloor(std::string name) const
{
   for (const Floor& floor: FloorList)
   {
      if(boost::algorithm::iequals(floor.getName(),name))
      {
         return floor;
      }
   }

   throw HouseNoFloorEx;
}

/*!
 * add a floor to the house
 * @param _Floor
 */
void House::addFloor(const Floor& _Floor)
{
   FloorList.push_back(_Floor);
}
/*****************************************************
 * Room handling
*****************************************************/
/*!
 * get the number of rooms in the house
 * loops through all floors
 * @return number of rooms
 */
unsigned int House::getNumberOfRooms() const
{
   unsigned int NumberOfRooms = 0;
   for (const Floor& floor: FloorList)
   {
      NumberOfRooms += floor.getNumberOfRooms();
   }
   return NumberOfRooms;
}

/*!
 * get the room by its name
 * @param name
 * @return const reference to the room
 */
const Room& House::getRoom(std::string name) const
{
   for (const Floor& floor: FloorList)
   {
      if(boost::algorithm::iequals(floor.getRoom(name).Name, name))
      {
         return floor.getRoom(name);
      }
   }

   throw HouseNoRoomEx;
}

