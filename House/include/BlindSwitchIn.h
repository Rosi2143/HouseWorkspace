/*
 * BlindSwitchIn.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef BLINDSWITCHIN_H
#define BLINDSWITCHIN_H

#include <iBlindSwitchIn.h>
#include <string>
#include <list>


class BlindSwitchIn : public iBlindSwitchIn{
public:
      BlindSwitchIn(unsigned int _Id, std::string _Name, iRoom* _pRoom);
      BlindSwitchIn(const BlindSwitchIn& Blind);  // copy constructor
      ~BlindSwitchIn(){
      }

      // Operators
      BlindSwitchIn& operator=(const BlindSwitchIn& other);    // assignment operator

      // access functions
      BlindSwitchInState  getState() const {return _State;}
      // up
      virtual void  OnPressUp();
      virtual void  OnShortPressUp();
      virtual void  OnLongPressUp();
      virtual void  OnVeryLongPressUp();
      // down
      virtual void  OnPressDown();
      virtual void  OnShortPressDown();
      virtual void  OnLongPressDown();
      virtual void  OnVeryLongPressDown();

      // construction functions
protected:
      BlindSwitchInState  _State;

      BlindSwitchInState  moveUp();
      BlindSwitchInState  moveDown();
      BlindSwitchInState  moveStop();
};

#endif /* BLINDSWITCHIN_H */
