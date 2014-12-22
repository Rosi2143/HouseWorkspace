/*
 * INode.h
 *
 *  Created on: Dec 19, 2014
 *      Author: micha
 */

#ifndef INODE_H_
#define INODE_H_

#include "wiringPi.h"

class INode{
public:
   virtual wiringPiNodeStruct* getNode() =  0;
   virtual bool readPort(int pin) =  0;
   virtual void writePort(int pin, int value) =  0;
   virtual void configPort(int pin, int mode) =  0;
};

#endif /* INODE_H_ */
