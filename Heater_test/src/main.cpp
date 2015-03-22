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
#include "HeaterSwitchIn.h"

using namespace std;
using namespace boost::gregorian;

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

class HeaterTest: public ::testing::Test {
   protected:
      HeaterTest(): _room(0, "TestRoom", nullptr) {
      }

      virtual void SetUp() {
      }
      MockRoom _room;
};

TEST_F(HeaterTest, ConstructorNoRoom_State_Off) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", nullptr);
   ASSERT_EQ(HeaterOff, HeaterSwitch.getState());
   ASSERT_EQ(1, HeaterSwitch.getId());
}

TEST_F(HeaterTest, CopyConstructorNoRoom_State_Off) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", nullptr);
   HeaterSwitchIn HeaterSwitch2(HeaterSwitch);
   ASSERT_EQ(HeaterOff, HeaterSwitch2.getState());
}

TEST_F(HeaterTest, AssignmentNoRoom_State_Off) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", nullptr);
   HeaterSwitchIn HeaterSwitch2(2, "---", nullptr);
   HeaterSwitch2 = HeaterSwitch;
   ASSERT_EQ(HeaterOff, HeaterSwitch2.getState());
   ASSERT_EQ(1, HeaterSwitch2.getId());
}

TEST_F(HeaterTest, Constructor_State_Off) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", &_room);
   ASSERT_EQ(HeaterOff, HeaterSwitch.getState());
}

TEST_F(HeaterTest, ConstructorNoRoom_Name_Same) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", nullptr);
   ASSERT_STRCASEEQ("Licht", HeaterSwitch.getName().c_str());
}

TEST_F(HeaterTest, CopyConstructorNoRoom_Name_Same) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", nullptr);
   HeaterSwitchIn HeaterSwitch2(HeaterSwitch);
   ASSERT_STRCASEEQ("Licht", HeaterSwitch2.getName().c_str());
}

TEST_F(HeaterTest, AssignmentNoRoom_Name_Same) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", nullptr);
   HeaterSwitchIn HeaterSwitch2(1, "----", nullptr);
   HeaterSwitch2 = HeaterSwitch;
   ASSERT_STRCASEEQ("Licht", HeaterSwitch2.getName().c_str());
}

TEST_F(HeaterTest, Constructor_Name_added) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", &_room);
   ASSERT_STRCASEEQ("TestRoom_Licht", HeaterSwitch.getName().c_str());
}

TEST_F(HeaterTest, Constructor_Toggle_State_On) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", &_room);
   HeaterSwitch.toggleState();
   ASSERT_EQ(HeaterOn, HeaterSwitch.getState());
}

TEST_F(HeaterTest, CopyConstructor_Toggle_State_On) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", &_room);
   HeaterSwitch.toggleState();
   HeaterSwitchIn HeaterSwitch2(HeaterSwitch);
   ASSERT_EQ(HeaterOn, HeaterSwitch2.getState());
}

TEST_F(HeaterTest, Assignment_Toggle_State_On) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", &_room);
   HeaterSwitchIn HeaterSwitch2(2, "Licht", &_room);
   HeaterSwitch.toggleState();
   HeaterSwitch2 = HeaterSwitch;
   ASSERT_EQ(HeaterOn, HeaterSwitch2.getState());
}

TEST_F(HeaterTest, Constructor_ToggleTwice_State_Off) {
   HeaterSwitchIn HeaterSwitch(1, "Licht", &_room);
   HeaterSwitch.toggleState();
   HeaterSwitch.toggleState();
   ASSERT_EQ(HeaterOff, HeaterSwitch.getState());
}

