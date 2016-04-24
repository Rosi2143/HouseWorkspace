/*
<1<a * BlindStates.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: micha
 *
 *  Description see: http://www.boost.org/doc/libs/1_51_0/libs/statechart/doc/tutorial.html
 */

#include "BlindStates.h"

sc::result BlindMovingUp::react( const EvRunTimer & )
{
//  int& re = context< Blinds >().RunTimer();
  context< Blinds >().IncreaseRunTimer();
//  int& re2 = context< Blinds >().RunTimer();
  return discard_event();
}

sc::result BlindMovingDown::react( const EvRunTimer & )
{
//  int& re = context< Blinds >().RunTimer();
  context< Blinds >().DecreaseRunTimer();
//  int& re2 = context< Blinds >().RunTimer();
  return discard_event();
}
