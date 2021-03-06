/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/bind.hpp>
#include <SwitchIn.h>
#include <functional>

#include "MockRoom.h"
#include "MockTime.h"
#include "MockInputUser.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

class SwitchInTest: public ::testing::Test {
   protected:
      SwitchInTest() :
            _room(0, "TestRoom", nullptr), _inputUser(1, "Test", nullptr), _inputUser2(
                  2, "Test2", nullptr), testString("Test"), testRoomString(
                  "TestRoom") {
         ResultString = testRoomString + "_" + testString;
      }

      virtual void SetUp() {
      }
      PressTime _pressTime;
      MockTime _time;
      MockRoom _room;
      MockInputUser _inputUser;
      MockInputUser _inputUser2;
      std::string testString;
      std::string testRoomString;
      std::string ResultString;
};

TEST_F(SwitchInTest, Constructor_OK) {
   SwitchIn _switch(0, testString, nullptr);
   ASSERT_EQ(_switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), _switch.getName().c_str());
   ASSERT_EQ(_switch.getRoom(), nullptr);
}

TEST_F(SwitchInTest, CopyConstructor_OK) {
   SwitchIn _switch(0, testString, nullptr);
   SwitchIn __switch(_switch);
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), nullptr);
}

TEST_F(SwitchInTest, Assignment_OK) {
   SwitchIn _switch(0, testString, &_room);
   SwitchIn __switch(1, "g", nullptr);
   __switch = _switch;
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, ConstructorWithRoom_OK) {
   SwitchIn _switch(0, testString, &_room);
   ASSERT_EQ(_switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), _switch.getName().c_str());
   ASSERT_EQ(_switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, CopyConstructorWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   SwitchIn _switch(0, testString, &_room);
   SwitchIn __switch(_switch);
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, AssignmentWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   SwitchIn _switch(0, testString, &_room);
   SwitchIn __switch(1, "z", nullptr);
   __switch = _switch;
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, ShortPress_OK) {
   SwitchIn _switch(1, "z", &_room);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, NoPressRelease_OK) {
   SwitchIn _switch(1, "z", &_room);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, PressDoubleRelease_OK) {
   SwitchIn _switch(1, "z", &_room);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, GetActionList_OK) {
   SwitchIn _switch(1, "z", nullptr);
   EXPECT_EQ(0, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddOneActionOK) {
   SwitchIn _switch(1, "z", nullptr);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddTwoActionsOK) {
   SwitchIn _switch(1, "z", nullptr);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   _switch.addAction(LongPressed, &_inputUser, sAf);
   EXPECT_EQ(2, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddAllActionsOK) {
   SwitchIn _switch(1, "z", nullptr);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   for (int i = 0; i < NumOfSwitchInStates; i++) {
      _switch.addAction((SwitchInState) i, &_inputUser, sAf);
   }
   EXPECT_EQ(NumOfSwitchInStates, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddOneActionTwice_OK) {
   SwitchIn _switch(1, "z", nullptr);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   _switch.addAction(Pressed, &_inputUser, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
   EXPECT_EQ(1, _switch.getActionMap().find(Pressed)->second.size());
}

TEST_F(SwitchInTest, AddMultipleActions_OK) {
   SwitchIn _switch(1, "z", nullptr);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   _switch.addAction(Pressed, &_inputUser2, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
   EXPECT_EQ(2, _switch.getActionMap().find(Pressed)->second.size());
}

TEST_F(SwitchInTest, CheckActionPressedNoRoom_OK) {
   SwitchIn _switch(1, "z", nullptr);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   EXPECT_CALL(_inputUser, OnPress(_)).Times(0);
   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionPressed_OK) {
   SwitchIn _switch(1, "z", &_room);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionPressedMultipleUsers_OK) {
   SwitchIn _switch(1, "z", &_room);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_));
   EXPECT_CALL(_inputUser2, OnPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, &_inputUser, sAf);
   _switch.addAction(Pressed, &_inputUser2, sAf);
   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionPressed_NOK) {
   SwitchIn _switch(1, "z", &_room);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_)).Times(0);
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Released, &_inputUser, sAf);

   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionReleased_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnRelease;
   _switch.addAction(Released, &_inputUser, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnRelease(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionReleasedMultipleUsers_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnRelease;
   _switch.addAction(Released, &_inputUser, sAf);
   _switch.addAction(Released, &_inputUser2, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnRelease(_));
   EXPECT_CALL(_inputUser2, OnRelease(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionReleased_NOK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnShortPress;
   _switch.addAction(ShortPressed, &_inputUser, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnRelease(_)).Times(0);
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnShortPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionShortPress_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnShortPress;
   _switch.addAction(ShortPressed, &_inputUser, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnShortPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionShortPressMultipleUsers_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnShortPress;
   _switch.addAction(ShortPressed, &_inputUser, sAf);
   _switch.addAction(ShortPressed, &_inputUser2, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnShortPress(_));
   EXPECT_CALL(_inputUser2, OnShortPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionLongPress_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnLongPress;
   _switch.addAction(LongPressed, &_inputUser, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnLongPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Long));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionLongPressMultipleUsers_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnLongPress;
   _switch.addAction(LongPressed, &_inputUser, sAf);
   _switch.addAction(LongPressed, &_inputUser2, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnLongPress(_));
   EXPECT_CALL(_inputUser2, OnLongPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Long));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionVeryLongPress_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnVeryLongPress;
   _switch.addAction(VeryLongPressed, &_inputUser, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnVeryLongPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(VeryLong));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionVeryLongPressMultipleUsers_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnVeryLongPress;
   _switch.addAction(VeryLongPressed, &_inputUser, sAf);
   _switch.addAction(VeryLongPressed, &_inputUser2, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnVeryLongPress(_));
   EXPECT_CALL(_inputUser2, OnVeryLongPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(VeryLong));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionBlocked_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnBlocked;
   _switch.addAction(Jammed, &_inputUser, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnBlocked(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Blocked));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionBlockedMultipleUsers_OK) {
   SwitchIn _switch(1, "z", &_room);
   t_SwitchInActionFunction sAf = &iInputUser::OnBlocked;
   _switch.addAction(Jammed, &_inputUser, sAf);
   _switch.addAction(Jammed, &_inputUser2, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnBlocked(_));
   EXPECT_CALL(_inputUser2, OnBlocked(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(
         Return(second_clock::local_time() + millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Blocked));
   _switch.OnRelease();
}
