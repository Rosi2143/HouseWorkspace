/*
 * SwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef SWITCHIN_H
#define SWITCHIN_H

#include <string>
#include <list>
#include <map>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "iSwitchIn.h"
#include "iInputUser.h"

class iRoom;

class SwitchIn: public iSwitchIn {
   public:
      // Constructors
      SwitchIn(unsigned int Id, std::string Name, iRoom* pRoom);
      SwitchIn(const SwitchIn &obj);          // copy constructor
      virtual ~SwitchIn() {
      }

      // Operators
      virtual SwitchIn& operator=(const SwitchIn& other); // assignment operator

      // Port interface functions
      virtual void OnPress();
      virtual void OnRelease();

      // access functions
      virtual SwitchInState getState() const {
         return _State;
      }
      virtual const ActionFunctionMap getActionMap() const {
         return _switchActionMap;
      }

      // construction functions
      virtual void addAction(const SwitchInState& state, iInputUser* pInputUser,
            t_SwitchInActionFunction Function);
   protected:
      SwitchIn() :
            iSwitchIn(0, "", nullptr), _State(Unknown) {
         std::cout << "Wrong default constructor SwitchIn";
      }
      SwitchInState _State;
      ActionFunctionMap _switchActionMap;

      boost::posix_time::ptime PressTime;
      boost::posix_time::ptime ReleaseTime;
      boost::posix_time::time_duration PressDuration;
};

#endif /* SWITCH_H */
