/*
 * Floor.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include "iFloor.h"
#include <string>
#include <vector>
#include <iostream>

typedef std::vector<iRoom*> RoomsPtr;

class Floor : public iFloor
{
   public:
      // Constructors
      Floor(unsigned int Id, std::string _name);
      Floor( const Floor &_floor);  // copy constructor
      virtual ~Floor();

      // Operators
      Floor& operator=(const Floor& other);    // assignment operator

      // access functions
      virtual unsigned int getNumberOfSwitches() const;
      virtual unsigned int getNumberOfRooms() const;
      virtual const iRoom& getRoom(std::string name) const;
      virtual const iSwitchIn* getSwitch(std::string name) const;

      // construction functions
      virtual unsigned int addRoom(iRoom& room);

   protected:
      Floor(){std::cout << "Wrong default constructor for Floor";}
      RoomsPtr _RoomList;
};

#endif /* FLOOR_H_ */
