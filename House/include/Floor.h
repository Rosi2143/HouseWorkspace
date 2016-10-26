/*
 * Floor.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include <string>
#include <vector>
#include <iostream>

class Room;

typedef std::vector<Room*> RoomsPtr;

class Floor
{
   public:
      // Constructors
      Floor(std::string _name);
      Floor( const Floor &_floor);  // copy constructor
      virtual ~Floor();

      // Operators
      Floor& operator=(const Floor& other);    // assignment operator

      // access functions
      virtual unsigned int getNumberOfRooms() const;
      virtual const Room& getRoom(std::string name) const;

      // construction functions
      virtual void addRoom(Room* ptrRoom);

   protected:
      Floor():_Name(""), _Id(0){std::cout << "Wrong default constructor";}
      std::string  _Name;
      unsigned int _Id;
      RoomsPtr _RoomList;
};

#endif /* FLOOR_H_ */
