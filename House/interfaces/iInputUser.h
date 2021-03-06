/*
 * iInputUser.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IINPUTUSER_H_
#define IINPUTUSER_H_

#include <string>
#include <list>
#include <iostream>

#include "Base.h"

class iInputUser: public Base {
   public:
      // Constructors
      iInputUser(unsigned int Id, std::string Name, iRoom* pRoom):Base(Id, Name, pRoom){};
      iInputUser(const iInputUser& light);  // copy constructor
      virtual ~iInputUser() {}

      // Operators
      //virtual iInputUser& operator=(const iInputUser& other) = 0;

      // access functions
      virtual void OnPress(int time) = 0;
      virtual void OnRelease(int time) = 0;
      virtual void OnShortPress(int time) = 0;
      virtual void OnLongPress(int time) = 0;
      virtual void OnVeryLongPress(int time) = 0;
      virtual void OnBlocked(int time) = 0;

      // construction functions
   protected:
      iInputUser(): Base(0, "", nullptr){
         std::cout << "Wrong default constructor iInputUser";
      }
};

#endif /* IINPUTUSER_H_ */
