/*
 * Light.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <string>
#include <list>

enum LightState
{
   LightOn,
   LightOff
}LightState;

class Room;

class Light {
public:
      Light(unsigned int _Id, std::string _Name, const Room* _pRoom);
      ~Light();

      // access functions
      std::string getName() const {return Name;}
      LightState  getState() const {return State;}
      LightState  toggleState();

      // construction functions
protected:
      LightState   State;
      std::string  Name;
      unsigned int Id;
      Room*        pRoom;
};

#endif /* LIGHT_H_ */