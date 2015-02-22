/*
 * Time.h
 *
 *  Created on: Feb 17, 2015
 *      Author: micha
 */

#ifndef TIME_H_
#define TIME_H_

#include "boost/date_time/posix_time/posix_time.hpp"
#include "iTime.h"

typedef struct PressTime {
      int ShortPressTimeMs;
      int LongPressTimeMs;
      int VeryLongPressTimeMs;
      int JammedPressTimeMs;
} PressTime;

class Time: public iTime {
   public:
      Time(PressTime pressTime) :
            _PressTime(pressTime) {
      }
      ;
      virtual ~Time() {
      }
      virtual ptime getCurrentTime() const {
         return microsec_clock::local_time();
      }
      virtual PressType evalPressType(
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
   protected:
      PressTime _PressTime;
};

#endif /* TIME_H_ */
