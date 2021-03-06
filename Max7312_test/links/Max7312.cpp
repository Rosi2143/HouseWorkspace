
#include <stddef.h>
#include <wiringPi_Mock.h>
#include <wiringPiI2C_Mock.h>
#include "Max7312.h"
#include "helper.h"

/**
 * get the pin inside a byte from the pin - relative to pinBase
 * @param pin - pin relative to pinbase
 * @return ID in the byte
 */
#define GET_LOWER_PIN_ID(pin) (pin - _pinBase)

/**
 * get the pin inside a byte from the pin - relative to pinBase
 * @param pin - pin relative to pinbase
 * @return ID in the byte
 */
#define GET_HIGHER_PIN_ID(pin) (GET_LOWER_PIN_ID(pin) - 8)

/**
* read a single port - function required for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @return
 */
int _readPortMax7312(struct wiringPiNodeStruct *node, int pin){
   if(node == NULL)
   {
      return 0;
   }
   Max7312* _this = (Max7312*)(node->thisNode);
   if(_this == NULL)
   {
      return 0;
   }
   return _this->readPort(pin);
}

/**
 * write a single port - function requrired for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @param value - value to port should be set to 0 - OFF, 1 - ON
 */
void _writePortMax7312(struct wiringPiNodeStruct *node, int pin, int value){
   if(node == NULL)
   {
      return;
   }
   Max7312* _this = (Max7312*)(node->thisNode);
   if(_this == NULL)
   {
      return;
   }
   _this->writePort(pin, value);
}

/**
 * set a single port to Output or Input - function requrired for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @param mode - 0 - Output; 1 - Input
 */
void _configPortMax7312(struct wiringPiNodeStruct *node, int pin, int mode){
   if(node == NULL)
   {
      return;
   }
   Max7312* _this = (Max7312*)(node->thisNode);
   if(_this == NULL)
   {
      return;
   }
   _this->configPort(pin, mode);
}

// Comments
//
//...
/**
 * constructor were the specific chip address, the port directions and and the timeoutflag can be set
 * @param pinBase pinBase can be any number you like above 64
 * @param chipAddress chip address between 0x20 and 0x5E
 * @param intPin pin where the interrupt is connected to
 * @param portDirection1 default values of ports 0-7 (1 - input; 0 - output)
 * @param portDirection2 default values of ports 8-15 (1 - input; 0 - output)
 * @param timeoutFlag 1 enable Bus timeout, 0 disable Bus timeout
 */
Max7312::Max7312(unsigned int  pinBase,
                 unsigned char chipAddress,
                 unsigned char intPin,
                 unsigned char portDirection1,
                 unsigned char portDirection2,
                 unsigned char timeoutFlag)
: _intPin(intPin)
{
setChipAddress(chipAddress);
setPinBase(pinBase);
init(portDirection1, portDirection2, timeoutFlag);
}

/**
 * sets the chip address if it is in the correct range, otherwise it is set to MAX7312_MIN_ADDRESS
 * @param chipAddress I2C adress
 */
void Max7312::setChipAddress(unsigned char chipAddress)
{
   if(MAX7312_MAX_ADDRESS <= chipAddress)
   {
      _chipAddress=MAX7312_MAX_ADDRESS;
   }
   else if(MAX7312_MIN_ADDRESS >= chipAddress)
   {
      _chipAddress=MAX7312_MIN_ADDRESS;
   }
   else
   {
      _chipAddress=chipAddress;
   }
}

/**
 * sets the pinBase if it is in the correct range, otherwise it is set to MAX7312_MIN_PINBASE
 * @param pinBase - any number above 64
 */
void Max7312::setPinBase(unsigned int pinBase)
{
   if(MAX7312_MIN_PINBASE <= pinBase)
   {
      _pinBase=pinBase;
   }
   else
   {
      _pinBase=MAX7312_MIN_PINBASE;
   }
}

/**
 * initialize the Max7311
 * @param portDirection1 default values of ports 0-7 (1 - input; 0 - output)
 * @param portDirection2 default values of ports 8-15 (1 - input; 0 - output)
 * @param timeoutFlag 1 enable Bus timeout, 0 disable Bus timeout
*/
void Max7312::init(unsigned char portDirection1,
                   unsigned char portDirection2,
                   unsigned char timeoutFlag)
{
   initDataBuffers();


   if ((fd = wiringPiI2CSetup (_chipAddress)) < 0)
     return;

   node = wiringPiNewNode (_pinBase, MAX7312_NUM_OF_PORTS) ;

   node->fd           = fd ;
   node->pinMode      = _configPortMax7312;
   node->digitalRead  = _readPortMax7312;
   node->digitalWrite = _writePortMax7312;
   node->data1        = readPort1 () ;
   node->data2        = readPort2 () ;
   node->thisNode     = this;
   configPort1(portDirection1);
   configPort2(portDirection2);
   configTimeout(timeoutFlag);
}

/**
 * set all port data to 0
 */
void Max7312::initDataBuffers(){
_port1_data=0;
_port2_data=0;
}


/********** high level commands, for the user! */

/**
 * read the value of lower byte
 * @return value of port
 */
unsigned char Max7312::readPort1(){
wiringPiI2CWrite(fd, INPUT_PORT_1);
_port1_data=wiringPiI2CRead(fd);
return _port1_data;
}

/**
 * read the value of higher byte
 * @return value of port
 */
unsigned char Max7312::readPort2(){
wiringPiI2CWrite(fd, INPUT_PORT_2);
_port2_data=wiringPiI2CRead(fd);
return _port2_data;
}

/**
 * write byte data to lower port
 * @param portData
 */
void Max7312::writePort1(unsigned char portData){
wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, portData);
_port1_data = portData;
}

/**
 * write byte data to higher port
 * @param portData
 */
void Max7312::writePort2(unsigned char portData){
wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, portData);
_port2_data = portData;}

/**
 * set byte data to lower PolarityInversionRegister
 * @param portInversion
 */
void Max7312::polarityInversionPort1(unsigned char portInversion){
wiringPiI2CWriteReg16(fd, POLARITY_INVERSION_PORT_1, portInversion);
}

/**
 * set byte data to lower PolarityInversionRegister
 * @param portInversion
 */
void Max7312::polarityInversionPort2(unsigned char portInversion){
wiringPiI2CWriteReg16(fd, POLARITY_INVERSION_PORT_2, portInversion);
}

/**
 * set byte data to lower configuration register
 * @param portDirection
 */
void Max7312::configPort1(unsigned char portDirection){
wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, portDirection);
_port1_mode = portDirection;
}

/**
 * set byte data to higher configuration register
 * @param portDirection
 */
void Max7312::configPort2(unsigned char portDirection){
wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, portDirection);
_port2_mode = portDirection;
}

/**
 * (de-)activate I2C-timeout register
 * @param timeoutFlag
 */
void Max7312::configTimeout(unsigned char timeoutFlag){
wiringPiI2CWriteReg16(fd, TIMEOUT_REGISTER, timeoutFlag);
}

/**
 * checks the interrupt flag and if set reads the new value
 */
void Max7312::readIntFlag(){}

/*********** mid level commands, for sending data/cmds */

/**
 * checks if the port pin is active
 * @param pin - port relative to pinBase
 * @return true - port pin is active, false port pin is inactive
 */
bool Max7312::isPortActive(int pin){
   if(isLowerPort(pin)){
      return (CHECKBIT(_port1_data, (GET_LOWER_PIN_ID(pin))));
   } else {
      return (CHECKBIT(_port2_data, (GET_HIGHER_PIN_ID(pin))));
   }
}

/**
 * checks if the port pin is active
 * @param pin - port relative to pinBase
 * @return - true port pin is input, false port pin is output
 */
bool Max7312::isPortInput(int pin){
   if(isLowerPort(pin)){
      return (CHECKBIT(_port1_mode, (GET_LOWER_PIN_ID(pin))));
   } else {
      return (CHECKBIT(_port2_mode, (GET_HIGHER_PIN_ID(pin))));
   }
}

/**
 * check if the pin belongs to port1 or port2
 * @param pin - port relative to pinBase
 * @return TRUE - pin belongs to Port1(lower), FALSE - pin belongs to Port2(higher)
 */
bool Max7312::isLowerPort(int pin){
   if( (GET_LOWER_PIN_ID(pin)) <= 7){
      return true;
   }
   else {
      return false;
   }
}

/**
 * read a single port - function required for wiringPi interface
 * @param pin - port relative to pinBase
 * @return true - port is active, false - port is inactive
 */
bool Max7312::readPort(int pin){
   bool portIsInput = isPortInput(pin);
   if(isLowerPort(pin)){
      if (portIsInput){
         wiringPiI2CWrite(fd, INPUT_PORT_1);
      } else {
         wiringPiI2CWrite(fd, OUTPUT_PORT_1);
      }
   } else  {
      if (portIsInput){
         wiringPiI2CWrite(fd, INPUT_PORT_2);
      } else {
         wiringPiI2CWrite(fd, OUTPUT_PORT_2);
      }
   }
   int port_data=wiringPiI2CRead(fd);
   if(isLowerPort(pin)){
      _port1_data = port_data;
   } else {
      _port2_data = port_data;
   }
   return isPortActive(pin);
}

/**
 * write a single port - function required for wiringPi interface
 * @param pin - port relative to pinBase
 * @param newState - value to port should be set to 0 - OFF, 1 - ON
 * @return new value of complete port
 */
int Max7312::writePort(int pin, bool newState){
   if(isLowerPort(pin)){
      if(newState){
         SETBIT(_port1_data, (GET_LOWER_PIN_ID(pin)));
      } else {
         CLEARBIT(_port1_data, (GET_LOWER_PIN_ID(pin)));
      }
      writePort1(_port1_data);
      return _port1_data;
   } else {
      if(newState){
         SETBIT(_port2_data, (GET_HIGHER_PIN_ID(pin)));
      } else {
         CLEARBIT(_port2_data, (GET_HIGHER_PIN_ID(pin)));
      }
      writePort2(_port2_data);
      return _port2_data;
   }
}

/**
 * set a single port to Output or Input - function requrired for wiringPi interface
 * @param pin - port relative to pinBase
 * @param newMode - 0 - Output; 1 - Input
 * @return new value of complete port
 */
int Max7312::configPort(int pin, bool newMode){
   if (isLowerPort(pin)) {
      if(newMode)
      {
         SETBIT(_port1_mode, (GET_LOWER_PIN_ID(pin)));
      }
      else
      {
         CLEARBIT(_port1_mode, (GET_LOWER_PIN_ID(pin)));
      }
      configPort1(_port1_mode);
      return _port1_mode;
   } else {
      if(newMode)
      {
         SETBIT(_port2_mode, (GET_HIGHER_PIN_ID(pin)));
      }
      else
      {
         CLEARBIT(_port2_mode, (GET_HIGHER_PIN_ID(pin)));
      }
      configPort2(_port2_mode);
      return _port2_mode;
   }
}
