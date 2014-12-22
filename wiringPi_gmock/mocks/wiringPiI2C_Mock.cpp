/*
 * wiringPiI2C_mock.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: micha
 */

#include <gmock/gmock.h>  // Brings in Google Mock.

class MockWiringPiI2C{
 public:
   static MockWiringPiI2C* Instance();
   // Core wiringPi functions
   MOCK_METHOD1(wiringPiI2CRead,      int(int fd));
   MOCK_METHOD2(wiringPiI2CReadReg8,  int(int fd, int reg));
   MOCK_METHOD2(wiringPiI2CReadReg16, int(int fd, int reg));

   MOCK_METHOD2(wiringPiI2CWrite,      int(int fd, int data));
   MOCK_METHOD3(wiringPiI2CWriteReg8,  int(int fd, int reg, int data));
   MOCK_METHOD3(wiringPiI2CWriteReg16, int(int fd, int reg, int data));

   MOCK_METHOD2(wiringPiI2CSetupInterface, int(const char *device, int devId));
   MOCK_METHOD1(wiringPiI2CSetup,          int(const int devId));
 private:
   MockWiringPiI2C(){};
   MockWiringPiI2C(MockWiringPiI2C const&){};
   static MockWiringPiI2C* m_pInstance;
};

MockWiringPiI2C* MockWiringPiI2C::m_pInstance = NULL;

MockWiringPiI2C* MockWiringPiI2C::Instance()
{
   if (!m_pInstance){
      m_pInstance = new MockWiringPiI2C;
   }
   return m_pInstance;
}

// read functions
int wiringPiI2CRead           (int fd)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CRead(fd);
}

int wiringPiI2CReadReg8       (int fd, int reg)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CReadReg8(fd, reg);
}

int wiringPiI2CReadReg16      (int fd, int reg)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CReadReg16(fd, reg);
}

// write functions
int wiringPiI2CWrite          (int fd, int data)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CWrite(fd, data);
}

int wiringPiI2CWriteReg8      (int fd, int reg, int data)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CWriteReg8(fd, reg, data);
}

int wiringPiI2CWriteReg16     (int fd, int reg, int data)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CWriteReg16(fd, reg, data);
}


int wiringPiI2CSetupInterface (const char *device, int devId)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CSetupInterface(device, devId);
}

int wiringPiI2CSetup          (const int devId)
{
   return MockWiringPiI2C::Instance()->wiringPiI2CSetup(devId);
}
