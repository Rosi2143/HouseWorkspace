/*
 * Switch.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef SWITCH_H
#define SWITCH_H

#include <string>
#include <list>
#include <map>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "iSwitch.h"
#include "iInputUser.h"

class iRoom;

class Switch: public iSwitch{
   public:
      // Constructors
      Switch(unsigned int Id, std::string Name, const iRoom* pRoom, iInputUser* pInputUser);
      Switch(const Switch &obj);          // copy constructor
      virtual ~Switch() {
      }

      // Operators
      virtual Switch& operator=(const Switch& other);    // assignment operator

      // Port interface functions
      virtual void OnPress();
      virtual void OnRelease();

      // access functions
      virtual SwitchState getState() const {
         return _State;
      }
      virtual const iRoom* getRoom() const {
         return _pRoom;
      }
      virtual const ActionFunctionMap getActionMap() const {
         return _switchActionMap;
      }

      // construction functions
      virtual void addAction(const SwitchState& state, t_SwitchActionFunction Function);
   protected:
      Switch() :
            iSwitch(0, ""), _State(Unknown), _pRoom(nullptr), _pInputUser(nullptr) {
         std::cout << "Wrong default constructor Switch";
      }
      SwitchState _State;
      const iRoom* _pRoom;
      iInputUser* _pInputUser;
      ActionFunctionMap _switchActionMap;

      boost::posix_time::ptime PressTime;
      boost::posix_time::ptime ReleaseTime;
      boost::posix_time::time_duration PressDuration;
};

#endif /* SWITCH_H */
