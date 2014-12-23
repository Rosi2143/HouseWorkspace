/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Max7312.h"
#include "wiringPi_Mock.h"
#include "wiringPiI2C_Mock.h"

using namespace std;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

extern int _readPortMax7312(struct wiringPiNodeStruct *node, int pin);
extern void _writePortMax7312(struct wiringPiNodeStruct *node, int pin, int value);
extern void _configPortMax7312(struct wiringPiNodeStruct *node, int pin, int mode);

void SetExpectationsConstructor()
{
   int fd = 10;
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CSetup(_)).WillOnce(Return(fd));
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWrite(fd, INPUT_PORT_1)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWrite(fd, INPUT_PORT_2)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CRead (fd)).WillRepeatedly(Return(true));;
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, TIMEOUT_REGISTER, 1)).Times(1);
}
TEST(StaticFunctions, ReadPort_NodeNULL_OK)
{
   ASSERT_EQ(_readPortMax7312(NULL, 0),NULL);
}

TEST(StaticFunctions, ReadPort_thisNULL_OK)
{
   struct wiringPiNodeStruct *node ;
   node = new wiringPiNodeStruct();
   node->thisNode = NULL;
   ASSERT_EQ(_readPortMax7312(node, 0),NULL);
}

TEST(StaticFunctions, ReadPort_allOk_OK)
{
   struct wiringPiNodeStruct *node;
   node = new wiringPiNodeStruct();

   SetExpectationsConstructor();

   EXPECT_CALL(*(MockWiringPi::Instance()),wiringPiNewNode(_, _)).WillOnce(Return(node));
   Max7312 testMax;
   node->thisNode = &testMax;
   //ON_CALL(*(MockWiringPi::Instance()),wiringPiNewNode(_, _)).WillByDefault(Invoke());
   ASSERT_EQ(_readPortMax7312(NULL, 0),NULL);
}

TEST(StaticFunctions, WritePort_NodeNULL_OK)
{
   ASSERT_NO_THROW(_writePortMax7312(NULL, 0, 0));
}

TEST(StaticFunctions, WritePort_thisNULL_OK)
{
   struct wiringPiNodeStruct *node ;
   node = new wiringPiNodeStruct();
   node->thisNode = NULL;
   ASSERT_NO_THROW(_writePortMax7312(node, 0, 0));
}

TEST(StaticFunctions, ConfigPort_NULL_OK)
{
   ASSERT_NO_THROW(_configPortMax7312(NULL, 0, 0));
}

TEST(StaticFunctions, ConfigPort_thisNULL_OK)
{
   struct wiringPiNodeStruct *node ;
   node = new wiringPiNodeStruct();
   node->thisNode = NULL;
   ASSERT_NO_THROW(_configPortMax7312(node, 0, 0));
}

class TestFunctions : public ::testing::Test {
 protected:
  virtual void SetUp() {
     node = new wiringPiNodeStruct();
     SetExpectationsConstructor();
     EXPECT_CALL(*(MockWiringPi::Instance()),wiringPiNewNode(_, _)).WillOnce(Return(node));
     testMax = new Max7312;
     testMax->setPinBase(MAX7312_MIN_PINBASE);
  }

  // virtual void TearDown() {}
  struct wiringPiNodeStruct *node;
  Max7312* testMax;
};
// test testfunctions
// isLowerPort
TEST_F(TestFunctions, isLowerPort_low0_yes)
{
   ASSERT_EQ(testMax->isLowerPort(MAX7312_MIN_PINBASE + 0), true);
}

TEST_F(TestFunctions, isLowerPort_low3_yes)
{
   ASSERT_EQ(testMax->isLowerPort(MAX7312_MIN_PINBASE + 3), true);
}

TEST_F(TestFunctions, isLowerPort_low7_yes)
{
   ASSERT_EQ(testMax->isLowerPort(MAX7312_MIN_PINBASE + 7), true);
}

TEST_F(TestFunctions, isLowerPort_high8_no)
{
   ASSERT_EQ(testMax->isLowerPort(MAX7312_MIN_PINBASE + 8), false);
}

TEST_F(TestFunctions, isLowerPort_high11_no)
{
   ASSERT_EQ(testMax->isLowerPort(MAX7312_MIN_PINBASE + 11), false);
}

TEST_F(TestFunctions, isLowerPort_high15_no)
{
   ASSERT_EQ(testMax->isLowerPort(MAX7312_MIN_PINBASE + 15), false);
}

// isPortInput
TEST_F(TestFunctions, isPortInput_low0_yes)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 0, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 0), true);
}

TEST_F(TestFunctions, isPortInput_low3_yes)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 3, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 3), true);
}

TEST_F(TestFunctions, isPortInput_low7_yes)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 7, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 7), true);
}

TEST_F(TestFunctions, isPortInput_low0_no)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 0, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 0), false);
}

TEST_F(TestFunctions, isPortInput_low3_no)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 3, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 3), false);
}

TEST_F(TestFunctions, isPortInput_low7_no)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 7, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 7), false);
}

TEST_F(TestFunctions, isPortInput_high8_no)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 8, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 8), false);
}

TEST_F(TestFunctions, isPortInput_high11_no)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 11, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 11), false);
}

TEST_F(TestFunctions, isPortInput_high15_no)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 15, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 15), false);
}

TEST_F(TestFunctions, isPortInput_high8_yes)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 8, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 8), true);
}

TEST_F(TestFunctions, isPortInput_high11_yes)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 11, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 11), true);
}

TEST_F(TestFunctions, isPortInput_high15_yes)
{
   testMax->configPort(MAX7312_MIN_PINBASE + 15, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 15), true);
}
