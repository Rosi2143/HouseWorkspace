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
};

TEST_F(BlindStatesTest, ConstructorNoRoom_State_Off) {
   ASSERT_EQ(1, 1);
   for (BlindMachine::state_iterator itState = blindMachine.state_begin();
         itState != blindMachine.state_end();
         ++itState){
      std::string StateName  = typeid( *itState ).name();
      std::cout << StateName << "\n";
   }
   blindMachine.process_event(EvUpPressed());
   for (BlindMachine::state_iterator itState = blindMachine.state_begin();
         itState != blindMachine.state_end();
         ++itState){
      std::string StateName  = typeid( *itState ).name();
      std::cout << StateName << "\n";
   }
   blindMachine.process_event(EvFullTimerExpired());
   for (BlindMachine::state_iterator itState = blindMachine.state_begin();
         itState != blindMachine.state_end();
         ++itState){
      std::string StateName  = typeid( *itState ).name();
      std::cout << StateName << "\n";
   }
}

