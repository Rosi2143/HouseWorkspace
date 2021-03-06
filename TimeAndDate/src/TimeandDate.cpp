/*
 * TimeAndDate.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: micha
 */
#include "TimeAndDate.h"

PressType Time::evalPressType(
      boost::posix_time::time_duration duration) const {
   if (duration
         < boost::posix_time::milliseconds(_PressTime.ShortPressTimeMs)) {
      return Short;
   } else if (duration
         < boost::posix_time::milliseconds(_PressTime.LongPressTimeMs)) {
      return Long;
   } else if (duration
         < boost::posix_time::milliseconds(
               _PressTime.VeryLongPressTimeMs)) {
      return VeryLong;
   } else if (duration
         < boost::posix_time::milliseconds(_PressTime.JammedPressTimeMs)) {
      return Blocked;
   } else {
      return Blocked;
   }
}

