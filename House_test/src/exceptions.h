/*
 * exceptions.h
 *
 *  Created on: Feb 7, 2015
 *      Author: micha
 */

#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

class NoFloorException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "No floor found";
  }
};

class NoRoomException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "No room found";
  }
};


#endif /* SRC_EXCEPTIONS_H_ */
