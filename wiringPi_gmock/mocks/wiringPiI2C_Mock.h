/*
 * wiringPiI2C.h:
 *	Simplified I2C access routines
 *	Copyright (c) 2013 Gordon Henderson
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with wiringPi.
 *    If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

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

   ~MockWiringPiI2C(){delete m_pInstance;}
private:
   MockWiringPiI2C(){};
   MockWiringPiI2C(MockWiringPiI2C const&){};
   static MockWiringPiI2C* m_pInstance;
};

extern int wiringPiI2CRead           (int fd) ;
extern int wiringPiI2CReadReg8       (int fd, int reg) ;
extern int wiringPiI2CReadReg16      (int fd, int reg) ;

extern int wiringPiI2CWrite          (int fd, int data) ;
extern int wiringPiI2CWriteReg8      (int fd, int reg, int data) ;
extern int wiringPiI2CWriteReg16     (int fd, int reg, int data) ;

extern int wiringPiI2CSetupInterface (const char *device, int devId) ;
extern int wiringPiI2CSetup          (const int devId) ;

