/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Timer.h"

using namespace std;
using namespace boost::gregorian;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

using namespace boost::posix_time;

int var;
void timer_handler(int) {
   var++;
}

class TimerTest: public ::testing::Test, public Timer {
   protected:
      TimerTest() {
      }

      virtual void SetUp() {
         var = 0;
      }
};

TEST_F(TimerTest, StartTimer_once_OK) {
   EXPECT_EQ(0,
         start_timer(1000 /*time in ms */, 1 /* TimerId */,
               &timer_handler /* HandlerFunction */));
}

TEST_F(TimerTest, AddTimer_once_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };

   EXPECT_EQ(0, add_timer(timerStruct));
   EXPECT_EQ(1, _TimerList.front()._TimerId);
   EXPECT_GE(getNextTimerDelay(), 990);
   EXPECT_LE(getNextTimerDelay(), 1000);

}

TEST_F(TimerTest, AddTimer_twoBefore_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(100);
   timerStruct = {t_now, 2, timer_handler};
   EXPECT_EQ(0, add_timer(timerStruct));
   EXPECT_EQ(2, _TimerList.front()._TimerId);
   EXPECT_GE(getNextTimerDelay(), 90);
   EXPECT_LE(getNextTimerDelay(), 100);
}

TEST_F(TimerTest, AddTimer_twoAfter_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(2000);
   timerStruct = {t_now, 2, timer_handler};
   EXPECT_EQ(1, add_timer(timerStruct));
   EXPECT_EQ(1, _TimerList.front()._TimerId);
   EXPECT_GE(getNextTimerDelay(), 990);
   EXPECT_LE(getNextTimerDelay(), 1000);
}

TEST_F(TimerTest, AddTimer_threeBefore_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(2000);
   timerStruct = {t_now, 2, timer_handler};
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(100);
   timerStruct = {t_now, 3, timer_handler};
   EXPECT_EQ(0, add_timer(timerStruct));
   EXPECT_EQ(3, _TimerList.front()._TimerId);
   EXPECT_GE(getNextTimerDelay(), 90);
   EXPECT_LE(getNextTimerDelay(), 100);
}

TEST_F(TimerTest, AddTimer_threeAfter_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(1500);
   timerStruct = {t_now, 2, timer_handler};
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(2000);
   timerStruct = {t_now, 3, timer_handler};
   EXPECT_EQ(2, add_timer(timerStruct));
   EXPECT_EQ(1, _TimerList.front()._TimerId);
   EXPECT_GE(getNextTimerDelay(), 990);
   EXPECT_LE(getNextTimerDelay(), 1000);
}

TEST_F(TimerTest, AddTimer_threeInbetween_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(2000);
   timerStruct = {t_now, 2, timer_handler};
   add_timer(timerStruct);

   t_now = microsec_clock::local_time() + boost::posix_time::milliseconds(1500);
   timerStruct = {t_now, 3, timer_handler};
   EXPECT_EQ(1, add_timer(timerStruct));
   EXPECT_EQ(1, _TimerList.front()._TimerId);
   EXPECT_GE(getNextTimerDelay(), 990);
   EXPECT_LE(getNextTimerDelay(), 1000);
}
