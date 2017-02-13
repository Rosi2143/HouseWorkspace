/*
 * Room.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

#include "iRoom.h"

class iBlindSwitchIn;
class iHeaterSwitchIn;
class iLightSwitchIn;

class iFloor;
class iSwitchIn;

class Room: public iRoom {
   public:
      // Constructors
      Room(unsigned int Id, std::string Name, const iFloor* pFloor);
      Room(const Room &room);  // copy constructor
      virtual ~Room();

      // Operators
      Room& operator=(const Room& other);

      // access functions
//      virtual const Light* getLight(std::string Name) const;
//      virtual const Heater* getHeater(std::string Name) const;
//      virtual const Blind* getBlind(std::string Name) const;
      virtual const iSwitchIn* getSwitchIn(std::string Name) const;

      virtual const iTime* getTimeRef() const;

      // construction functions
//      virtual void addLight(const Light& Light);
//      virtual void addHeater(const Heater& Heater);
//      virtual void addBlind(const Blind& Blind);
      virtual void addSwitchIn(const iSwitchIn& SwitchIn);

   protected:
      Room() :
            iRoom(0, "", nullptr) {
         std::cout << "Wrong default constructor Room";
      }
//      std::vector<iLight*> _Lights;
//      std::vector<iHeater*> _Heaters;
//      std::vector<iBlind*> _Blinds;
      std::vector<iSwitchIn*> _LightSwitches;
      std::vector<iSwitchIn*> _HeaterSwitches;
      std::vector<iSwitchIn*> _BlindSwitches;
};

#endif /* ROOM_H */
