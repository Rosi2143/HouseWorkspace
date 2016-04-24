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
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>

namespace mpl = boost::mpl;
namespace sc = boost::statechart;

// events
struct EvUpPressed: sc::event<EvUpPressed> {
      EvUpPressed() {
      #ifdef DEBUGOUT
         std::cout << "Button Up pressed!" << std::endl;
      #endif
      }
};
struct EvDownPressed: sc::event<EvDownPressed> {
      EvDownPressed() {
#ifdef DEBUGOUT
         std::cout << "Button Down pressed!" << std::endl;
#endif
      }
};
struct EvReleased: sc::event<EvReleased> {
      EvReleased() {
#ifdef DEBUGOUT
         std::cout << "Button released!" << std::endl;
#endif
         }
};
struct EvFullTimerExpired: sc::event<EvFullTimerExpired> {
      EvFullTimerExpired() {
#ifdef DEBUGOUT
         std::cout << "Timer Full expired!" << std::endl;
#endif
         }
};
struct EvRunTimer: sc::event<EvRunTimer> {
      EvRunTimer() {
#ifdef DEBUGOUT
         std::cout << "RunTimer ended!" << std::endl;
#endif
      }
};

// states
struct Blinds;
struct BlindSomewhere;
struct BlindUp;
struct BlindDown;
struct BlindMovingUp;
struct BlindMovingDown;

// interface to get state values
struct IRunTimer {
      virtual int RunTimer() const = 0;
};

struct IIncreaseRunTimer {
      virtual int IncreaseRunTimer() const = 0;
};

struct IDecreaseRunTimer {
      virtual int DecreaseRunTimer() const = 0;
};

// machine
struct BlindMachine: IRunTimer,
                     IIncreaseRunTimer,
                     IDecreaseRunTimer,
                     sc::state_machine<BlindMachine, Blinds> {
      int RunTimer() const {
         return state_cast<const IRunTimer &>().RunTimer();
      }
      int IncreaseRunTimer() const {
         return state_cast<const IIncreaseRunTimer &>().IncreaseRunTimer();
      }
      int DecreaseRunTimer() const {
         return state_cast<const IDecreaseRunTimer &>().DecreaseRunTimer();
      }
};

struct Blinds: IRunTimer,
               IIncreaseRunTimer,
               IDecreaseRunTimer,
               sc::simple_state<Blinds, BlindMachine, BlindSomewhere> {
   public:
      Blinds() :
            _RunTimer(50) {
#ifdef DEBUGOUT
         std::cout << "entry: Blinds" << std::endl;
#endif
      } // entry
      ~Blinds() {
#ifdef DEBUGOUT
         std::cout << "exit: Blinds" << std::endl;
#endif
         } // exit
      int RunTimer() const {
         return _RunTimer;
      }
      int& RunTimer() {
         return _RunTimer;
      }
      int IncreaseRunTimer() const{
         return _RunTimer++;
      }
      int DecreaseRunTimer() const{
         return 23;//_RunTimer++;
      }

   private:
      int _RunTimer;
};

struct BlindSomewhere: sc::simple_state<BlindSomewhere, Blinds> {
      BlindSomewhere() {
#ifdef DEBUGOUT
         std::cout << "entry: BlindSomewhere" << std::endl;
#endif
         } // entry
      ~BlindSomewhere() {
#ifdef DEBUGOUT
         std::cout << "exit: BlindSomewhere" << std::endl;
#endif
      } // exit

      typedef mpl::list<sc::transition<EvUpPressed, BlindMovingUp>,
            sc::transition<EvDownPressed, BlindMovingDown> > reactions;
};

struct BlindUp: sc::simple_state<BlindUp, Blinds> {
      BlindUp() {
#ifdef DEBUGOUT
         std::cout << "entry: BlindUp" << std::endl;
#endif
         } // entry
      ~BlindUp() {
#ifdef DEBUGOUT
         std::cout << "exit: BlindUp" << std::endl;
#endif
         } // exit
      typedef mpl::list<sc::transition<EvUpPressed, BlindMovingUp>,
            sc::transition<EvDownPressed, BlindMovingDown> > reactions;
      int Do() {
         return context<Blinds>().RunTimer()++;}
      }
;

struct BlindDown: sc::simple_state<BlindDown, Blinds> {
      BlindDown() {
#ifdef DEBUGOUT
         std::cout << "entry: BlindDown" << std::endl;
#endif
         } // entry
      ~BlindDown() {
#ifdef DEBUGOUT
         std::cout << "exit: BlindDown" << std::endl;
#endif
      } // exit
      typedef mpl::list<sc::transition<EvUpPressed, BlindMovingUp>,
            sc::transition<EvDownPressed, BlindMovingDown> > reactions;
};

struct BlindMovingUp: sc::simple_state<BlindMovingUp, Blinds> {
      BlindMovingUp() {
#ifdef DEBUGOUT
         std::cout << "entry: BlindMovingUp" << std::endl;
#endif
      } // entry
      ~BlindMovingUp() {
#ifdef DEBUGOUT
         std::cout << "exit: BlindMovingUp" << std::endl;
#endif
      } // exit
      typedef mpl::list<sc::transition<EvDownPressed, BlindSomewhere>,
            sc::transition<EvReleased, BlindSomewhere>,
            sc::transition<EvFullTimerExpired, BlindUp>,
            sc::custom_reaction< EvRunTimer > > reactions;
      sc::result react( const EvRunTimer & );
};

struct BlindMovingDown: sc::simple_state<BlindMovingDown, Blinds> {
      BlindMovingDown() {
#ifdef DEBUGOUT
         std::cout << "entry: BlindMovingDown" << std::endl;
#endif
         } // entry
      ~BlindMovingDown() {
#ifdef DEBUGOUT
         std::cout << "exit: BlindMovingDown" << std::endl;
#endif
         } // exit
      typedef mpl::list<sc::transition<EvUpPressed, BlindSomewhere>,
            sc::transition<EvReleased, BlindSomewhere>,
            sc::transition<EvFullTimerExpired, BlindDown>,
            sc::custom_reaction< EvRunTimer >> reactions;
      sc::result react( const EvRunTimer & );
};
#endif /* BLINDSTATES_H_ */
