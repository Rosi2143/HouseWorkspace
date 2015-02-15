/*
 * iRoom.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IROOM_H
#define IROOM_H

#include <string>
#include <list>
#include <iostream>

#include "Base.h"

class iFloor;
class iLight;
class iHeater;
class iBlind;
class iSwitch;

class iRoom: public Base {
   public:
      // Constructors
      iRoom(unsigned int Id, std::string Name, const iFloor* pFloor);
      iRoom(const iRoom &iRoom);  // copy constructor
      virtual ~iRoom();

      // Operators
      iRoom& operator=(iRoom other);

      // access functions
      virtual const iLight& getLight(std::string Name) const;
      virtual const iHeater& getHeater(std::string Name) const;
      virtual const iBlind& getBlind(std::string Name) const;
      virtual const iSwitch& getSwitch(std::string Name) const;

      // construction functions
      virtual void addLight(const iLight& Light);
      virtual void addHeater(const iHeater& Heater);
      virtual void addBlind(const iBlind& Blind);
      virtual void addSwitch(const iSwitch& Switch);

   protected:
      iRoom() :
            Base(0, "") {
         std::cout << "Wrong default constructor iRoom";
      }
};

#endif /* IROOM_H */
