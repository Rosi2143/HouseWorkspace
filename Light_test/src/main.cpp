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
#include "LightSwitchIn.h"

using namespace std;
using namespace boost::gregorian;

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

class LightTest: public ::testing::Test {
   protected:
      LightTest(): _room(0, "TestRoom", nullptr) {
      }

      virtual void SetUp() {
      }
      MockRoom _room;
};

TEST_F(LightTest, ConstructorNoRoom_State_Off) {
   LightSwitchIn LightSwitch(1, "Licht", nullptr);
   ASSERT_EQ(LightOff, LightSwitch.getState());
   ASSERT_EQ(1, LightSwitch.getId());
}

TEST_F(LightTest, CopyConstructorNoRoom_State_Off) {
   LightSwitchIn LightSwitch(1, "Licht", nullptr);
   LightSwitchIn LightSwitch2(LightSwitch);
   ASSERT_EQ(LightOff, LightSwitch2.getState());
}

TEST_F(LightTest, AssignmentNoRoom_State_Off) {
   LightSwitchIn LightSwitch(1, "Licht", nullptr);
   LightSwitchIn LightSwitch2(2, "---", nullptr);
   LightSwitch2 = LightSwitch;
   ASSERT_EQ(LightOff, LightSwitch2.getState());
   ASSERT_EQ(1, LightSwitch2.getId());
}

TEST_F(LightTest, Constructor_State_Off) {
   LightSwitchIn LightSwitch(1, "Licht", &_room);
   ASSERT_EQ(LightOff, LightSwitch.getState());
}

TEST_F(LightTest, ConstructorNoRoom_Name_Same) {
   LightSwitchIn LightSwitch(1, "Licht", nullptr);
   ASSERT_STRCASEEQ("Licht", LightSwitch.getName().c_str());
}

TEST_F(LightTest, CopyConstructorNoRoom_Name_Same) {
   LightSwitchIn LightSwitch(1, "Licht", nullptr);
   LightSwitchIn LightSwitch2(LightSwitch);
   ASSERT_STRCASEEQ("Licht", LightSwitch2.getName().c_str());
}

TEST_F(LightTest, AssignmentNoRoom_Name_Same) {
   LightSwitchIn LightSwitch(1, "Licht", nullptr);
   LightSwitchIn LightSwitch2(1, "----", nullptr);
   LightSwitch2 = LightSwitch;
   ASSERT_STRCASEEQ("Licht", LightSwitch2.getName().c_str());
}

TEST_F(LightTest, Constructor_Name_added) {
   LightSwitchIn LightSwitch(1, "Licht", &_room);
   ASSERT_STRCASEEQ("TestRoom_Licht", LightSwitch.getName().c_str());
}

TEST_F(LightTest, Constructor_Toggle_State_On) {
   LightSwitchIn LightSwitch(1, "Licht", &_room);
   LightSwitch.toggleState();
   ASSERT_EQ(LightOn, LightSwitch.getState());
}

TEST_F(LightTest, CopyConstructor_Toggle_State_On) {
   LightSwitchIn LightSwitch(1, "Licht", &_room);
   LightSwitch.toggleState();
   LightSwitchIn LightSwitch2(LightSwitch);
   ASSERT_EQ(LightOn, LightSwitch2.getState());
}

TEST_F(LightTest, Assignment_Toggle_State_On) {
   LightSwitchIn LightSwitch(1, "Licht", &_room);
   LightSwitchIn LightSwitch2(2, "Licht", &_room);
   LightSwitch.toggleState();
   LightSwitch2 = LightSwitch;
   ASSERT_EQ(LightOn, LightSwitch2.getState());
}

TEST_F(LightTest, Constructor_ToggleTwice_State_Off) {
   LightSwitchIn LightSwitch(1, "Licht", &_room);
   LightSwitch.toggleState();
   LightSwitch.toggleState();
   ASSERT_EQ(LightOff, LightSwitch.getState());
}

