/*
 * Base.h
 *
 *  Created on: Feb 12, 2015
 *      Author: micha
 */

#pragma once

#define BASE_NO_ROOM nullptr

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
      virtual bool getBaseState() const {
         return _BaseState;
      }
      virtual unsigned int getId() const {
         return _Id;
      }
      virtual std::string getName() const {
         return _Name;
      }
      virtual iRoom* getRoom() const {
         return _pRoom;
      }

   protected:
      Base() :
            _Name(""), _Id(0), _BaseState(false), _pRoom(nullptr) {
         std::cout << "Wrong default constructor Base";
         printCallStack();
      }
      std::string _Name;
      unsigned int _Id;
      bool _BaseState;
      iRoom* _pRoom;

      void printCallStack(void)
      {
          int j, nptrs;
          #define SIZE 100
          void *buffer[SIZE];
          char **strings;

         nptrs = backtrace(buffer, SIZE);
          printf("backtrace() returned %d addresses\n", nptrs);

         /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
             would produce similar output to the following: */

         strings = backtrace_symbols(buffer, nptrs);
          if (strings == NULL) {
              perror("backtrace_symbols");
              exit(EXIT_FAILURE);
          }

         for (j = 0; j < nptrs; j++)
              printf("%s\n", strings[j]);

         free(strings);
      }
};
