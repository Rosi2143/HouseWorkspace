#ifndef Max7312_h
#define Max7312_h

// Chip Addresses, it is default addres and can be changed 
// with AD0, AD1 and AD2 pins same as i2c EEPROM
#define MAX7312_ADDRESS 0x20

//Register address	
#define INPUT_PORT_1 0X00
#define INPUT_PORT_2 0X01

#define OUTPUT_PORT_1 0x02
#define OUTPUT_PORT_2 0x03

#define POLARITY_INVERSION_PORT_1 0x04
#define POLARITY_INVERSION_PORT_2 0x05

#define CONFIGURATION_PORT_1 0x06
#define CONFIGURATION_PORT_2 0x07

#define TIMEOUT_REGISTER 0x08
#define FACTORY_RESERVED 0xFF

class Max7312{
public:
  Max7312();
  Max7312(unsigned char chipAddress);
  Max7312(unsigned char chipAddress, unsigned char portDirection1, unsigned char portDirection2);
  Max7312(unsigned char chipAddress, unsigned char portDirection1, unsigned char portDirection2, unsigned char timeoutFlag);

  void init(unsigned char portDirection1, unsigned char portDirection2);
  void init(unsigned char portDirection1, unsigned char portDirection2, unsigned char timeoutFlag);
  
  unsigned char readPort1();
  unsigned char readPort2();
  
  void writePort1(unsigned char portData);
  void writePort2(unsigned char portData);
  
  void polarityInversionPort1(unsigned char portInversion);
  void polarityInversionPort2(unsigned char portInversion);
  
  void configPort1(unsigned char portDirection);
  void configPort2(unsigned char portDirection);
  
  void configTimeout(unsigned char timeoutFlag);
  
  void readIntFlag();
  
private:

  void initDataBuffers();
  void writeChar(unsigned char registerAddress, unsigned char charData);
  unsigned char readChar(unsigned char registerAddress);
  

  unsigned char _int_pin; // LOW: active.
  unsigned char _port1_data;
  unsigned char _port2_data;
  unsigned char _chipAddress;
};

#endif
