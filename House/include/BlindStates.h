/*
 * BlindStates.h
 *
 *  Created on: Apr 21, 2015
 *      Author: micha
 */

#ifndef BLINDSTATES_H_
#define BLINDSTATES_H_

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>

namespace mpl = boost::mpl;
namespace sc = boost::statechart;

// events
struct EvUpPressed: sc::event<EvUpPressed> {
   EvUpPressed() {
      std::cout << "Button Up pressed!" << std::endl;
   }
};
struct EvDownPressed: sc::event<EvDownPressed> {
   EvDownPressed() {
      std::cout << "Button Down pressed!" << std::endl;
   }
};
struct EvReleased: sc::event<EvReleased> {
   EvReleased() {
      std::cout << "Button released!" << std::endl;
   }
};
struct EvFullTimerExpired: sc::event<EvFullTimerExpired> {
   EvFullTimerExpired() {
      std::cout << "Timer Full expired!" << std::endl;
   }
};

// states
struct BlindSomewhere;
struct BlindUp;
struct BlindDown;
struct BlindMovingUp;
struct BlindMovingDown;

// machine
struct BlindMachine: sc::state_machine<BlindMachine, BlindSomewhere> {
};

struct BlindSomewhere: sc::simple_state<BlindSomewhere, BlindMachine> {
      BlindSomewhere() {
         std::cout << "entry: BlindSomewhere" << std::endl;
      } // entry
      ~BlindSomewhere() {
         std::cout << "exit: BlindSomewhere" << std::endl;
      } // exit

      typedef mpl::list<
         sc::transition< EvUpPressed, BlindMovingUp>,
         sc::transition< EvDownPressed, BlindMovingDown>
      > reactions;
};

struct BlindUp: sc::simple_state<BlindUp, BlindMachine> {
      BlindUp() {
         std::cout << "entry: BlindUp" << std::endl;
      } // entry
      ~BlindUp() {
         std::cout << "exit: BlindUp" << std::endl;
      } // exit
      typedef mpl::list<
         sc::transition< EvUpPressed, BlindMovingUp>,
         sc::transition< EvDownPressed, BlindMovingDown>
      > reactions;
};

struct BlindDown: sc::simple_state<BlindDown, BlindMachine> {
      BlindDown() {
         std::cout << "entry: BlindDown" << std::endl;
      } // entry
      ~BlindDown() {
         std::cout << "exit: BlindDown" << std::endl;
      } // exit
      typedef mpl::list<
         sc::transition< EvUpPressed, BlindMovingUp>,
         sc::transition< EvDownPressed, BlindMovingDown>
      > reactions;
};

struct BlindMovingUp: sc::simple_state<BlindMovingUp, BlindMachine> {
      BlindMovingUp() {
         std::cout << "entry: BlindMovingUp" << std::endl;
      } // entry
      ~BlindMovingUp() {
         std::cout << "exit: BlindMovingUp" << std::endl;
      } // exit
      typedef mpl::list<
         sc::transition< EvDownPressed, BlindSomewhere>,
         sc::transition< EvReleased, BlindSomewhere>,
         sc::transition< EvFullTimerExpired, BlindUp>
      > reactions;
};

struct BlindMovingDown: sc::simple_state<BlindMovingDown, BlindMachine> {
      BlindMovingDown() {
         std::cout << "entry: BlindMovingDown" << std::endl;
      } // entry
      ~BlindMovingDown() {
         std::cout << "exit: BlindMovingDown" << std::endl;
      } // exit
      typedef mpl::list<
         sc::transition< EvUpPressed, BlindSomewhere>,
         sc::transition< EvReleased, BlindSomewhere>,
         sc::transition< EvFullTimerExpired, BlindDown>
      > reactions;
};
#endif /* BLINDSTATES_H_ */
