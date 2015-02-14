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

class Light;
class Heater;
class Blind;
class Switch;
class Floor;

class Room
{
   public:
      Room(unsigned int _Id, std::string _Name, const Floor* _Floor);
      Room( const Room &_room);  // copy constructor
      ~Room();

      // access functions
      std::string   getName() const {return Name;}
      const Light&  getLight (std::string Name) const;
      const Heater& getHeater(std::string Name) const;
      const Blind&  getBlind (std::string Name) const;
      const Switch& getSwitch(std::string Name) const;

      // construction functions
      void addLight (const Light&  _Light);
      void addHeater(const Heater& _Heater);
      void addBlind (const Blind&  _Blind);
      void addSwitch(const Switch& _Switch);

   protected:
      Room(){}
      std::string Name;
      unsigned int Id;
      std::vector<Light&>  Lights;
      std::vector<Heater&> Heaters;
      std::vector<Blind&>  Blinds;
      std::vector<Switch&> Switches;
      Floor*               pFloor;
};

#endif /* ROOM_H */