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
Floor::Floor(std::string _name)
:_Name(_name)
{

}

Floor::~Floor()
{

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
void Floor::addRoom(Room* ptrRoom)
{
   _RoomList.push_back(ptrRoom);
}

const Room& Floor::getRoom(std::string name) const
{
   for (Room* ptrRoom: _RoomList)
   {
      if(boost::algorithm::iequals(ptrRoom->getName(), name))
      {
         return *ptrRoom;
      }
   }

   throw FloorNoRoomEx;
}
