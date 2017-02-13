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
class iSwitchIn;
class iTime;

class iRoom: public Base {
   public:
      // Constructors
      iRoom(unsigned int Id, std::string Name, const iFloor* pFloor):Base(Id, Name, nullptr){}
      iRoom(const iRoom &iRoom){}  // copy constructor
      virtual ~iRoom(){}

      // Operators
      //iRoom& operator=(const iRoom& other);

      // access functions
      //      virtual const iBlind* getBlind(std::string Name) const = 0;
      //      virtual const iHeater* getHeater(std::string Name) const = 0;
      //      virtual const iLight* getLight(std::string Name) const = 0;
      virtual const iSwitchIn* getSwitchIn(std::string Name) const = 0;
      virtual unsigned int getNumberOfSwitches() const = 0;

      virtual const iTime* getTimeRef() const = 0;

      // construction functions
      //      virtual void addBlind(const iBlind& Blind) = 0;
      //      virtual void addHeater(const iHeater& Heater) = 0;
      //      virtual void addLight(const iLight& Light) = 0;
      virtual void addSwitchIn(const iSwitchIn& SwitchIn) = 0;

   protected:
      iRoom() :
            Base(0, "", nullptr) {
         std::cout << "Wrong default constructor iRoom";
         printCallStack();
      }
};

#endif /* IROOM_H */
