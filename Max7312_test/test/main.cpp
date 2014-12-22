/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Max7312.h"

using namespace std;

extern int _readPortMax7312(struct wiringPiNodeStruct *node, int pin);

TEST(StaticFunctions, ReadPort_NULL_OK)
{
   ASSERT_EQ(_readPortMax7312(NULL, 1),NULL);
}