/*
 ***************************************************************************
 *
 * Author: Michael Rossner
 *
 * Copyright (C) 2015 Michael Rossner
 *
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
#include <boost/thread.hpp>

using namespace boost::posix_time;

bool operator==(const TimerStruct& struct1, const TimerStruct& struct2) {
   return ((struct1._TimerCallback == struct2._TimerCallback)
         && (struct1._TimerId == struct2._TimerId)
         && (struct1._TimerTime == struct2._TimerTime));
}

/*!
 * add the timer to the list and start the timer with the lowest runtime
 * @param ptime - time when the timer should expire
 * @param TimerId - ID of the timer, assigned by client
 * @param timer_func_handler - pointer to the function handling the timer callback
 * @return 0 in case of success; 1 in case timer could not be started
 */
int Timer::start_timer(const ptime& time, int TimerId,
      TimerCallBack timer_func_handler) {
   ptime t_now = microsec_clock::local_time();
   if(time > t_now) {
      return start_timer((time - t_now).total_milliseconds(), TimerId, timer_func_handler);
   }
   else {
      return 1;
   }
}

/*!
 * add the timer to the list and start the timer with the lowest runtime
 * @param mSec - timer delay in MilliSeconds
 * @param TimerId - ID of the timer, assigned by client
 * @param timer_func_handler - pointer to the function handling the timer callback
 * @return 0 in case of success; 1 in case timer could not be started
 */
int Timer::start_timer(int mSec, int TimerId,
      TimerCallBack timer_func_handler) {

   if (verbose) {
      std::cout << "start_timer " << mSec << "ms ID=" << TimerId << std::endl;
   }

   ptime t_timer = microsec_clock::local_time()
         + boost::posix_time::milliseconds(mSec);
   TimerStruct timerStruct = { t_timer, TimerId, timer_func_handler };
   int pos = add_timer(timerStruct);
   if (pos == -1) {
      return 1;
   }

   if (verbose) {
      std::cout << "\tstart_timer pos = " << pos << std::endl;
   }

   if (pos == 0) {
      stop_timer();
      // start timer if this is the least value
      initiate_timer();
   }

   return 0;
}

/*!
 * start the timer with the lowest runtime
 */
void Timer::initiate_timer() {

   if (!_TimerList.empty()) {
      int NextTimerIntervall = getNextTimerDelay();
      set_interval(NextTimerIntervall);

      timer_func_handler_pntr = _TimerList.front()._TimerCallback;
      int TimerId = _TimerList.front()._TimerId;

      if (verbose) {
         std::cout << "TimerList size = " << _TimerList.size() << std::endl;
         std::cout << "new timer intervall = " << interval_ << "ms"
               << std::endl;
      }

      if (interval_) {
         timer_.expires_from_now(boost::posix_time::milliseconds(interval_));
         timer_.async_wait(
               boost::bind(&Timer::handle_timer_event, this,
                     boost::asio::placeholders::error, TimerId));
         if (verbose) {
            std::cout << "timer started for " << interval_ << "ms" << std::endl;
         }
         boost::shared_ptr<boost::thread> thread(
               new boost::thread(
                     boost::bind(&boost::asio::io_service::run, &io_service_)));
         //thread->join();
      } else {
         timer_func_handler_pntr(TimerId);
         stop_timer();
         _TimerList.pop_front();
         initiate_timer();
      }
   }
}

/*!
 *
 * @param milliseconds
 */
void Timer::set_interval(const std::size_t& milliseconds) {
   interval_ = milliseconds;
}
/*!
 * stop the running timer
 */
void Timer::stop_timer(void) {
   timer_.cancel();
}

/*!
 * sort function for the TimerList, sorts the timer according to the runtime
 * @param _TimerStruct1 first timer entry
 * @param _TimerStruct2 second timer entry
 * @return true if first is smaller than second - see sort function requirement for lists
 */
bool TimerStructCompare(const TimerStruct& _TimerStruct1,
      const TimerStruct& _TimerStruct2) {
   return (_TimerStruct1._TimerTime < _TimerStruct2._TimerTime);
}
/*!
 * add the new timer to the list, sort the list and return the index in the sorted list
 * @param _timerStruct: TimerStruct to be added to the sorted list
 * @return returns the 0-based position of the new entry in the sorted list
 *         -1 is returned in case of error
 */
int Timer::add_timer(const TimerStruct& _timerStruct) {
   _TimerList.push_back(_timerStruct);
   _TimerList.sort(TimerStructCompare);

   // find position of new timer in list
   std::list<TimerStruct>::iterator findIter = std::find(_TimerList.begin(),
         _TimerList.end(), _timerStruct);
   int pos = 0;
   bool found = false;
   for (const TimerStruct& entry : _TimerList) {
      if (entry == _timerStruct) {
         found = true;
         break;
      } else {
         pos++;
      }
   }

   if (!found) {
      pos = -1;
   }
   return pos;
}

/*!
 * @return time in Milliseconds when the next timer runs out
 */
int32_t Timer::getNextTimerDelay() {
   boost::posix_time::time_duration NextTimer = _TimerList.front()._TimerTime
         - microsec_clock::local_time();

   return NextTimer.total_milliseconds();

}

/*!
 *
 * @param error
 */
void Timer::handle_timer_event(const boost::system::error_code& error,
      int TimerId) {
   if (verbose) {
      std::cout << "handle_timer_event, Timerid = " << TimerId << std::endl;
   }
   switch (error.value()) {
   case boost::system::errc::success: {
      if (interval_) {
         timer_func_handler_pntr(TimerId);
         _TimerList.pop_front();
         initiate_timer();
      } else {

      }
   }
      break;

   case boost::system::errc::operation_canceled: {
      std::cout << "Timer " << TimerId << " cancelled" << std::endl;
   }
      break;

   default: {
      std::cout << "Assert unexpected case Timer = " << TimerId << " Error = "
            << error.value() << std::endl;
   }
      break;
   }
}

