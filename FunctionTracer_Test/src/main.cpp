/*
 * main.cpp
 *
 *  Created on: Apr 10, 2016
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FunctionTracer.h"
using namespace std;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

TEST(House, TraceLevel0_inactive) {
   FUNCTION_TRACE
   ASSERT_EQ(NULL, p0.get());
}

TEST(House, TraceLevel1_active) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   ASSERT_TRUE(NULL != p0.get());
}

TEST(House, TraceLevel1_Up_Counter1) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   ASSERT_EQ(1, FunctionTraceCounter.get(getpid()));
}

TEST(House, TraceLevel1_secondIsInactive) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   FUNCTION_TRACE_TEST(2)
   ASSERT_TRUE(NULL != p0.get());
   ASSERT_TRUE(NULL == p2.get());
}

TEST(House, TraceLevel1_UpUp_Counter1) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   FUNCTION_TRACE_TEST(2)
   ASSERT_EQ(2, FunctionTraceCounter.get(getpid()));
   ASSERT_EQ(2, CounterValue2);
}

TEST(House, TraceLevel2_UpUp_Counter2) {
   SetTraceLevel(2);
   FUNCTION_TRACE
   FUNCTION_TRACE_TEST(2)
   ASSERT_EQ(2, FunctionTraceCounter.get(getpid()));
}

TEST(House, TraceLevel1_UpDown_Counter0) {
   SetTraceLevel(1);
   {
      FUNCTION_TRACE
   }
   ASSERT_TRUE(0 == FunctionTraceCounter.get(getpid()));
}

TEST(House, TraceLevel1_TwoParallelCalls_TwoOutputs) {
   SetTraceLevel(1);
   {
      FUNCTION_TRACE_TEST(1)
      ASSERT_TRUE(p1.get() != nullptr);
   }
   {
      FUNCTION_TRACE_TEST(2)
      ASSERT_TRUE(p2.get() != nullptr);
   }
   ASSERT_TRUE(0 == FunctionTraceCounter.get(getpid()));
}

TEST(House, TraceLevel1_TwoTwoParallelCalls_TwoOutputs) {
   SetTraceLevel(1);
   {
      FUNCTION_TRACE_TEST(1)
      ASSERT_TRUE(p1.get() != nullptr);
      {
         FUNCTION_TRACE_TEST(2)
         ASSERT_TRUE(p2.get() == nullptr);
      }
   }
   {
      FUNCTION_TRACE_TEST(1)
      ASSERT_TRUE(p1.get() != nullptr);
      {
         FUNCTION_TRACE_TEST(2)
         ASSERT_TRUE(p2.get() == nullptr);
      }
   }
   ASSERT_TRUE(0 == FunctionTraceCounter.get(getpid()));
}

TEST(House, TraceLevel2_TwoTwoParallelCalls_FourOutputs) {
   SetTraceLevel(2);
   {
      FUNCTION_TRACE_TEST(1)
      ASSERT_TRUE(p1.get() != nullptr);
      {
         FUNCTION_TRACE_TEST(2)
         ASSERT_TRUE(p2.get() != nullptr);
      }
   }
   {
      FUNCTION_TRACE_TEST(1)
      ASSERT_TRUE(p1.get() != nullptr);
      {
         FUNCTION_TRACE_TEST(2)
         ASSERT_TRUE(p2.get() != nullptr);
      }
   }
   ASSERT_TRUE(0 == FunctionTraceCounter.get(getpid()));
}

TEST(House, TraceLevel2_TwoTwoParallelCalls_ThreeOutputs) {
   SetTraceLevel(2);
   {
      FUNCTION_TRACE_TEST(1)
      ASSERT_TRUE(p1.get() != nullptr);
      {
         FUNCTION_TRACE_TEST(2)
         ASSERT_TRUE(p2.get() != nullptr);
      }
      {
         FUNCTION_TRACE_TEST(2)
         ASSERT_TRUE(p2.get() != nullptr);
      }
   }
}

TEST(House, TraceLevel1_SmallDelay_ClockTimeSmall) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   usleep(5050);
   p0->Destructor();
   ASSERT_LE(p0->_Cpu_Time_Used_ms, 1);
   ASSERT_GE(p0->_Clock_Time_Used_ms, 5);
}

TEST(House, TraceLevel1_LargeDelay_ClockTimeLarge) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   usleep(5000000);
   p0->Destructor();
   ASSERT_LE(p0->_Cpu_Time_Used_ms, 1);
   ASSERT_GE(p0->_Clock_Time_Used_ms, 5000);
}

TEST(House, TraceLevel1_SmallCpuConsumption_CpuTimeSmall) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   int i;
   for(i = 0; i<(1000*1000*10); i++) {int u = i*i; u=u;}
   p0->Destructor();
   ASSERT_GE(p0->_Cpu_Time_Used_ms, 10);
   ASSERT_GE(p0->_Clock_Time_Used_ms, 10);
}

TEST(House, TraceLevel1_LargeCpuConsumption_CpuTimeLarge) {
   SetTraceLevel(1);
   FUNCTION_TRACE
   int i;
   for(i = 0; i<(1000*1000*1000); i++) {int u = i*i; u=u;}
   p0->Destructor();
   ASSERT_GE(p0->_Cpu_Time_Used_ms, 1000);
   ASSERT_GE(p0->_Clock_Time_Used_ms, 1000);
}

TEST(House, TraceLevel2_TwoFunction_InnerShorterThanOuter) {
   SetTraceLevel(2);
   FUNCTION_TRACE
   int i;
   for(i = 0; i<(1000*1000*10); i++) {int u = i*i; u=u;}
   FUNCTION_TRACE_TEST(1)
   int i2;
   for(i2 = 0; i2<(1000*1000*10); i2++) {int u = i2*i2; u=u;}
   p1->Destructor();
   p0->Destructor();
   ASSERT_GE(p0->_Cpu_Time_Used_ms, p1->_Cpu_Time_Used_ms);
   ASSERT_GE(p0->_Clock_Time_Used_ms, p1->_Clock_Time_Used_ms);
}

TEST(House, TraceLevel1_MultipleCalls_CheckPerformanceNotTooHigh) {
   SetTraceLevel(1);
   const int iLoopCounter = 1000*1000;
   FUNCTION_TRACE_TEST(1)
   for(int i = 2; i<iLoopCounter; i++) {
      FUNCTION_TRACE_TEST(i)
   }
   FUNCTION_TRACE_TEST_END(1)

   FUNCTION_TRACE
   for(int i = 2; i<iLoopCounter; i++) {int u = i*i; u=u;}
   FUNCTION_TRACE_TEST_END(0)

   ASSERT_GE(p1->_Cpu_Time_Used_ms,  p0->_Cpu_Time_Used_ms);
   ASSERT_LE(p1->_Cpu_Time_Used_ms, (p0->_Cpu_Time_Used_ms*300));
}
