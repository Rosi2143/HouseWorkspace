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
using ::testing::TestWithParam;
using ::testing::Values;

extern int _readPortMax7312   (struct wiringPiNodeStruct *node, int pin);
extern void _writePortMax7312 (struct wiringPiNodeStruct *node, int pin, int value);
extern void _configPortMax7312(struct wiringPiNodeStruct *node, int pin, int mode);

void SetExpectationsConstructor(int fd)
{
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

   SetExpectationsConstructor(10);

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
 public:
  TestFunctions():fd(10)
                 ,node(NULL)
                 ,testMax(NULL){}
 protected:
  virtual void SetUp() {
     node = new wiringPiNodeStruct();
     SetExpectationsConstructor(fd);
     EXPECT_CALL(*(MockWiringPi::Instance()),wiringPiNewNode(_, _)).WillOnce(Return(node));
     testMax = new Max7312;
     testMax->setPinBase(MAX7312_MIN_PINBASE);
  }

  // virtual void TearDown() {}
  int fd;
  struct wiringPiNodeStruct *node;
  Max7312* testMax;
};

typedef struct {int pin; bool out;} IsLowerTypes;
class TestFunctionsIsLower : public TestFunctions,
                           public ::testing::WithParamInterface<IsLowerTypes> {
};
INSTANTIATE_TEST_CASE_P(TestFunctionsParamIsLower,
                        TestFunctionsIsLower,
                        ::testing::Values(
                              IsLowerTypes({MAX7312_MIN_PINBASE + 0, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 1, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 2, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 3, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 4, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 5, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 6, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 7, true}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 8, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 9, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 10, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 11, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 12, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 13, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 14, false}),
                              IsLowerTypes({MAX7312_MIN_PINBASE + 15, false}))
                       );
// test test functions
// isLowerPort
TEST_P(TestFunctionsIsLower, isLowerPort_Params)
{
   IsLowerTypes const& p = GetParam();
   ASSERT_EQ(testMax->isLowerPort(p.pin), p.out);
}

// isPortInput
TEST_F(TestFunctions, isPortInput_low0_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 0, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 0), true);
}

TEST_F(TestFunctions, isPortInput_low3_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 3, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 3), true);
}

TEST_F(TestFunctions, isPortInput_low7_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 7, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 7), true);
}

TEST_F(TestFunctions, isPortInput_low0_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 0, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 0), false);
}

TEST_F(TestFunctions, isPortInput_low3_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 3, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 3), false);
}

TEST_F(TestFunctions, isPortInput_low7_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 7, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 7), false);
}

TEST_F(TestFunctions, isPortInput_high8_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 8, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 8), false);
}

TEST_F(TestFunctions, isPortInput_high11_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 11, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 11), false);
}

TEST_F(TestFunctions, isPortInput_high15_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 15, 0);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 15), false);
}

TEST_F(TestFunctions, isPortInput_high8_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 8, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 8), true);
}

TEST_F(TestFunctions, isPortInput_high11_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 11, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 11), true);
}

TEST_F(TestFunctions, isPortInput_high15_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, _)).Times(1);
   testMax->configPort(MAX7312_MIN_PINBASE + 15, 1);
   ASSERT_EQ(testMax->isPortInput(MAX7312_MIN_PINBASE + 15), true);
}

// isPortActive
TEST_F(TestFunctions, isPortActive_high5_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, _)).Times(1);
   testMax->writePort(MAX7312_MIN_PINBASE + 5, 1);
   ASSERT_EQ(testMax->isPortActive(MAX7312_MIN_PINBASE + 5), true);
}

TEST_F(TestFunctions, isPortActive_low5_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, _)).Times(1);
   testMax->writePort(MAX7312_MIN_PINBASE + 5, 0);
   ASSERT_EQ(testMax->isPortActive(MAX7312_MIN_PINBASE + 5), false);
}

TEST_F(TestFunctions, isPortActive_high15_yes)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, _)).Times(1);
   testMax->writePort(MAX7312_MIN_PINBASE + 15, 1);
   ASSERT_EQ(testMax->isPortActive(MAX7312_MIN_PINBASE + 15), true);
}

TEST_F(TestFunctions, isPortActive_low15_no)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, _)).Times(1);
   testMax->writePort(MAX7312_MIN_PINBASE + 15, 0);
   ASSERT_EQ(testMax->isPortActive(MAX7312_MIN_PINBASE + 15), false);
}

// test write function
class TestFunctionsWritePort : public TestFunctions,
                               public ::testing::WithParamInterface<unsigned int> {
};
INSTANTIATE_TEST_CASE_P(TestFunctionsParamWritePort,
                        TestFunctionsWritePort,
                        ::testing::Range(0U,256U));
TEST_P(TestFunctionsWritePort, writePort1_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, GetParam())).Times(1);
   testMax->writePort1(GetParam());
   ASSERT_EQ(testMax->getPort1Data(), GetParam());
}
TEST_P(TestFunctionsWritePort, writePort2_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, GetParam())).Times(1);
   testMax->writePort2(GetParam());
   ASSERT_EQ(testMax->getPort2Data(), GetParam());
}
TEST_P(TestFunctionsWritePort, configPort1_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, GetParam())).Times(1);
   testMax->configPort1(GetParam());
   ASSERT_EQ(testMax->getPort1Mode(), GetParam());
}
TEST_P(TestFunctionsWritePort, configPort2_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, GetParam())).Times(1);
   testMax->configPort2(GetParam());
   ASSERT_EQ(testMax->getPort2Mode(), GetParam());
}

typedef struct {int pin; int LowerPort; int HigherPort;} BitCoded;
class TestFunctionsBitCoded : public TestFunctions,
                              public ::testing::WithParamInterface<BitCoded> {
};
INSTANTIATE_TEST_CASE_P(TestFunctionsParamBitCoded,
                        TestFunctionsBitCoded,
                        ::testing::Values(
                              BitCoded({MAX7312_MIN_PINBASE + 0,  0x01, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 1,  0x02, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 2,  0x04, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 3,  0x08, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 4,  0x10, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 5,  0x20, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 6,  0x40, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 7,  0x80, 0x00}),
                              BitCoded({MAX7312_MIN_PINBASE + 8,  0x00, 0x01}),
                              BitCoded({MAX7312_MIN_PINBASE + 9,  0x00, 0x02}),
                              BitCoded({MAX7312_MIN_PINBASE + 10, 0x00, 0x04}),
                              BitCoded({MAX7312_MIN_PINBASE + 11, 0x00, 0x08}),
                              BitCoded({MAX7312_MIN_PINBASE + 12, 0x00, 0x10}),
                              BitCoded({MAX7312_MIN_PINBASE + 13, 0x00, 0x20}),
                              BitCoded({MAX7312_MIN_PINBASE + 14, 0x00, 0x40}),
                              BitCoded({MAX7312_MIN_PINBASE + 15, 0x00, 0x80}))
                       );
TEST_P(TestFunctionsBitCoded, writePort_OFF_ON_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0)).Times(1);
   testMax->writePort1(0x00);
   testMax->writePort2(0x00);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, GetParam().LowerPort)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, GetParam().HigherPort)).Times(1);
   }
   testMax->writePort(GetParam().pin, true);
   ASSERT_EQ(testMax->getPort1Data(), GetParam().LowerPort);
   ASSERT_EQ(testMax->getPort2Data(), GetParam().HigherPort);
}

TEST_P(TestFunctionsBitCoded, writePort_ON_ON_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0xFF)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0xFF)).Times(1);
   testMax->writePort1(0xFF);
   testMax->writePort2(0xFF);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0xFF)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0xFF)).Times(1);
   }
   testMax->writePort(GetParam().pin, true);
   ASSERT_EQ(testMax->getPort1Data(), 0xFF);
   ASSERT_EQ(testMax->getPort2Data(), 0xFF);
}

TEST_P(TestFunctionsBitCoded, writePort_OFF_OFF_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0x00)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0x00)).Times(1);
   testMax->writePort1(0x00);
   testMax->writePort2(0x00);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0x00)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0x00)).Times(1);
   }
   testMax->writePort(GetParam().pin, false);
   ASSERT_EQ(testMax->getPort1Data(), 0x00);
   ASSERT_EQ(testMax->getPort2Data(), 0x00);
}

TEST_P(TestFunctionsBitCoded, writePort_ON_OFF_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0xFF)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0xFF)).Times(1);
   testMax->writePort1(0xFF);
   testMax->writePort2(0xFF);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, 0xFF - GetParam().LowerPort)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, 0xFF - GetParam().HigherPort)).Times(1);
   }
   testMax->writePort(GetParam().pin, false);
   ASSERT_EQ(testMax->getPort1Data(), 0xFF - GetParam().LowerPort);
   ASSERT_EQ(testMax->getPort2Data(), 0xFF - GetParam().HigherPort);
}

//config port
TEST_P(TestFunctionsBitCoded, configPort_OFF_ON_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0)).Times(1);
   testMax->configPort1(0x00);
   testMax->configPort2(0x00);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, GetParam().LowerPort)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, GetParam().HigherPort)).Times(1);
   }
   testMax->configPort(GetParam().pin, true);
   ASSERT_EQ(testMax->getPort1Mode(), GetParam().LowerPort);
   ASSERT_EQ(testMax->getPort2Mode(), GetParam().HigherPort);
}

TEST_P(TestFunctionsBitCoded, configPort_ON_ON_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0xFF)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0xFF)).Times(1);
   testMax->configPort1(0xFF);
   testMax->configPort2(0xFF);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0xFF)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0xFF)).Times(1);
   }
   testMax->configPort(GetParam().pin, true);
   ASSERT_EQ(testMax->getPort1Mode(), 0xFF);
   ASSERT_EQ(testMax->getPort2Mode(), 0xFF);
}

TEST_P(TestFunctionsBitCoded, configPort_OFF_OFF_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0x00)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0x00)).Times(1);
   testMax->configPort1(0x00);
   testMax->configPort2(0x00);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0x00)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0x00)).Times(1);
   }
   testMax->configPort(GetParam().pin, false);
   ASSERT_EQ(testMax->getPort1Mode(), 0x00);
   ASSERT_EQ(testMax->getPort2Mode(), 0x00);
}

TEST_P(TestFunctionsBitCoded, configPort_ON_OFF_equal)
{
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0xFF)).Times(1);
   EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0xFF)).Times(1);
   testMax->configPort1(0xFF);
   testMax->configPort2(0xFF);
   if(GetParam().pin < (MAX7312_MIN_PINBASE + 8)){
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, 0xFF - GetParam().LowerPort)).Times(1);
   } else {
      EXPECT_CALL(*(MockWiringPiI2C::Instance()), wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, 0xFF - GetParam().HigherPort)).Times(1);
   }
   testMax->configPort(GetParam().pin, false);
   ASSERT_EQ(testMax->getPort1Mode(), 0xFF - GetParam().LowerPort);
   ASSERT_EQ(testMax->getPort2Mode(), 0xFF - GetParam().HigherPort);
}

typedef struct {int address_in; int address_out;} ChipAddress;
class TestFunctionsChipAddress : public TestFunctions,
                                 public ::testing::WithParamInterface<ChipAddress> {
};
INSTANTIATE_TEST_CASE_P(TestFunctionsParamChipAddress,
                        TestFunctionsChipAddress,
                        ::testing::Values(
                              ChipAddress({MAX7312_MIN_ADDRESS -1,  MAX7312_MIN_ADDRESS}),
                              ChipAddress({MAX7312_MIN_ADDRESS,     MAX7312_MIN_ADDRESS}),
                              ChipAddress({MAX7312_MIN_ADDRESS + 1, MAX7312_MIN_ADDRESS + 1}),
                              ChipAddress({MAX7312_MAX_ADDRESS - 1, MAX7312_MAX_ADDRESS - 1}),
                              ChipAddress({MAX7312_MAX_ADDRESS,     MAX7312_MAX_ADDRESS}),
                              ChipAddress({MAX7312_MAX_ADDRESS + 1, MAX7312_MAX_ADDRESS}))
                       );
TEST_P(TestFunctionsChipAddress, setChipAddress_params)
{
   testMax->setChipAddress(GetParam().address_in);
   ASSERT_EQ(testMax->getChipAddress(), GetParam().address_out);
}

typedef struct {int address_in; int address_out;} PinBase;
class TestFunctionsPinBase : public TestFunctions,
                                 public ::testing::WithParamInterface<PinBase> {
};
INSTANTIATE_TEST_CASE_P(TestFunctionsParamPinBase,
                        TestFunctionsPinBase,
                        ::testing::Values(
                              PinBase({MAX7312_MIN_PINBASE -1,  MAX7312_MIN_PINBASE}),
                              PinBase({MAX7312_MIN_PINBASE,     MAX7312_MIN_PINBASE}),
                              PinBase({MAX7312_MIN_PINBASE + 1, MAX7312_MIN_PINBASE + 1}))
                       );
TEST_P(TestFunctionsPinBase, setPinBase_params)
{
   testMax->setPinBase(GetParam().address_in);
   ASSERT_EQ(testMax->getPinBase(), GetParam().address_out);
}
