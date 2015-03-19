/*
 * Base.h
 *
 *  Created on: Feb 12, 2015
 *      Author: micha
 */

#ifndef SRC_BASE_H_
#define SRC_BASE_H_

#include <iostream>

class iRoom;

class Base {
   public:
      // Constructors
      Base(unsigned int _Id, std::string _Name, iRoom* pRoom) :
            _Name(_Name), _Id(_Id), _BaseState(false), _pRoom(pRoom) {
      }
      Base(const Base &base) :  // copy constructor
            _Name(base.getName()), _Id(base.getId()),
                  _BaseState(base.getBaseState()), _pRoom(base.getRoom()) {
      }  // copy constructor
      virtual ~Base() {
      }

      // Operators
      Base& operator=(const Base& other) {
         _Name = other.getName();
         _Id = other.getId();
         _BaseState = other.getBaseState();
         _pRoom = other.getRoom();
         return *this;
      }

      // access functions
      virtual std::string getName() const {
         return _Name;
      }
      virtual unsigned int getId() const {
         return _Id;
      }
      virtual bool getBaseState() const {
         return _BaseState;
      }
      virtual iRoom* getRoom() const {
         return _pRoom;
      }

   protected:
      Base() :
            _Name(""), _Id(0), _BaseState(false), _pRoom(nullptr) {
         std::cout << "Wrong default constructor Base";
      }
      std::string _Name;
      unsigned int _Id;
      bool _BaseState;
      iRoom* _pRoom;
};

#endif /* SRC_BASE_H_ */