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

using namespace std;

extern int _readPortMax7312(struct wiringPiNodeStruct *node, int pin);
extern void _writePortMax7312(struct wiringPiNodeStruct *node, int pin, int value);
extern void _configPortMax7312(struct wiringPiNodeStruct *node, int pin, int mode);

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
   Max7312 testMax;
   struct wiringPiNodeStruct *node ;
   node = new wiringPiNodeStruct();
   node->thisNode = &testMax;
   ASSERT_EQ(_readPortMax7312(NULL, 0),NULL);
}

TEST(StaticFunctions, WritePort_NodeNULL_OK)
{
   ASSERT_NO_THROW(_writePortMax7312(NULL, 0, 0));
}

TEST(StaticFunctions, ConfigPort_NULL_OK)
{
   ASSERT_NO_THROW(_configPortMax7312(NULL, 0, 0));
}
