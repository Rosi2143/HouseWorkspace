/*
 ***************************************************************************
 *
 * Author: Teunis van Beelen
 *
 * Copyright (C) 2010, 2011, 2012 Teunis van Beelen
 *
 * teuniz@gmail.com
 *
 ***************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ***************************************************************************
 *
 * This version of GPL is at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
 *
 ***************************************************************************
 */

#include <stdio.h>

#include "boost/date_time/posix_time/posix_time.hpp"
#include <sys/time.h>
#include <signal.h>
#include <list>

#pragma once

#include "iTimer.h"

struct TimerStruct {
      boost::posix_time::ptime _TimerTime;
      int _TimerId;
      TimerCallBack _TimerCallback;

};
bool operator==(const TimerStruct& struct1, const TimerStruct& struct2);

class Timer: public iTimer {
   public:
      Timer() {
      }
      ~Timer() {
      }

      virtual int start_timer(int, int, TimerCallBack);
      virtual void stop_timer(void);
      virtual int32_t getNextTimerDelay();

      static void TimerCallBackFkt(int arg);
   protected:
      int set_timer(const itimerval&);
      int add_timer(const TimerStruct);

      struct sigaction new_handler, old_handler;

      std::list<TimerStruct> _TimerList;
      TimerCallBack timer_func_handler_pntr;

};

