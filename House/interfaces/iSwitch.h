/*
 * iSwitch.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef ISWITCH_H
#define ISWITCH_H

#include <string>
#include <list>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include "Base.h"
#include "iInputUser.h"

typedef enum SwitchState {
   Unknown,
   Released,
   Pressed,
   ShortPressed,
   LongPressed,
   VeryLongPressed,
   Jammed,
   NumOfSwitchStates
} SwitchState;

typedef void (iInputUser::*t_SwitchActionFunction)(int);
typedef std::pair<iInputUser*, t_SwitchActionFunction> SwitchAction;
typedef std::map<SwitchState, SwitchAction> ActionFunctionMap;

class iRoom;

class IBaseSwitch {
   public:
      // Constructors
      IBaseSwitch() {
      }
      IBaseSwitch(const IBaseSwitch& baseSwitch);  // copy constructor
      virtual ~IBaseSwitch() {
      }

     // Operators
     //virtual IBaseSwitch& operator=(const IBaseSwitch& other)

      // Port interface functions
      virtual void OnPress() = 0;
      virtual void OnRelease() = 0;

      // access functions
      virtual SwitchState getState() const = 0;
      virtual void addAction(const SwitchState& state,
            t_SwitchActionFunction Function) = 0;
};

class iSwitch: public IBaseSwitch, public Base {
   public:
      // Constructors
      iSwitch(unsigned int Id, std::string Name) : Base(Id, Name){}
      iSwitch(const iSwitch &obj);          // copy constructor
      virtual ~iSwitch() {
      }

      // Operators
      virtual iSwitch& operator=(const iSwitch& other){    // assignment operator
         Base::operator=(other);
         return *this;
      }

      // Port interface functions
      virtual void OnPress() = 0;
      virtual void OnRelease() = 0;

      // access functions
      virtual SwitchState getState() const = 0;
      virtual const iRoom* getRoom() const = 0;
      virtual const ActionFunctionMap getActionMap() const = 0;

      // construction functions
      virtual void addAction(const SwitchState& state, t_SwitchActionFunction Function) = 0;
   protected:
      iSwitch() :
            Base(0, ""){
         std::cout << "Wrong default constructor iSwitch";
      }
};

#endif /* ISWITCH_H */
