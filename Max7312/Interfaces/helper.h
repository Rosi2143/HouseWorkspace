/*
 * helper.h
 *
 *  Created on: Dec 20, 2014
 *      Author: micha
 */

#ifndef HELPER_H_
#define HELPER_H_

#define SETBIT(x,y)    (x |= (1 << y))     //Set bit y in byte x
#define CLEARBIT(x,y)  (x &= (~(1 << y) )) //Clear bit y in byte x
#define TOGGLEBIT(x,y) (x ^= (1 << y))     //Toggle bit y in byte x
#define CHECKBIT(x,y)  (x &  (1 << y))     //True if bit y of byte x=1

#endif /* HELPER_H_ */
