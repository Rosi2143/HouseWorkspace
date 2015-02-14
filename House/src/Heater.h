/*
 * Heater.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef HEATER_H
#define HEATER_H

#include <string>
#include <list>

enum HeaterState
{
   HeaterOn,
   HeaterOff
}HeaterState;

class Room;

class Heater {
public:
      Heater(unsigned int _Id, std::string _Name, const Room* _pRoom);
      ~Heater();

      // access functions
      std::string getName() const {return Name;}
      HeaterState  getState() const {return State;}
      HeaterState  toggleState();

      // construction functions
protected:
      HeaterState  State;
      std::string Name;
      unsigned int Id;
      Room*        pRoom;
};

#endif /* HEATER_H */