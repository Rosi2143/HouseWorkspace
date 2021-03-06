/*
 * SwitchIn.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: micha
 */

#include <TimeAndDate.h>
#include <iostream>

#include "iRoom.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../include/SwitchIn.h"

using namespace boost::posix_time;

SwitchIn::SwitchIn(unsigned int Id, std::string Name, iRoom* pRoom) :
      iSwitchIn(Id, Name, pRoom), _State(Unknown), PressTime(
            pos_infin), ReleaseTime(pos_infin), PressDuration(seconds(0)) {
   if (pRoom != nullptr) {
      _Name = _pRoom->getName() + "_" + Name;
   }
   _switchActionMap.clear();
}

SwitchIn::SwitchIn(const SwitchIn &SwitchIn) :
      iSwitchIn(SwitchIn._Id, SwitchIn._Name, SwitchIn._pRoom), _State(
            SwitchIn._State), _switchActionMap(
            SwitchIn._switchActionMap), PressTime(pos_infin), ReleaseTime(
            pos_infin), PressDuration(seconds(0)) {

}

SwitchIn& SwitchIn::operator=(const SwitchIn& other) {
   if (&other == this) {
      return *this;
   }
   iSwitchIn::operator =(other);
   _State = other._State;
   _switchActionMap = other._switchActionMap;
   return *this;
}

/*!
 * called from house construction to add actions to certain presses
 * @param state: state of switch where action is added to
 * @param _function: function pointer to actions
 */
void SwitchIn::addAction(const SwitchInState& state, iInputUser* pInputUser,
      t_SwitchInActionFunction Function) {
   SwitchInAction switchInAction = std::make_pair(pInputUser, Function);
   if (_switchActionMap.find(state) == _switchActionMap.end()) {
      std::list<SwitchInAction> list;
      list.push_back(switchInAction);
      _switchActionMap[state] = list;
   } else {
      std::cout << "Action for " << state << " already defined." << std::endl;
      bool bFound = false;
      for (auto switchAction : _switchActionMap.find(state)->second) {
         iInputUser* inputUser = std::get < 0 > (switchAction);
         t_SwitchInActionFunction switchActionFunction = std::get < 1
               > (switchAction);
         if ( (pInputUser == inputUser) and (Function == switchActionFunction) )
         {
            bFound = true;
            continue;
         }
      }
      if (false == bFound) {
         _switchActionMap.find(state)->second.push_back(switchInAction);
      }
   }
}

/*!
 * called from Input unit when a press of a button was detected. OnPress will be
 * called in registered User when the function is added.
 */
void SwitchIn::OnPress() {
if (_pRoom != nullptr) {
   const iTime* _time = _pRoom->getTimeRef();
   if (_time != nullptr) {
      PressTime = _time->getCurrentTime();
      std::string test = to_simple_string(PressTime);
      std::cout << "Press at: " << test << std::endl;
      ActionFunctionMap::const_iterator SwitchInActionIterator =
            _switchActionMap.find(Pressed);
      if (SwitchInActionIterator != _switchActionMap.end()) {
         for (auto switchAction : SwitchInActionIterator->second) {
            iInputUser* inputUser = std::get < 0 > (switchAction);
            t_SwitchInActionFunction switchActionFunction = std::get < 1
                  > (switchAction);
            (inputUser->*switchActionFunction)(0);
         }
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
void SwitchIn::OnRelease() {
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
         ActionFunctionMap::const_iterator SwitchInActionIterator =
               _switchActionMap.find(Released);
         if (SwitchInActionIterator != _switchActionMap.end()) {
            for (auto switchAction : SwitchInActionIterator->second) {
               iInputUser* inputUser = std::get < 0 > (switchAction);
               t_SwitchInActionFunction switchActionFunction = std::get < 1
                     > (switchAction);
               (inputUser->*switchActionFunction)(0);
            }
         }

         PressType pressType = _time->evalPressType(PressDuration);
         switch (pressType) {
         case Short: {
            SwitchInActionIterator = _switchActionMap.find(ShortPressed);
         }
            break;
         case Long: {
            SwitchInActionIterator = _switchActionMap.find(LongPressed);
         }
            break;
         case VeryLong: {
            SwitchInActionIterator = _switchActionMap.find(VeryLongPressed);
         }
            break;
         case Blocked: {
            SwitchInActionIterator = _switchActionMap.find(Jammed);
         }
            break;
         default: {
            std::cout << "invalid TimeSpan" << std::endl;
            SwitchInActionIterator = _switchActionMap.end();
         }
         }
         if (SwitchInActionIterator != _switchActionMap.end()) {
            for (auto switchAction : SwitchInActionIterator->second) {
               iInputUser* inputUser = std::get < 0 > (switchAction);
               t_SwitchInActionFunction switchActionFunction = std::get < 1
                     > (switchAction);
               (inputUser->*switchActionFunction)(0);
            }
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
