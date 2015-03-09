/*
 * Blind.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef BLINDSWITCHIN_H
#define BLINDSWITCHIN_H

#include <iBlindSwitchIn.h>
#include <string>
#include <list>


class Blind : public iBlindSwitchIn{
public:
      Blind(unsigned int _Id, std::string _Name, iRoom* _pRoom);
      ~Blind();

      // Operators
      Blind& operator=(const Blind& other);    // assignment operator

      // access functions
      BlindSwitchInState  getState() const {return State;}
      BlindSwitchInState  moveUp();
      BlindSwitchInState  moveDown();

      // construction functions
protected:
      BlindSwitchInState  State;
};

#endif /* BLINDSWITCHIN_H */
