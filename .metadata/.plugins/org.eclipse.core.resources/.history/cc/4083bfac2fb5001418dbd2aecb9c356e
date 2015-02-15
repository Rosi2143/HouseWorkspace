/*
 * main.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Switch.h"
using namespace std;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

TEST(XmlParser, Read_OK) {
   House _house;
   _house.readHouseXml("src/test_OK.xml");
   ASSERT_EQ(_house.getVersion(), 2);
   string HouseName("Störtenberg 3");
   ASSERT_STRCASEEQ(HouseName.c_str(), _house.getName().c_str());
   ASSERT_EQ(3, _house.getNumberOfFloors());
   ASSERT_EQ(6, _house.getNumberOfRooms());

   string FloorName("_AA_");
   EXPECT_NO_THROW(_house.getFloor(FloorName));
   ASSERT_STRCASEEQ(FloorName.c_str(),_house.getFloor(FloorName).getName().c_str());

   EXPECT_ANY_THROW(_house.getFloor("test"));

   string RoomName("AA");
   EXPECT_NO_THROW(_house.getRoom(RoomName));
   ASSERT_STRCASEEQ(RoomName.c_str(),_house.getRoom(RoomName).Name.c_str());

   EXPECT_ANY_THROW(_house.getRoom("test"));
}
