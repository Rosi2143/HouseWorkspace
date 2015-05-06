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

#include "Timer.h"

using namespace boost::posix_time;

void timer_sig_handler(int);

bool operator==(const TimerStruct& struct1, const TimerStruct& struct2) {
   return ( (struct1._TimerCallback == struct2._TimerCallback)
         && (struct1._TimerId == struct2._TimerId)
         && (struct1._TimerTime == struct2._TimerTime)
          );
}

/*!
 *
 * @param mSec - timer delay in MilliSeconds
 * @param TimerId - ID of the timer, asssinged by client
 * @param timer_func_handler - pointer to the function handling the timer callback
 * @return 0 in case of success; 1 in case timer could not be started
 */
int Timer::start_timer(int mSec, int TimerId,  TimerCallBack timer_func_handler)
{

   ptime t_now(microsec_clock::local_time());
   ptime t_timer = t_now + boost::posix_time::milliseconds(mSec);
   TimerStruct timerStruct = {t_timer, TimerId, timer_func_handler};
   int pos = add_timer(timerStruct);
   if(pos == -1)
   {
      return 1;
   }

   int NextTimer = getNextTimerDelay();
   timer_func_handler_pntr = _TimerList.front()._TimerCallback;

   struct itimerval timervalue;
   timervalue.it_interval.tv_sec = NextTimer / 1000;
   timervalue.it_interval.tv_usec = (NextTimer % 1000) * 1000;
   timervalue.it_value.tv_sec = NextTimer / 1000;
   timervalue.it_value.tv_usec = (NextTimer % 1000) * 1000;
   if(set_timer(timervalue))
   {
     printf("\nsetitimer() error\n");
     return(1);
   }

   new_handler.sa_handler = &timer_sig_handler;
   new_handler.sa_flags = SA_NOMASK;
   if(sigaction(SIGALRM, &new_handler, &old_handler))
   {
     printf("\nsigaction() error\n");
     return(1);
   }

   return(0);
}

/*!
 *
 * @param _timervalue: Time structure containing the timer information
 * @return 0 in case of success; 1 in case timer could not be started
 */
int Timer::set_timer(const itimerval& _timervalue)
{
   /*
   printf("timervalue.it_interval.tv_sec = %i\n", (int)_timervalue.it_interval.tv_sec);
   printf("timervalue.it_interval.tv_usec = %i\n", (int)_timervalue.it_interval.tv_usec);
   printf("timervalue.it_value.tv_sec = %i\n", (int)_timervalue.it_value.tv_sec);
   printf("timervalue.it_value.tv_usec = %i\n", (int)_timervalue.it_value.tv_usec);
   */
   if(-1 == setitimer(ITIMER_REAL, &_timervalue, NULL))
   {
     printf("\nsetitimer() error: %s\n", strerror(errno));
     return(1);
   }
   return 0;
}

/*!
 *
 * @param arg
 */
void Timer::TimerCallBackFkt(int arg)
{

}

/*!
 * stop the running timer
 */
void Timer::stop_timer(void)
{
   struct itimerval timervalue;

  timervalue.it_interval.tv_sec = 0;
  timervalue.it_interval.tv_usec = 0;
  timervalue.it_value.tv_sec = 0;
  timervalue.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &timervalue, NULL);

  sigaction(SIGALRM, &old_handler, NULL);
}

bool TimerStructCompare(const TimerStruct& _TimerStruct1, const TimerStruct& _TimerStruct2)
{
   return (_TimerStruct1._TimerTime < _TimerStruct2._TimerTime);
}
/*!
 * @param _timerStruct: TimerStruct to be added to the sorted list
 * @return returns the 0-based position of the new entry in the sorted list
 *         -1 is returned in case of error
 */
int Timer::add_timer(const TimerStruct _timerStruct)
{
   _TimerList.push_back(_timerStruct);
   _TimerList.sort(TimerStructCompare);

   std::list<TimerStruct>::iterator findIter = std::find(_TimerList.begin(),
                                                         _TimerList.end(),
                                                         _timerStruct);
   int pos = 0;
   bool found = false;
   for(const TimerStruct& entry : _TimerList)
   {
      if (entry == _timerStruct)
      {
         found = true;
         break;
      }
      else
      {
         pos++;
      }
   }

   if(!found)
   {
      pos = -1;
   }
   return pos;
}

/*!
 * @return time in Milliseconds when the next timer runs out
 */
int32_t Timer::getNextTimerDelay()
{
   boost::posix_time::time_duration NextTimer = _TimerList.front()._TimerTime - microsec_clock::local_time();
   // printf("NextTimer.total_milliseconds = %i\n", (int)NextTimer.total_milliseconds());

   return NextTimer.total_milliseconds();

}

void timer_sig_handler(int arg)
{
   Timer::TimerCallBackFkt(arg);
}

