/*
 * iTime.h
 *
 *  Created on: Feb 17, 2015
 *      Author: micha
 */

#pragma once

#include "boost/date_time/posix_time/posix_time.hpp"

typedef struct PressTime {
      int ShortPressTimeMs;
      int LongPressTimeMs;
      int VeryLongPressTimeMs;
      int JammedPressTimeMs;
} PressTime;

typedef enum PressType {
   Short,
   Long,
   VeryLong,
   Blocked
} PressType;

class iTime {
   public:
      iTime(){};
      virtual ~iTime(){}
      virtual boost::posix_time::ptime getCurrentTime() const = 0;
      virtual PressType evalPressType(boost::posix_time::time_duration duration) const = 0;
};

