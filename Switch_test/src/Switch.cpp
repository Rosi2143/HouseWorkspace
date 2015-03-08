/*
 * Switch.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: micha
 */

#include <iostream>

#include "Switch.h"
#include "Time.h"
#include "iRoom.h"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;

Switch::Switch(unsigned int Id, std::string Name, iRoom* pRoom,
      iInputUser* pInputUser) :
      iSwitch(Id, Name, pRoom), _State(Unknown), _pInputUser(pInputUser) {
   if (pRoom != nullptr) {
      _Name = _pRoom->getName() + "_" + Name;
   }
   _switchActionMap.clear();
}

Switch::Switch(const Switch &Switch) :
      iSwitch(Switch._Id, Switch._Name, Switch._pRoom), _State(Switch._State), _pInputUser(
            Switch._pInputUser), _switchActionMap(Switch._switchActionMap), PressTime(
            pos_infin), ReleaseTime(pos_infin), PressDuration(seconds(0)) {

}

Switch& Switch::operator=(const Switch& other) {
   if (&other == this) {
      return *this;
   }
   iSwitch::operator =(other);
   _State = other._State;
   _switchActionMap = other._switchActionMap;
   _pRoom = other._pRoom;
   _pInputUser = other._pInputUser;
   return *this;
}

/*!
 * called from house construction to add actions to certain presses
 * @param state: state of switch where action is added to
 * @param _function: function pointer to actions
 */
void Switch::addAction(const SwitchState& state,
      t_SwitchActionFunction Function) {
   if (_switchActionMap.find(state) == _switchActionMap.end()) {
      _switchActionMap[state] = std::make_pair(_pInputUser, Function);
   } else {
      std::cout << "Action for " << state << " already defined." << std::endl;
   }
}

/*!
 * called from Input unit when a press of a button was detected. OnPress will be
 * called in registered User when the function is added.
 */
void Switch::OnPress() {
   if (_pRoom != nullptr) {
      const iTime* _time = _pRoom->getTimeRef();
      if (_time != nullptr) {
         PressTime = _time->getCurrentTime();
         std::string test = to_simple_string(PressTime);
         std::cout << "Press at: " << test << std::endl;
         ActionFunctionMap::const_iterator SwitchActionIterator =
               _switchActionMap.find(Pressed);
         if (SwitchActionIterator != _switchActionMap.end()) {
            SwitchAction sA = SwitchActionIterator->second;
            iInputUser* inputUser = std::get < 0 > (sA);
            t_SwitchActionFunction switchActionFunction = std::get < 1 > (sA);
            (inputUser->*switchActionFunction)(0);
         }
      }
   } else {
      std::cout << "No Room specified " << std::endl;
   }
}

/*!
 * called from Input unit when a release of a button was detected
 * On<XXX> Functions are called if added.
 */
void Switch::OnRelease() {
   if (_pRoom != nullptr) {
      const iTime* _time = _pRoom->getTimeRef();
      if (_time != nullptr) {
         ReleaseTime = _time->getCurrentTime();
         std::string test = to_simple_string(ReleaseTime);
         std::cout << "Release at: " << test << std::endl;
         if (ReleaseTime > PressTime) {
            PressDuration = ReleaseTime - PressTime;
            std::string test1 = to_simple_string(PressDuration);
            std::cout << "Duration is: " << test1 << std::endl;
            ActionFunctionMap::const_iterator SwitchActionIterator =
                  _switchActionMap.find(Released);
            if (SwitchActionIterator != _switchActionMap.end()) {
               SwitchAction sA = SwitchActionIterator->second;
               iInputUser* inputUser = std::get < 0 > (sA);
               t_SwitchActionFunction switchActionFunction = std::get < 1
                     > (sA);
               (inputUser->*switchActionFunction)(0);
            }

            PressType pressType = _time->evalPressType(PressDuration);
            switch (pressType) {
            case Short: {
               SwitchActionIterator = _switchActionMap.find(ShortPressed);
            }
               break;
            case Long: {
               SwitchActionIterator = _switchActionMap.find(LongPressed);
            }
               break;
            case VeryLong: {
               SwitchActionIterator = _switchActionMap.find(VeryLongPressed);
            }
               break;
            case Blocked: {
               SwitchActionIterator = _switchActionMap.find(Jammed);
            }
               break;
            default: {
               std::cout << "invalid TimeSpan" << std::endl;
               SwitchActionIterator = _switchActionMap.end();
            }
            }
            if (SwitchActionIterator != _switchActionMap.end()) {
               SwitchAction sA = SwitchActionIterator->second;
               iInputUser* inputUser = std::get < 0 > (sA);
               t_SwitchActionFunction switchActionFunction = std::get < 1
                     > (sA);
               (inputUser->*switchActionFunction)(0);
            }
            PressTime = pos_infin;
         } else {
            std::cout << "No Press detected" << std::endl;
         }
      }
   } else {
      std::cout << "No Room specified " << std::endl;
   }
}
