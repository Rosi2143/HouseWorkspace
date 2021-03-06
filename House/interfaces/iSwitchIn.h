/*
 * iSwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef ISWITCHIN_H
#define ISWITCHIN_H

#include <string>
#include <list>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include "Base.h"
#include "iInputUser.h"

typedef enum SwitchInState {
   Unknown,
   Released,
   Pressed,
   ShortPressed,
   LongPressed,
   VeryLongPressed,
   Jammed,
   NumOfSwitchInStates
} SwitchInState;

typedef void (iInputUser::*t_SwitchInActionFunction)(int);
typedef std::pair<iInputUser*, t_SwitchInActionFunction> SwitchInAction;
typedef std::list<SwitchInAction> SwitchInActionList;
typedef std::map<SwitchInState, SwitchInActionList> ActionFunctionMap;

class iRoom;

class IBaseSwitchIn {
   public:
      // Constructors
      IBaseSwitchIn() {
      }
      IBaseSwitchIn(const IBaseSwitchIn& baseSwitchIn);  // copy constructor
      virtual ~IBaseSwitchIn() {
      }

      // Operators
      //virtual IBaseSwitchIn& operator=(const IBaseSwitchIn& other)

      // Port interface functions
      virtual void OnPress() = 0;
      virtual void OnRelease() = 0;

      // access functions
      virtual SwitchInState getState() const = 0;
      virtual void addAction(const SwitchInState& state, iInputUser* pInputUser,
            t_SwitchInActionFunction Function) = 0;
};

class iSwitchIn: public IBaseSwitchIn, public Base {
   public:
      // Constructors
      iSwitchIn(unsigned int Id, std::string Name, iRoom* pRoom) :
            Base(Id, Name, pRoom) {
      }
      iSwitchIn(const iSwitchIn &obj);          // copy constructor
      virtual ~iSwitchIn() {
      }

      // Operators
      virtual iSwitchIn& operator=(const iSwitchIn& other) { // assignment operator
         Base::operator=(other);
         return *this;
      }

      // Port interface functions
      virtual void OnPress() = 0;
      virtual void OnRelease() = 0;

      // access functions
      virtual SwitchInState getState() const = 0;
      virtual const ActionFunctionMap getActionMap() const = 0;

      // construction functions
      virtual void addAction(const SwitchInState& state, iInputUser* pInputUser,
            t_SwitchInActionFunction Function) = 0;
   protected:
      iSwitchIn() :
            Base(0, "", nullptr) {
         std::cout << "Wrong default constructor iSwitchIn";
      }
};

#endif /* ISWITCHIN_H */
