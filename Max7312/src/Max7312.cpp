
#include "Max7312.h"
//#include "Ardino.h"
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "helper.h"

/**
 * read a single port - function required for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @return
 */
static int _readPortMax7312(struct wiringPiNodeStruct *node, int pin){
   Max7312* _this = (Max7312*)(node->thisNode);
   return _this->readPort(pin);
}

/**
 * write a single port - function requrired for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @param value - value to port should be set to 0 - OFF, 1 - ON
 */
static void _writePortMax7312(struct wiringPiNodeStruct *node, int pin, int value){
   Max7312* _this = (Max7312*)(node->thisNode);
   _this->writePort(pin, value);
}

/**
 * set a single port to Output or Input - function requrired for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @param mode - 0 - Output; 1 - Input
 */
static void _configPortMax7312(struct wiringPiNodeStruct *node, int pin, int mode){
   Max7312* _this = (Max7312*)(node->thisNode);
   _this->configPort(pin, mode);
}

// Comments
//
//...

/**
 * default constructor uses address #MAX7312_ADDRESS
 */
Max7312::Max7312(){
setChipAddress(MAX7312_ADDRESS);
setPinBase(MAX7312_MIN_PINBASE);
init(0x00, 0x00);
}

/**
 *
 * constructor were the specific chip address can be set
 * @param pinBase pinBase can be any number you like above 64
 * @param chipAddress chip address between 0x20 and 0x5E
 */
Max7312::Max7312(unsigned int pinBase, unsigned char chipAddress){
setChipAddress(chipAddress);
setPinBase(pinBase);
init(0x00, 0x00);
}

/**
 * constructor were the specific chip address and the port directions can be set
 * @param pinBase pinBase can be any number you like above 64
 * @param chipAddress chip address between 0x20 and 0x5E
 * @param portDirection1 default values of ports 0-7 (1 - input; 0 - output)
 * @param portDirection2 default values of ports 8-15 (1 - input; 0 - output)
 */
Max7312::Max7312(unsigned int pinBase, unsigned char chipAddress, unsigned char portDirection1, unsigned char portDirection2)
{
setChipAddress(chipAddress);
setPinBase(pinBase);
init(portDirection1, portDirection2);
}

/**
 * constructor were the specific chip address, the port directions and and the timeoutflag can be set
 * @param pinBase pinBase can be any number you like above 64
 * @param chipAddress chip address between 0x20 and 0x5E
 * @param portDirection1 default values of ports 0-7 (1 - input; 0 - output)
 * @param portDirection2 default values of ports 8-15 (1 - input; 0 - output)
 * @param timeoutFlag 1 enable Bus timeout, 0 disable Bus timeout
 */
Max7312::Max7312(unsigned int pinBase, unsigned char chipAddress, unsigned char portDirection1, unsigned char portDirection2, unsigned char timeoutFlag)
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
if( (MAX7312_MIN_ADDRESS <= chipAddress)
and (MAX7312_MAX_ADDRESS >= chipAddress)
)
{
_chipAddress=chipAddress;
}
else
{
_chipAddress=MAX7312_MIN_ADDRESS;
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
 */
void Max7312::init(unsigned char portDirection1, unsigned char portDirection2)
{
init(portDirection1, portDirection2, 0x01);
}

/**
 * initialize the Max7311
 * @param portDirection1 default values of ports 0-7 (1 - input; 0 - output)
 * @param portDirection2 default values of ports 8-15 (1 - input; 0 - output)
 * @param timeoutFlag 1 enable Bus timeout, 0 disable Bus timeout
*/
void Max7312::init(unsigned char portDirection1, unsigned char portDirection2, unsigned char timeoutFlag)
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

void Max7312::writePort1(unsigned char portData){
wiringPiI2CWriteReg16(fd, OUTPUT_PORT_1, portData);
}
void Max7312::writePort2(unsigned char portData){
wiringPiI2CWriteReg16(fd, OUTPUT_PORT_2, portData);
}

void Max7312::polarityInversionPort1(unsigned char portInversion){
wiringPiI2CWriteReg16(fd, POLARITY_INVERSION_PORT_1, portInversion);
}
void Max7312::polarityInversionPort2(unsigned char portInversion){
wiringPiI2CWriteReg16(fd, POLARITY_INVERSION_PORT_2, portInversion);
}

void Max7312::configPort1(unsigned char portDirection){
wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_1, portDirection);
}

void Max7312::configPort2(unsigned char portDirection){
wiringPiI2CWriteReg16(fd, CONFIGURATION_PORT_2, portDirection);
}

void Max7312::configTimeout(unsigned char timeoutFlag){
wiringPiI2CWriteReg16(fd, TIMEOUT_REGISTER, timeoutFlag);
}

void Max7312::readIntFlag(){}

/*********** mid level commands, for sending data/cmds */

/**
 * checks if the port pin is active
 * @param portValue
 * @return true - port pin is active, false port pin is inactive
 */
bool Max7312::isPortActive(int portValue, int pin){
   if(isLowerPort(pin)){
      return (CHECKBIT(portValue, (pin - _pinBase)));
   } else {
      return (CHECKBIT(portValue, (pin - _pinBase - 8)));
   }
}

/**
 * sets one port pin to the new state
 * @param portValue old port value
 * @param pin port relative to pinBase
 * @param newState true - new port state is active, false new port state is inactive
 * @return new value of port
 */
int Max7312::setPortActive(int portValue, int pin, bool newState){
   if(isLowerPort(pin)){
      return (CHECKBIT(portValue, (pin - _pinBase)));
   } else {
      return (CHECKBIT(portValue, (pin - _pinBase - 8)));
   }
}

/**
 * checks if the port pin is active
 * @param pin - port relative to pinBase
 * @return - true port pin is input, false port pin is output
 */
bool Max7312::isPortInput(int pin){
   if(isLowerPort(pin)){
      return (CHECKBIT(_port1_mode, (pin - _pinBase)));
   } else {
      return (CHECKBIT(_port2_mode, (pin - _pinBase - 8)));
   }
}

/**
 * check if the pin belongs to port1 or port2
 * @param pin - port relative to pinBase
 * @return TRUE - pin belongs to Port1(lower), FALSE - pin belongs to Port2(higher)
 */
bool Max7312::isLowerPort(int pin){
   if( (pin - _pinBase) <= 7){
      return true;
   }
   else {
      return false;
   }
}

/**
 * read a single port - function required for wiringPi interface
 * @param node link to port structure
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
   return isPortActive(port_data, pin);
}

/**
 * write a single port - function requrired for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @param value - value to port should be set to 0 - OFF, 1 - ON
 */
void Max7312::writePort(int pin, bool state){
   if(isLowerPort(pin)){
      wiringPiI2CWrite(fd, OUTPUT_PORT_1);
   } else  {
      wiringPiI2CWrite(fd, INPUT_PORT_2);
   }
}

/**
 * set a single port to Output or Input - function requrired for wiringPi interface
 * @param node link to port structure
 * @param pin - port relative to pinBase
 * @param mode - 0 - Output; 1 - Input
 */
void Max7312::configPort(int pin, bool mode){
   if (isLowerPort(pin)) {
      if(mode)
      _port1_mode = mode;
   } else {
      _port2_mode = mode;
   }
}

