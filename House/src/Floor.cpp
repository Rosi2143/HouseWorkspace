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
      iFloor(_Floor._Id, _Floor._Name, _Floor._pFloor) {
   _RoomList = _Floor._RoomList;
}

Floor& Floor::operator=(Floor other) {
   if (&other == this) {
      return *this;
   }
   _RoomList = other._RoomList;
   return *this;
}


Floor::~Floor()
{
   _RoomList.erase();
}

/*!
 * get the number of rooms in this floor
 * @return mumber of rooms
 */
unsigned int Floor::getNumberOfRooms() const
{
   return _RoomList.size();
}

/*!
 * add a room to the floor
 * @param _pRoom: Pointer of the room to add. object will be copied
 */
void Floor::addRoom(iRoom* ptrRoom)
{
   _RoomList.push_back(ptrRoom);
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
