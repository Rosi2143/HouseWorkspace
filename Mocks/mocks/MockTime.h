/*
 * MockTime.h
 *
 *  Created on: Feb 17, 2015
 *      Author: micha
 */

#ifndef MOCKTIME_H_
#define MOCKTIME_H_

#include "iTime.h"
#include "gmock/gmock.h"

class MockTime : public iTime {
 public:
  MOCK_CONST_METHOD0(getCurrentTime,     boost::posix_time::ptime());
  MOCK_CONST_METHOD1(evalPressType,      PressType(boost::posix_time::time_duration duration));};

#endif /* MOCKTIME_H_ */
