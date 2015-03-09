/*
 * Heater.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef HEATERSWITCHIN_H
#define HEATERSWITCHIN_H

#include <string>
#include <list>
#include <iostream>

#include "iHeaterSwitchIn.h"

class HeaterSwitchIn: public iHeaterSwitchIn {
public:
      // Constructors
      HeaterSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom);
      HeaterSwitchIn(const HeaterSwitchIn& heater);  // copy constructor
      virtual ~HeaterSwitchIn(){}

      // Operators
      HeaterSwitchIn& operator=(const HeaterSwitchIn& other);

      // access functions
      virtual HeaterSwitchInState  getState() const {return _State;}
      virtual HeaterSwitchInState  toggleState();

      // construction functions
protected:
      HeaterSwitchIn(): iHeaterSwitchIn(0, "", nullptr), _State(HeaterOff) {
         std::cout << "Wrong default constructor HeaterSwitchIn";
      }
      HeaterSwitchInState  _State;
};

#endif /* HEATERSWITCHIN_H */
