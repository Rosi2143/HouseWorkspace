/*
 * Floor.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include <string>
#include <list>

class Room;

typedef std::vector<Room*> RoomsPtr;

class Floor
{
   public:
      Floor(std::string _name);
      Floor( const Floor &_floor);  // copy constructor
      ~Floor();

      // access functions
      std::string  getName() const {return Name;}
      unsigned int getNumberOfRooms() const;
      const Room& getRoom(std::string name) const;

      // construction functions
      void addRoom(const Room& _Room);

   protected:
      Floor(){}
      std::string  Name;
      unsigned int Id;
      RoomsPtr RoomList;
};

#endif /* FLOOR_H_ */