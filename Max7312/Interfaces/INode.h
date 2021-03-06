/*
 * INode.h
 *
 *  Created on: Dec 19, 2014
 *      Author: micha
 */

#ifndef INODE_H_
#define INODE_H_

#include "../../wiringPi_gmock/mocks/wiringPi_Mock.h"

class INode{
public:
   virtual ~INode(){}
   virtual wiringPiNodeStruct* getNode() =  0;
   virtual bool readPort  (int pin) =  0;
   virtual int  writePort (int pin, bool value) =  0;
   virtual int  configPort(int pin, bool mode) =  0;
};

#endif /* INODE_H_ */
