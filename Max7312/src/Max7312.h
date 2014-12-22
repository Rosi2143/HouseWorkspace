#ifndef Max7312_h
#define Max7312_h

#include "INode.h"

// Chip Addresses, it is default address and can be changed
// with AD0, AD1 and AD2 pins same as i2c EEPROM

/**
 * defines the number of GPIO pins of the Max7312
 */
#define MAX7312_NUM_OF_PORTS 16

/**
 * defines the minimum possible address for the device
 */
#define MAX7312_MIN_ADDRESS 0x20

/**
 * defines the maximum possible address for the device
 */
#define MAX7312_MAX_ADDRESS 0x5E

/**
 * defines the default address for the device
 */
#define MAX7312_ADDRESS MAX7312_MIN_ADDRESS


/**
 * defines the minimum possible pinBase for the device
 */
#define MAX7312_MIN_PINBASE 64


//Register address	

/**
 * command byte register address to read first input port
 */
#define INPUT_PORT_1 0X00

/**
 * command byte register address to read first input port
 */
#define INPUT_PORT_2 0X01

/**
 * Output Port Registers
 * The output port registers (Table 3) set the outgoing
* logic levels of the I/Os defined as outputs by the
* respective configuration register. Reads from the out-
* put port registers reflect the value that is in the flip-flop
* controlling the output selection, not the actual I/O value.
 */
#define OUTPUT_PORT_1 0x02
#define OUTPUT_PORT_2 0x03

/**
 * Polarity Inversion Registers
 * The polarity inversion registers (Table 4) enable polarity
 * inversion of pins defined as inputs by the respective
 * port configuration registers. Set the bit in the polarity
 * inversion register to invert the corresponding port pin’s
 * polarity. Clear the bit in the polarity inversion register to
 * retain the corresponding port pin’s original polarity.
 */
#define POLARITY_INVERSION_PORT_1 0x04
#define POLARITY_INVERSION_PORT_2 0x05

/**
 * Configuration Registers
 * The configuration registers (Table 5) configure the
 * directions of the I/O pins. Set the bit in the respective
 * configuration register to enable the corresponding port
 * as an input. Clear the bit in the configuration register to
 * enable the corresponding port as an output.
 */
#define CONFIGURATION_PORT_1 0x06
#define CONFIGURATION_PORT_2 0x07

/**
 * Bus Timeout
 * Set register 0x08 LSB (bit 0) to enable the bus timeout
 * function (Table 6) or clear it to disable the bus timeout
 * function. Enabling the timeout feature resets the
 * MAX7311 serial bus interface when SCL stops either high
 * or low during a read or write. If either SCL or SDA is low
 * for more than 29ms after the start of a valid serial transfer,
 * the interface resets itself and sets up SDA as an input.
 * The MAX7311 then waits for another START condition.
 */
#define TIMEOUT_REGISTER 0x08

/**
 * reserved value - do not use
 */
#define FACTORY_RESERVED 0xFF

class Max7312 : public INode{
public:
  Max7312();
  Max7312(unsigned int pinBase, unsigned char chipAddress);
  Max7312(unsigned int pinBase, unsigned char chipAddress, unsigned char portDirection1, unsigned char portDirection2);
  Max7312(unsigned int pinBase, unsigned char chipAddress, unsigned char portDirection1, unsigned char portDirection2, unsigned char timeoutFlag);
  virtual ~Max7312(){}

  void setChipAddress(unsigned char chipAddress);
  void setPinBase(unsigned int pinBase);

  void init(unsigned char portDirection1, unsigned char portDirection2);
  void init(unsigned char portDirection1, unsigned char portDirection2, unsigned char timeoutFlag);
  
//  int readPort(struct wiringPiNodeStruct *node, int pin);
  unsigned char readPort1();
  unsigned char readPort2();
  
//  void writePort(struct wiringPiNodeStruct *node, int pin, int value);
  void writePort1(unsigned char portData);
  void writePort2(unsigned char portData);
  
  void polarityInversionPort1(unsigned char portInversion);
  void polarityInversionPort2(unsigned char portInversion);
  
//  void configPort(struct wiringPiNodeStruct *node, int pin, int mode);
  void configPort1(unsigned char portDirection);
  void configPort2(unsigned char portDirection);
  
  void configTimeout(unsigned char timeoutFlag);
  
  void readIntFlag();
  
  virtual bool isLowerPort (int pin);
  virtual bool isPortActive (int portValue, int pin);
  virtual int  setPortActive(int portValue, int pin, bool newState);
  virtual bool isPortInput (int pin);
  virtual wiringPiNodeStruct* getNode(){return node;}
  virtual bool readPort  (int pin);
  virtual void writePort (int pin, bool state);
  virtual void configPort(int pin, bool mode);
private:

  void initDataBuffers();

  int 			fd ;
  struct wiringPiNodeStruct *node ;
  unsigned char _int_pin; // LOW: active.
  unsigned char _port1_data;
  unsigned char _port2_data;
  unsigned char _port1_mode;
  unsigned char _port2_mode;
  unsigned char _chipAddress;
  unsigned int  _pinBase;
};

#endif
