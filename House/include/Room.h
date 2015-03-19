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
#include <iostream>

#include "BlindSwitchIn.h"
#include "iRoom.h"
#include "Floor.h"
#include "HeaterSwitchIn.h"
#include "LightSwitchIn.h"
#include "SwitchIn.h"

class Room: public iRoom {
   public:
      // Constructors
      Room(unsigned int Id, std::string Name, const Floor* pFloor);
      Room(const Room &room);  // copy constructor
      virtual ~Room();

      // Operators
      Room& operator=(const Room& other);

      // access functions
//      virtual const Light& getLight(std::string Name) const;
//      virtual const Heater& getHeater(std::string Name) const;
//      virtual const Blind& getBlind(std::string Name) const;
      virtual const SwitchIn& getSwitchIn(std::string Name) const;

      virtual const iTime* getTimeRef() const;

      // construction functions
//      virtual void addLight(const Light& Light);
//      virtual void addHeater(const Heater& Heater);
//      virtual void addBlind(const Blind& Blind);
      virtual void addSwitchIn(const SwitchIn& SwitchIn);

   protected:
      Room() :
            iRoom(0, "", nullptr) {
         std::cout << "Wrong default constructor Room";
      }
//      std::vector<Light> _Lights;
//      std::vector<Heater> _Heaters;
//      std::vector<Blind> _Blinds;
      std::vector<SwitchIn> _Switches;
};

#endif /* ROOM_H */