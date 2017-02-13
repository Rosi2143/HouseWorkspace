/*
 * Floor.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */
#include "Floor.h"
#include "Room.h"
#include "exceptions.h"

#include <boost/foreach.hpp>
#include <boost/algorithm/string/predicate.hpp>

NoFloorException FloorNoFloorEx;
NoRoomException  FloorNoRoomEx;

/*****************************************************
 *****************************************************
 *  Floor
 *****************************************************
 ****************************************************/
/*!
 * Floor represents a single floor with all its rooms
 * @param _name: Name of the floor
 */
Floor::Floor(unsigned int Id, std::string Name) :
      iFloor(Id, Name, BASE_NO_ROOM) {
   _RoomList.clear();
}

Floor::Floor(const Floor &_Floor) :
      iFloor(_Floor._Id, _Floor._Name) {
   _RoomList = _Floor._RoomList;
}

Floor& Floor::operator=(const Floor& other) {
   if (&other == this) {
      return *this;
   }
   _RoomList = other._RoomList;
   return *this;
}


Floor::~Floor()
{
   _RoomList.erase(_RoomList.begin(), _RoomList.end());
}

/*!
 * add another room to this floor - if it does not yet exist
 * @return number of rooms
 */
unsigned int Floor::addRoom(iRoom& room)
{
  _RoomList.push_back(&room);

  return _RoomList.size();
}

/*!
 * get the number of switches in this floor
 * @return number of switches
 */
unsigned int Floor::getNumberOfSwitches() const
{
   unsigned int NumberOfSwitches = 0;
   for (iRoom* ptrRoom: _RoomList)
   {
      NumberOfSwitches+=ptrRoom->getNumberOfSwitches();
   }
   return NumberOfSwitches;
}

/*!
 * get specific switch in this floor
 * @return reference to this switch
 */
const iSwitchIn* Floor::getSwitch(std::string name) const
{
   for (iRoom* ptrRoom: _RoomList)
   {
      if(ptrRoom->getSwitchIn(name) != nullptr)
      {
         return ptrRoom->getSwitchIn(name);
      }
   }

   return nullptr;
}
/*!
 * get the number of rooms in this floor
 * @return number of rooms
 */
unsigned int Floor::getNumberOfRooms() const
{
   return _RoomList.size();
}

const iRoom& Floor::getRoom(std::string name) const
{
   for (iRoom* ptrRoom: _RoomList)
   {
      if(boost::algorithm::iequals(ptrRoom->getName(), name))
      {
         return *ptrRoom;
      }
   }

   throw FloorNoRoomEx;
}
