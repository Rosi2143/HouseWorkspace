/*
 * wiringPi_mock.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: micha
 */

#include "wiringPi_Mock.h"

MockWiringPi* MockWiringPi::m_pInstance = NULL;

MockWiringPi* MockWiringPi::Instance()
{
   if (!m_pInstance){
      m_pInstance = new MockWiringPi;
   }
   return m_pInstance;
}


// Core wiringPi functions

struct wiringPiNodeStruct *wiringPiFindNode (int pin)
{
   return MockWiringPi::Instance()->wiringPiFindNode(pin);
}
struct wiringPiNodeStruct *wiringPiNewNode  (int pinBase, int numPins)
{
   return MockWiringPi::Instance()->wiringPiNewNode(pinBase, numPins);
}

int  wiringPiSetup       (void)
{
   return MockWiringPi::Instance()->wiringPiSetup();
}

int  wiringPiSetupSys    (void)
{
   return MockWiringPi::Instance()->wiringPiSetupSys();
}

int  wiringPiSetupGpio   (void)
{
   return MockWiringPi::Instance()->wiringPiSetupGpio();
}

int  wiringPiSetupPhys   (void)
{
   return MockWiringPi::Instance()->wiringPiSetupPhys();
}

void pinModeAlt          (int pin, int mode)
{
   MockWiringPi::Instance()->pinModeAlt(pin, mode);
}

void pinMode             (int pin, int mode)
{
   MockWiringPi::Instance()->pinMode(pin, mode);
}

void pullUpDnControl     (int pin, int pud)
{
   MockWiringPi::Instance()->pullUpDnControl(pin, pud);
}

int  digitalRead         (int pin)
{
   return MockWiringPi::Instance()->digitalRead(pin);
}

void digitalWrite        (int pin, int value)
{
   MockWiringPi::Instance()->digitalWrite(pin, value);
}

void pwmWrite            (int pin, int value)
{
   MockWiringPi::Instance()->pwmWrite(pin, value);
}

int  analogRead          (int pin)
{
   return MockWiringPi::Instance()->analogRead(pin);
}

void analogWrite         (int pin, int value)
{
   MockWiringPi::Instance()->analogWrite(pin, value);
}
