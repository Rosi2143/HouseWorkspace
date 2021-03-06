/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <TimeAndDate.h>

using namespace std;
using namespace boost::gregorian;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

TEST(TimeTest, Presses_OK) {
   PressTime _pressTime;
   _pressTime.ShortPressTimeMs    = 500;
   _pressTime.LongPressTimeMs     = 1000;
   _pressTime.VeryLongPressTimeMs = 3000;
   _pressTime.JammedPressTimeMs   = 10000;
   Time _time(_pressTime);
   ASSERT_EQ(Short,    _time.evalPressType(boost::posix_time::milliseconds(0)));
   ASSERT_EQ(Short,    _time.evalPressType(boost::posix_time::milliseconds(10)));
   ASSERT_EQ(Short,    _time.evalPressType(boost::posix_time::milliseconds(499)));
   ASSERT_EQ(Long,     _time.evalPressType(boost::posix_time::milliseconds(500)));
   ASSERT_EQ(Long,     _time.evalPressType(boost::posix_time::milliseconds(999)));
   ASSERT_EQ(VeryLong, _time.evalPressType(boost::posix_time::milliseconds(1000)));
   ASSERT_EQ(VeryLong, _time.evalPressType(boost::posix_time::seconds(1)));
   ASSERT_EQ(VeryLong, _time.evalPressType(boost::posix_time::milliseconds(2999)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::milliseconds(3000)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::seconds(3)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::milliseconds(9999)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::milliseconds(10000)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::seconds(10)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::milliseconds(100000)));
   ASSERT_EQ(Blocked,          _time.evalPressType(boost::posix_time::seconds(100)));
}
