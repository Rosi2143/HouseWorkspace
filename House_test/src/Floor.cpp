/*
 * Floor.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */
#include "Floor.h"
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
:Name(_name)
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
   return RoomList.size();
}

/*!
 * add a room to the floor
 * @param _pRoom: Pointer of the room to add. object will be copied
 */
void Floor::addRoom(const Room& _Room)
{
   RoomList.push_back(_Room);
}

const Room& Floor::getRoom(std::string name) const
{
   for (const Room& room: RoomList)
   {
      if(boost::algorithm::iequals(room.Name, name))
      {
         return room;
      }
   }

   throw FloorNoRoomEx;
}
