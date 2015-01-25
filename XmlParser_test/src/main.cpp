/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XmlParser.h"

using namespace std;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

TEST(XmlParser, Read_OK) {
   House _house = readxml("src/house.xml");
   ASSERT_EQ(_house.Version, 2);
   std::string Name("Störtenberg 3");
   ASSERT_STRCASEEQ(Name.c_str(), _house.Name.c_str());
}