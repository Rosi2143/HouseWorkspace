/*
 ***************************************************************************
 *
 * Author: Michael Rossner
 *
 * Copyright (C) 2015 Michael Rossner
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

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <list>

#pragma once

#include "iTimer.h"

struct TimerStruct {
      boost::posix_time::ptime _TimerTime;
      int _TimerId;
      TimerCallBack _TimerCallback;
};
bool operator==(const TimerStruct& struct1, const TimerStruct& struct2);
bool TimerStructCompare(const TimerStruct& _TimerStruct1,
      const TimerStruct& _TimerStruct2);

class Timer: public iTimer {
   public:
#ifdef UNITTEST
      Timer() {};
#else
      Timer(boost::asio::io_service& io_service, boost::mutex& mutex, int _verbose = 0) :
            io_service_(io_service), io_mutex(mutex), timer_(io_service), interval_(
                  0), verbose(_verbose) {
      }
#endif
      ~Timer() {
      }

      virtual int start_timer(int, int, TimerCallBack);
      virtual int start_timer(const boost::posix_time::ptime&, int, TimerCallBack);
      virtual void stop_timer(void);
      virtual int32_t getNextTimerDelay();

   protected:
      int add_timer(const TimerStruct&);
      void set_interval(const std::size_t& milliseconds);
      void initiate_timer();
      void handle_timer_event(const boost::system::error_code& error,
            int TimerId);

      struct sigaction new_handler, old_handler;

      std::list<TimerStruct> _TimerList;
      TimerCallBack timer_func_handler_pntr;

   private:
#ifndef UNITTEST
      boost::asio::io_service& io_service_;
      boost::mutex& io_mutex;
      boost::asio::deadline_timer timer_;
#endif
      std::size_t interval_;
      int verbose;
};

