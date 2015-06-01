/*
 * iTimer.h
 *
 *  Created on: Feb 17, 2015
 *      Author: micha
 */

#pragma once

#include <stdint.h>

typedef void (*TimerCallBack)(int);

class iTimer {
   public:
      iTimer(){};
      virtual ~iTimer(){}
      virtual int start_timer(int, int, TimerCallBack) = 0;
      virtual void stop_timer(void) = 0;
      virtual int32_t getNextTimerDelay() = 0;
};

