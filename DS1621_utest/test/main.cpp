/*
 * main.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Ds1621.h"

using namespace std;

TEST(Test, Test)
{
   Ds1621 TempSensor(01);
   ASSERT_EQ(TempSensor.isDeviceUp(), false);
}
