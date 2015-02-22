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
#include "Switch.h"

using namespace std;
using namespace boost::gregorian;

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

class SwitchTest: public ::testing::Test {
   protected:
      SwitchTest() :
            _room(0, "TestRoom", nullptr), _inputUser(0, "Test"), testString(
                  "Test"), testRoomString("TestRoom") {
      }

      virtual void SetUp() {
      }
      MockTime _time;
      MockRoom _room;
      MockInputUser _inputUser;
      std::string testString;
      std::string testRoomString;
};

TEST_F(SwitchTest, Constructor_OK) {
   Switch _switch(0, testString, nullptr, &_inputUser);
   ASSERT_EQ(_switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), _switch.getName().c_str());
   ASSERT_EQ(_switch.getRoom(), nullptr);
}

TEST_F(SwitchTest, CopyConstructor_OK) {
   Switch _switch(0, testString, nullptr, &_inputUser);
   Switch __switch(_switch);
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), nullptr);
}

TEST_F(SwitchTest, Assignment_OK) {
   Switch _switch(0, testString, nullptr, &_inputUser);
   Switch __switch(1, "g", nullptr, &_inputUser);
   __switch = _switch;
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), nullptr);
}

TEST_F(SwitchTest, ConstructorWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   Switch _switch(0, testString, &_room, &_inputUser);
   ASSERT_EQ(_switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), _switch.getName().c_str());
   ASSERT_EQ(_switch.getRoom(), &_room);
}

TEST_F(SwitchTest, CopyConstructorWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   Switch _switch(0, testString, &_room, &_inputUser);
   Switch __switch(_switch);
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchTest, AssignmentWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   Switch _switch(0, testString, &_room, &_inputUser);
   Switch __switch(1, "z", nullptr, &_inputUser);
   __switch = _switch;
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchTest, ShortPress_OK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchTest, NoPressRelease_OK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchTest, PressDoubleRelease_OK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchTest, GetActionList_OK) {
   Switch _switch(1, "z", nullptr, &_inputUser);
   EXPECT_EQ(0, _switch.getActionMap().size());
}

TEST_F(SwitchTest, AddOneActionOK) {
   Switch _switch(1, "z", nullptr, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
}

TEST_F(SwitchTest, AddTwoActionsOK) {
   Switch _switch(1, "z", nullptr, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   _switch.addAction(LongPressed, sAf);
   EXPECT_EQ(2, _switch.getActionMap().size());
}

TEST_F(SwitchTest, AddAllActionsOK) {
   Switch _switch(1, "z", nullptr, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   for (int i = 0; i < NumOfSwitchStates; i++) {
      _switch.addAction((SwitchState) i, sAf);
   }
   EXPECT_EQ(NumOfSwitchStates, _switch.getActionMap().size());
}

TEST_F(SwitchTest, AddOneActionTwice_OK) {
   Switch _switch(1, "z", nullptr, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   _switch.addAction(Pressed, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
}

TEST_F(SwitchTest, CheckActionPressedNoRoom_OK) {
   Switch _switch(1, "z", nullptr, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   EXPECT_CALL(_inputUser, OnPress(_)).Times(0);
   _switch.OnPress();
}

TEST_F(SwitchTest, CheckActionPressed_OK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   _switch.OnPress();
}

TEST_F(SwitchTest, CheckActionPressed_NOK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_)).Times(0);
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   t_SwitchActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Released, sAf);

   _switch.OnPress();
}

TEST_F(SwitchTest, CheckActionReleased_OK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnRelease;
   _switch.addAction(Released, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnRelease(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchTest, CheckActionReleased_NOK) {
   Switch _switch(1, "z", &_room, &_inputUser);
   t_SwitchActionFunction sAf = &iInputUser::OnRelease;
   _switch.addAction(ShortPressed, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnRelease(_)).Times(0);
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}
