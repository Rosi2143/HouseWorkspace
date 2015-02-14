/*
 * Blind.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef BLIND_H
#define BLIND_H

#include <string>
#include <list>

enum BlindState
{
   BlindUp,
   BlindMovingDown,
   BlindDown,
   BlindMovingUp,
   BlindSomeWhere
}BlindState;

class Room;

class Blind {
public:
      Blind(unsigned int _Id, std::string _Name, const Room* _pRoom);
      ~Blind();

      // access functions
      std::string getName() const {return Name;}
      BlindState  getState() const {return State;}
      BlindState  moveUp();
      BlindState  moveDown();

      // construction functions
protected:
      BlindState  State;
      std::string Name;
      unsigned int Id;
      Room*        pRoom;
};

#endif /* BLIND_H */