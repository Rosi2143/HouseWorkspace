/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/bind.hpp>
#include <functional>

#include "MockRoom.h"
#include "MockTime.h"
#include "MockInputUser.h"
#include "BlindSwitchIn.h"

using namespace std;
using namespace boost::gregorian;

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

class BlindTest: public ::testing::Test {
   protected:
      BlindTest(): _room(0, "TestRoom", nullptr), TestString("Jalousie"){
      }

      virtual void SetUp() {
      }
      MockRoom _room;
      std::string TestString;
};

TEST_F(BlindTest, ConstructorNoRoom_State_Off) {
   BlindSwitchIn BlindSwitch(1, TestString, nullptr);
   ASSERT_EQ(BlindSomeWhere, BlindSwitch.getState());
   ASSERT_EQ(1, BlindSwitch.getId());
}

TEST_F(BlindTest, CopyConstructorNoRoom_State_Off) {
   BlindSwitchIn BlindSwitch(1, TestString, nullptr);
   BlindSwitchIn BlindSwitch2(BlindSwitch);
   ASSERT_EQ(BlindSomeWhere, BlindSwitch2.getState());
}

TEST_F(BlindTest, AssignmentNoRoom_State_Off) {
   BlindSwitchIn BlindSwitch(1, TestString, nullptr);
   BlindSwitchIn BlindSwitch2(2, "---", nullptr);
   BlindSwitch2 = BlindSwitch;
   ASSERT_EQ(BlindSomeWhere, BlindSwitch2.getState());
   ASSERT_EQ(1, BlindSwitch2.getId());
}

TEST_F(BlindTest, Constructor_State_Off) {
   BlindSwitchIn BlindSwitch(1, TestString, &_room);
   ASSERT_EQ(BlindSomeWhere, BlindSwitch.getState());
}

TEST_F(BlindTest, ConstructorNoRoom_Name_Same) {
   BlindSwitchIn BlindSwitch(1, TestString, nullptr);
   ASSERT_STRCASEEQ(TestString.c_str(), BlindSwitch.getName().c_str());
}

TEST_F(BlindTest, CopyConstructorNoRoom_Name_Same) {
   BlindSwitchIn BlindSwitch(1, TestString, nullptr);
   BlindSwitchIn BlindSwitch2(BlindSwitch);
   ASSERT_STRCASEEQ(TestString.c_str(), BlindSwitch2.getName().c_str());
}

TEST_F(BlindTest, AssignmentNoRoom_Name_Same) {
   BlindSwitchIn BlindSwitch(1, TestString, nullptr);
   BlindSwitchIn BlindSwitch2(1, "----", nullptr);
   BlindSwitch2 = BlindSwitch;
   ASSERT_STRCASEEQ(TestString.c_str(), BlindSwitch2.getName().c_str());
}

TEST_F(BlindTest, Constructor_Name_added) {
   BlindSwitchIn BlindSwitch(1, TestString, &_room);
   ASSERT_STRCASEEQ("TestRoom_Jalousie", BlindSwitch.getName().c_str());
}

TEST_F(BlindTest, Constructor_PressUp_State_On) {
   BlindSwitchIn BlindSwitch(1, TestString, &_room);
   BlindSwitch.OnPressUp();
   ASSERT_EQ(BlindMovingUp, BlindSwitch.getState());
}

TEST_F(BlindTest, CopyConstructor_PressUp_State_On) {
   BlindSwitchIn BlindSwitch(1, TestString, &_room);
   BlindSwitch.OnPressUp();
   BlindSwitchIn BlindSwitch2(BlindSwitch);
   ASSERT_EQ(BlindMovingUp, BlindSwitch2.getState());
}

TEST_F(BlindTest, Assignment_PressUp_State_On) {
   BlindSwitchIn BlindSwitch(1, TestString, &_room);
   BlindSwitchIn BlindSwitch2(2, TestString, &_room);
   BlindSwitch.OnPressUp();
   BlindSwitch2 = BlindSwitch;
   ASSERT_EQ(BlindMovingUp, BlindSwitch2.getState());
}

TEST_F(BlindTest, Constructor_PressUpTwice_State_Off) {
   BlindSwitchIn BlindSwitch(1, TestString, &_room);
   BlindSwitch.OnPressUp();
   BlindSwitch.OnPressUp();
   ASSERT_EQ(BlindMovingUp, BlindSwitch.getState());
}

