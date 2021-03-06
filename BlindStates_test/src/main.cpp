/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/bind.hpp>
#include <algorithm>
#include <functional>

#include "BlindStates.h"

using namespace std;

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

class BlindStatesTest: public ::testing::Test {
   protected:
      BlindStatesTest(){
      }

      virtual void SetUp() {
         blindMachine.initiate();
      }

      BlindMachine blindMachine;
      std::string StateName;

      std::string strGetStateName(){
         BlindMachine::state_iterator itState = blindMachine.state_begin();
         std::string _StateName;
         _StateName  = typeid( *itState ).name();
         _StateName.erase(std::remove_if(_StateName.begin(), _StateName.end(), &::isdigit),
                         _StateName.end());
         std::cout << _StateName << "\n";
         return _StateName;
      }
};

TEST_F(BlindStatesTest, CheckDefaultState) {
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
   EXPECT_EQ(50, blindMachine.RunTimer());
}

// #######################
// BlindSomewhere
// #######################
TEST_F(BlindStatesTest, BlindSomewhere_UpPressed_BlindMovingUp) {
   blindMachine.process_event(EvUpPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingUp", StateName);
}

TEST_F(BlindStatesTest, BlindSomewhere_DownPressed_BlindMovingDown) {
   blindMachine.process_event(EvDownPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingDown", StateName);
}

TEST_F(BlindStatesTest, BlindSomewhere_Released_BlindSomewhere) {
   blindMachine.process_event(EvReleased());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

TEST_F(BlindStatesTest, BlindSomewhere_RunTimer_BlindSomewhere) {
   blindMachine.process_event(EvRunTimer());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

TEST_F(BlindStatesTest, BlindSomewhere_RunTimer_Timer50) {
   blindMachine.process_event(EvRunTimer());
   EXPECT_EQ(50, blindMachine.RunTimer());
}

TEST_F(BlindStatesTest, BlindSomewhere_FullTimerExpired_BlindSomewhere) {
   blindMachine.process_event(EvFullTimerExpired());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

// #######################
// BlindMovingUp
// #######################
TEST_F(BlindStatesTest, BlindMovingUp_Release_BlindSomewhere) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvReleased());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

TEST_F(BlindStatesTest, BlindMovingUp_DownPressed_BlindSomewhere) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvDownPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

TEST_F(BlindStatesTest, BlindMovingUp_UpPressed_BlindMovingUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvUpPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingUp", StateName);
}

TEST_F(BlindStatesTest, BlindMovingUp_FullTimerExpired_BlindUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvFullTimerExpired());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindUp", StateName);
}

TEST_F(BlindStatesTest, BlindMovingUp_RunTimer_BlindUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvRunTimer());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingUp", StateName);
}

TEST_F(BlindStatesTest, BlindMovingUp_RunTimer_Timer51) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvRunTimer());
   EXPECT_EQ(51, blindMachine.RunTimer());
}

TEST_F(BlindStatesTest, BlindMovingUp_RunTimer_Timer52) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvRunTimer());
   blindMachine.process_event(EvRunTimer());
   EXPECT_EQ(52, blindMachine.RunTimer());
}

// #######################
// BlindMovingDown
// #######################
TEST_F(BlindStatesTest, BlindMovingDown_Release_BlindSomewhere) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvReleased());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

TEST_F(BlindStatesTest, BlindMovingDown_UpPressed_BlindSomewhere) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvUpPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindSomewhere", StateName);
}

TEST_F(BlindStatesTest, BlindMovingDown_DownPressed_BlindMovingDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvDownPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingDown", StateName);
}

TEST_F(BlindStatesTest, BlindMovingDown_FullTimerExpired_BlindDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvFullTimerExpired());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindDown", StateName);
}

TEST_F(BlindStatesTest, BlindMovingDown_RunTimer_BlindMovingDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvRunTimer());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingDown", StateName);
}

TEST_F(BlindStatesTest, BlindMovingDown_RunTimer_Timer49) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvRunTimer());
   EXPECT_EQ(49, blindMachine.RunTimer());
}

TEST_F(BlindStatesTest, BlindMovingDown_RunTimer_Timer48) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvRunTimer());
   blindMachine.process_event(EvRunTimer());
   EXPECT_EQ(48, blindMachine.RunTimer());
}

// #######################
// BlindDown
// #######################
TEST_F(BlindStatesTest, BlindDown_Release_BlindDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvReleased());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindDown", StateName);
}

TEST_F(BlindStatesTest, BlindDown_UpPressed_BlindMovingUp) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvUpPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingUp", StateName);
}

TEST_F(BlindStatesTest, BlindDown_DownPressed_BlindMovingDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvDownPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingDown", StateName);
}

TEST_F(BlindStatesTest, BlindDown_FullTimerExpired_BlindDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvFullTimerExpired());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindDown", StateName);
}

TEST_F(BlindStatesTest, BlindDown_RunTimer_BlindDown) {
   blindMachine.process_event(EvDownPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvRunTimer());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindDown", StateName);
}

// #######################
// BlindUp
// #######################
TEST_F(BlindStatesTest, BlindUp_Release_BlindUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvReleased());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindUp", StateName);
}

TEST_F(BlindStatesTest, BlindUp_UpPressed_BlindMovingUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvUpPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingUp", StateName);
}

TEST_F(BlindStatesTest, BlindUp_DownPressed_BlindMovingDown) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvDownPressed());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindMovingDown", StateName);
}

TEST_F(BlindStatesTest, BlindUp_FullTimerExpired_BlindUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvFullTimerExpired());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindUp", StateName);
}

TEST_F(BlindStatesTest, BlindUp_RunTimer_BlindUp) {
   blindMachine.process_event(EvUpPressed());
   blindMachine.process_event(EvFullTimerExpired());
   blindMachine.process_event(EvRunTimer());
   StateName  = strGetStateName();
   EXPECT_EQ("BlindUp", StateName);
}
