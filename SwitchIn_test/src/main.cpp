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
            _room(0, "TestRoom", nullptr), _inputUser(0, "Test", nullptr), testString(
                  "Test"), testRoomString("TestRoom") {
      }

      virtual void SetUp() {
      }
      PressTime _pressTime;
      MockTime _time;
      MockRoom _room;
      MockInputUser _inputUser;
      std::string testString;
      std::string testRoomString;
};

TEST_F(SwitchInTest, Constructor_OK) {
   SwitchIn _switch(0, testString, nullptr, &_inputUser);
   ASSERT_EQ(_switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), _switch.getName().c_str());
   ASSERT_EQ(_switch.getRoom(), nullptr);
}

TEST_F(SwitchInTest, CopyConstructor_OK) {
   SwitchIn _switch(0, testString, nullptr, &_inputUser);
   SwitchIn __switch(_switch);
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), nullptr);
}

TEST_F(SwitchInTest, Assignment_OK) {
   SwitchIn _switch(0, testString, &_room, &_inputUser);
   SwitchIn __switch(1, "g", nullptr, &_inputUser);
   __switch = _switch;
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(testString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, ConstructorWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   SwitchIn _switch(0, testString, &_room, &_inputUser);
   ASSERT_EQ(_switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), _switch.getName().c_str());
   ASSERT_EQ(_switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, CopyConstructorWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   SwitchIn _switch(0, testString, &_room, &_inputUser);
   SwitchIn __switch(_switch);
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, AssignmentWithRoom_OK) {
   std::string ResultString("TestRoom_Test");
   SwitchIn _switch(0, testString, &_room, &_inputUser);
   SwitchIn __switch(1, "z", nullptr, &_inputUser);
   __switch = _switch;
   ASSERT_EQ(__switch.getId(), 0);
   ASSERT_STREQ(ResultString.c_str(), __switch.getName().c_str());
   ASSERT_EQ(__switch.getRoom(), &_room);
}

TEST_F(SwitchInTest, ShortPress_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
  _switch.OnRelease();
}

TEST_F(SwitchInTest, NoPressRelease_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, PressDoubleRelease_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, GetActionList_OK) {
   SwitchIn _switch(1, "z", nullptr, &_inputUser);
   EXPECT_EQ(0, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddOneActionOK) {
   SwitchIn _switch(1, "z", nullptr, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddTwoActionsOK) {
   SwitchIn _switch(1, "z", nullptr, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   _switch.addAction(LongPressed, sAf);
   EXPECT_EQ(2, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddAllActionsOK) {
   SwitchIn _switch(1, "z", nullptr, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   for (int i = 0; i < NumOfSwitchInStates; i++) {
      _switch.addAction((SwitchInState) i, sAf);
   }
   EXPECT_EQ(NumOfSwitchInStates, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, AddOneActionTwice_OK) {
   SwitchIn _switch(1, "z", nullptr, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   _switch.addAction(Pressed, sAf);
   EXPECT_EQ(1, _switch.getActionMap().size());
}

TEST_F(SwitchInTest, CheckActionPressedNoRoom_OK) {
   SwitchIn _switch(1, "z", nullptr, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   EXPECT_CALL(_inputUser, OnPress(_)).Times(0);
   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionPressed_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Pressed, sAf);
   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionPressed_NOK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnPress(_)).Times(0);
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   t_SwitchInActionFunction sAf = &iInputUser::OnPress;
   _switch.addAction(Released, sAf);

   _switch.OnPress();
}

TEST_F(SwitchInTest, CheckActionReleased_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnRelease;
   _switch.addAction(Released, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnRelease(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionReleased_NOK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnShortPress;
   _switch.addAction(ShortPressed, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_inputUser, OnRelease(_)).Times(0);
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnShortPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionShortPress_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnShortPress;
   _switch.addAction(ShortPressed, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnShortPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Short));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionLongPress_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnLongPress;
   _switch.addAction(LongPressed, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnLongPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Long));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionVeryLongPress_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnVeryLongPress;
   _switch.addAction(VeryLongPressed, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnVeryLongPress(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(VeryLong));
   _switch.OnRelease();
}

TEST_F(SwitchInTest, CheckActionBlocked_OK) {
   SwitchIn _switch(1, "z", &_room, &_inputUser);
   t_SwitchInActionFunction sAf = &iInputUser::OnBlocked;
   _switch.addAction(Jammed, sAf);
   EXPECT_CALL(_room, getTimeRef()).WillRepeatedly(Return(&_time));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()));
   _switch.OnPress();

   EXPECT_CALL(_inputUser, OnBlocked(_));
   EXPECT_CALL(_time, getCurrentTime()).WillOnce(Return(second_clock::local_time()+millisec(500)));
   EXPECT_CALL(_time, evalPressType(_)).WillOnce(Return(Blocked));
   _switch.OnRelease();
}
