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
#include "Base.h"

typedef enum SwitchState {
   Unknown, Released, Pressed, ShortPressed, LongPressed, VeryLongPressed, Jammed
} SwitchState;

typedef int (*t_SwitchActionFunction)(/*int,int*/);
typedef std::map<SwitchState, t_SwitchActionFunction> ActionFunctionMap;

class Room;

class ISwitch {
   public:
      ISwitch() {
      }
      virtual ~ISwitch() {
      }
      // Port interface functions
      virtual void OnPress()   = 0;
      virtual void OnRelease() = 0;

      // access functions
      virtual SwitchState getState() const = 0;
      virtual void addAction(const SwitchState& state,
                  t_SwitchActionFunction _function) = 0;
};

class Switch: public ISwitch
            , public Base{
   public:
      Switch(unsigned int _Id, std::string _Name, const Room* _pRoom);
      Switch( const Switch &obj);  // copy constructor
      virtual ~Switch();

      // Port interface functions
      virtual void OnPress();
      virtual void OnRelease();

      // access functions
      SwitchState getState() const {
         return State;
      }
      const Room* getRoom() const {
         return pRoom;
      }
      const ActionFunctionMap getActionMap() const {
         return switchActionMap;
      }

      // construction functions
      void addAction(const SwitchState& state,
            t_SwitchActionFunction _function);
   protected:
      SwitchState State;
      const Room* pRoom;
      ActionFunctionMap switchActionMap;
};

#endif /* SWITCH_H */