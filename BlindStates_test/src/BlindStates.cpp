/*
 * BlindStates.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: micha
 *
 *  Description see: http://www.boost.org/doc/libs/1_51_0/libs/statechart/doc/tutorial.html
 */

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <iostream>

namespace sc = boost::statechart;

// events
struct EvUpPressed: sc::event<EvUpPressed> {
};
struct EvDownPressed: sc::event<EvDownPressed> {
};
struct EvReleased: sc::event<EvReleased> {
};
struct EvFullTimerExpired: sc::event<EvFullTimerExpired> {
};

struct BlindSomewhere;
struct BlindUp;
struct BlindDown;
struct BlindMovingUp;
struct BlindMovingDown;

struct BlindMachine: sc::state_machine<BlindMachine, BlindSomewhere> {
};

struct BlindSomewhere: sc::simple_state<BlindSomewhere, BlindMachine> {
      BlindSomewhere() {
      } // entry
      ~BlindSomewhere() {
      } // exit

      typdef mpl::list<
         typedef sc::transition< EvUpPressed, BlindMovingUp>,
         typedef sc::transition< EvDownPressed, BlindMovingDown>
      > reactions;
};

struct BlindUp: sc::simple_state<BlindUp, BlindMachine> {
      BlindUp() {
      } // entry
      ~BlindUp() {
      } // exit
      typdef mpl::list<
         typedef sc::transition< EvUpPressed, BlindMovingUp>,
         typedef sc::transition< EvDownPressed, BlindMovingDown>
      > reactions;
};

struct BlindDown: sc::simple_state<BlindDown, BlindMachine> {
      BlindDown() {
      } // entry
      ~BlindDown() {
      } // exit
      typdef mpl::list<
         typedef sc::transition< EvUpPressed, BlindMovingUp>,
         typedef sc::transition< EvDownPressed, BlindMovingDown>
      > reactions;
};

struct BlindMovingUp: sc::simple_state<BlindMovingUp, BlindMachine> {
      BlindMovingUp() {
      } // entry
      ~BlindMovingUp() {
      } // exit
      typdef mpl::list<
         typedef sc::transition< EvDownPressed, BlindSomewhere>,
         typedef sc::transition< EvReleased, BlindSomewhere>,
         typedef sc::transition< EvFullTimerExpired, BlindUp>
      > reactions;
};

struct BlindMovingDown: sc::simple_state<BlindMovingDown, BlindMachine> {
      BlindMovingDown() {
      } // entry
      ~BlindMovingDown() {
      } // exit
      typdef mpl::list<
         typedef sc::transition< EvUpPressed, BlindSomewhere>,
         typedef sc::transition< EvReleased, BlindSomewhere>,
         typedef sc::transition< EvFullTimerExpired, BlindDown>
      > reactions;
};