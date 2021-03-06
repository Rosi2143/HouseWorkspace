/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define UNITTEST

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
void timer_handler2(int) {
   var++;
}

class TimerTest: public ::testing::Test, public Timer {
   protected:
      TimerTest():Timer() {
      }

      virtual void SetUp() {
         var = 0;
      }
};

#if 0
TEST_F(TimerTest, StartTimer_once_OK) {
   EXPECT_EQ(0,
         start_timer(1000 /*time in ms */, 1 /* TimerId */,
               &timer_handler /* HandlerFunction */));
}
#endif

TEST_F(TimerTest, AddTimer_once_OK) {
   ptime t_now(
         microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };

   EXPECT_EQ(0, add_timer(timerStruct));
   EXPECT_EQ(1, _TimerList.front()._TimerId);
   EXPECT_EQ(1, _TimerList.size());
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
   EXPECT_EQ(2, _TimerList.size());
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
   EXPECT_EQ(2, _TimerList.size());
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
   EXPECT_EQ(3, _TimerList.size());
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
   EXPECT_EQ(3, _TimerList.size());
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
   EXPECT_EQ(3, _TimerList.size());
   EXPECT_GE(getNextTimerDelay(), 990);
   EXPECT_LE(getNextTimerDelay(), 1000);
}

TEST_F(TimerTest, TimerStructCompare_Smaller1) {
   ptime t_now1(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   ptime t_now2(microsec_clock::local_time() + boost::posix_time::milliseconds(2000));
   TimerStruct timerStruct1 = { t_now1, 1, timer_handler };
   TimerStruct timerStruct2 = { t_now2, 1, timer_handler };

   EXPECT_TRUE(TimerStructCompare(timerStruct1, timerStruct2));
}

TEST_F(TimerTest, TimerStructCompare_Bigger1) {
   ptime t_now1(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   ptime t_now2(microsec_clock::local_time() + boost::posix_time::milliseconds(2000));
   TimerStruct timerStruct1 = { t_now1, 1, timer_handler };
   TimerStruct timerStruct2 = { t_now2, 1, timer_handler };

   EXPECT_FALSE(TimerStructCompare(timerStruct2, timerStruct1));
}

TEST_F(TimerTest, TimerStructCompare_Same) {
   ptime t_now(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };

   EXPECT_FALSE(TimerStructCompare(timerStruct, timerStruct));
}

TEST_F(TimerTest, TimerStruct_Compare_Same) {
   ptime t_now(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct = { t_now, 1, timer_handler };

   EXPECT_EQ(timerStruct, timerStruct);
}

TEST_F(TimerTest, TimerStruct_Compare_DifferentTimes) {
   ptime t_now(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct1 = { t_now, 1, timer_handler };
   TimerStruct timerStruct2 = { t_now + boost::posix_time::milliseconds(1000), 1, timer_handler };

   EXPECT_FALSE(timerStruct1 == timerStruct2);
   EXPECT_FALSE(timerStruct2 == timerStruct1);
}

TEST_F(TimerTest, TimerStruct_Compare_DifferentId) {
   ptime t_now(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct1 = { t_now, 1, timer_handler };
   TimerStruct timerStruct2 = { t_now, 2, timer_handler };

   EXPECT_FALSE(timerStruct1 == timerStruct2);
   EXPECT_FALSE(timerStruct2 == timerStruct1);
}

TEST_F(TimerTest, TimerStruct_Compare_DifferentHandler) {
   ptime t_now(microsec_clock::local_time() + boost::posix_time::milliseconds(1000));
   TimerStruct timerStruct1 = { t_now, 1, timer_handler };
   TimerStruct timerStruct2 = { t_now, 1, timer_handler2};

   EXPECT_FALSE(timerStruct1 == timerStruct2);
   EXPECT_FALSE(timerStruct2 == timerStruct1);
}
