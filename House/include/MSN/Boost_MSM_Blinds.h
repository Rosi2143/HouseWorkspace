/*
 * Boost_MSM_SM.h
 *
 *  Created on: Mar 24, 2016
 *      Author: micha
 */

#ifndef BOOST_MSM_BLIND_H_
#define BOOST_MSM_BLIND_H_

#include <vector>
#include <iostream>

#include <boost/phoenix/phoenix.hpp>
#include <boost/mpl/string.hpp>

// add phoenix support in eUML
#define BOOST_MSM_EUML_PHOENIX_SUPPORT
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/euml/euml.hpp>
#include <boost/msm/front/euml/stl.hpp>

using namespace std;
using namespace boost::msm::front::euml;
namespace msm = boost::msm;
namespace mpl= boost::mpl;
using namespace boost::phoenix;

// entry/exit/action/guard logging functors
#include "logging_functors.h"

namespace  BlindsSm// Concrete FSM implementation
{
enum BlindTypeEnum {
   BLIND_WINDOW = 0, BLIND_DOOR = 1
};

// **********************
// class attributes
// **********************
struct MsmData {
      std::string m_BlindName;
      BlindTypeEnum m_BlindType;
      int m_BlindCounter;
};

// **********************
// events
// **********************
BOOST_MSM_EUML_DECLARE_ATTRIBUTE(std::string,m_name)
BOOST_MSM_EUML_ATTRIBUTES((attributes_ << m_name ), set_name_attr)
BOOST_MSM_EUML_EVENT_WITH_ATTRIBUTES(SetName,set_name_attr)

BOOST_MSM_EUML_DECLARE_ATTRIBUTE(BlindTypeEnum,m_type)
BOOST_MSM_EUML_ATTRIBUTES((attributes_ << m_type ), set_type_attr)
BOOST_MSM_EUML_EVENT_WITH_ATTRIBUTES(SetType,set_type_attr)

BOOST_MSM_EUML_EVENT(UpPressed)
BOOST_MSM_EUML_EVENT(DownPressed)
BOOST_MSM_EUML_EVENT(Release)
BOOST_MSM_EUML_EVENT(RunTimer)
BOOST_MSM_EUML_EVENT(FullTimerExpired)

// **********************
// Concrete FSM implementation
// The list of FSM states
// **********************

#ifndef MSM_STATE_BLINDSOMEWHERE
// **********************
// BlindSomeWhere
// **********************
// entry and exit actions as phoenix functions
struct BlindSomeWhere_entry_impl {
      typedef void result_type;
      void operator()() {
         cout << "entering: BlindSomeWhere" << endl;
      }
};
boost::phoenix::function<BlindSomeWhere_entry_impl> BlindSomeWhere_entry;
struct BlindSomeWhere_exit_impl {
      typedef void result_type;
      void operator()() {
         cout << "leaving: BlindSomeWhere" << endl;
      }
};
boost::phoenix::function<BlindSomeWhere_exit_impl> BlindSomeWhere_exit;

// a state using phoenix for entry/exit actions
BOOST_MSM_EUML_STATE(( BlindSomeWhere_entry(),BlindSomeWhere_exit() ), BlindSomeWhere)
#endif

#ifndef MSM_STATE_BLINDUP
// **********************
// BlindUp
// **********************
// entry and exit actions as phoenix functions
struct BlindUp_entry_impl {
      typedef void result_type;
      void operator()() {
         cout << "entering: BlindUp" << endl;
      }
};
boost::phoenix::function<BlindUp_entry_impl> BlindUp_entry;
struct BlindUp_exit_impl {
      typedef void result_type;
      void operator()() {
         cout << "leaving: BlindUp" << endl;
      }
};
boost::phoenix::function<BlindUp_exit_impl> BlindUp_exit;

// a state using phoenix for entry/exit actions
BOOST_MSM_EUML_STATE(( BlindUp_entry(),BlindUp_exit() ), BlindUp)
#endif

#ifndef MSM_STATE_BLINDDOWN
// **********************
// BlindDown
// **********************
// entry and exit actions as phoenix functions
struct BlindDown_entry_impl {
      typedef void result_type;
      void operator()() {
         cout << "entering: BlindDown" << endl;
      }
};
boost::phoenix::function<BlindDown_entry_impl> BlindDown_entry;
struct BlindDown_exit_impl {
      typedef void result_type;
      void operator()() {
         cout << "leaving: BlindDown" << endl;
      }
};
boost::phoenix::function<BlindDown_exit_impl> BlindDown_exit;

// a state using phoenix for entry/exit actions
BOOST_MSM_EUML_STATE(( BlindDown_entry(),BlindDown_exit() ), BlindDown)
#endif

#ifndef MSM_STATE_BLINDMOVINGUP
// **********************
// BlindMovingUp
// **********************
// entry and exit actions as phoenix functions
struct BlindMovingUp_entry_impl {
      typedef void result_type;
      void operator()() {
         cout << "entering: BlindMovingUp" << endl;
      }
};
boost::phoenix::function<BlindMovingUp_entry_impl> BlindMovingUp_entry;
struct BlindMovingUp_exit_impl {
      typedef void result_type;
      void operator()() {
         cout << "leaving: BlindMovingUp" << endl;
      }
};
boost::phoenix::function<BlindMovingUp_exit_impl> BlindMovingUp_exit;

// a state using phoenix for entry/exit actions
BOOST_MSM_EUML_STATE(( BlindMovingUp_entry(),BlindMovingUp_exit() ), BlindMovingUp)
#endif

#ifndef MSM_STATE_BLINDMOVINGDOWN
// **********************
// BlindMovingDown
// **********************
// entry and exit actions as phoenix functions
struct BlindMovingDown_entry_impl {
      typedef void result_type;
      void operator()() {
         cout << "entering: BlindMovingDown" << endl;
      }
};
boost::phoenix::function<BlindMovingDown_entry_impl> BlindMovingDown_entry;
struct BlindMovingDown_exit_impl {
      typedef void result_type;
      void operator()() {
         cout << "leaving: BlindMovingDown" << endl;
      }
};
boost::phoenix::function<BlindMovingDown_exit_impl> BlindMovingDown_exit;

// a state using phoenix for entry/exit actions
BOOST_MSM_EUML_STATE(( BlindMovingDown_entry(),BlindMovingDown_exit() ), BlindMovingDown)
#endif

// an action taking the fsm as argument and sending it a new event
struct process_RunTimer_impl {
      typedef void result_type;

      template<class Fsm>
      void operator()(Fsm& fsm) {
         cout << "RunTimer expired" << endl;
         fsm.process_event(FullTimerExpired);
      }
};
// it is also possible to use BOOST_PHOENIX_ADAPT_CALLABLE to avoid defining a global variable
BOOST_PHOENIX_ADAPT_CALLABLE(process_RunTimer, process_RunTimer_impl, 1)

// attributes of statemachine
BOOST_MSM_EUML_DECLARE_ATTRIBUTE(std::string,Blind_name)
BOOST_MSM_EUML_DECLARE_ATTRIBUTE(int,Blind_MoveCount)
BOOST_MSM_EUML_DECLARE_ATTRIBUTE(BlindTypeEnum,Blind_type)

// transition table. Actions and guards are written as phoenix functions
BOOST_MSM_EUML_TRANSITION_TABLE((
//an action without arguments
      BlindUp == BlindMovingUp + FullTimerExpired,

      BlindMovingUp == BlindDown + UpPressed,
      BlindMovingUp == BlindSomeWhere + UpPressed,
      BlindMovingUp == BlindUp + UpPressed,
      BlindMovingUp + RunTimer /(fsm_(Blind_MoveCount) += 1),
      //  +------------------------------------------------------------------------------+
      BlindSomeWhere + SetName/(fsm_(Blind_name) = event_(m_name)),
      BlindSomeWhere + SetType/(fsm_(Blind_type) = event_(m_type)),
      //  +------------------------------------------------------------------------------+
      BlindSomeWhere == BlindMovingUp + Release,
      BlindSomeWhere == BlindMovingUp + DownPressed,
      BlindSomeWhere == BlindMovingDown + Release,
      BlindSomeWhere == BlindMovingDown + UpPressed,
      //  +------------------------------------------------------------------------------+
      BlindMovingDown == BlindDown + DownPressed,
      BlindMovingDown == BlindSomeWhere + DownPressed,
      BlindMovingDown == BlindUp + DownPressed,
      BlindMovingDown + RunTimer /(fsm_(Blind_MoveCount) -= 1),
      //  +------------------------------------------------------------------------------+
      BlindDown == BlindMovingDown + FullTimerExpired
      //  +------------------------------------------------------------------------------+
      ), transition_table)

// create a state machine "on the fly"
BOOST_MSM_EUML_DECLARE_STATE_MACHINE(( transition_table,//STT
      init_ << BlindSomeWhere,// Init State
//      fsm_(m_name)=String_<mpl::string<'Test ','FSM'> >(),// Entry
//      fsm_(m_type)=Int_<1>(),
      no_action,// Entry
      no_action,// Exit
      attributes_ << Blind_name << Blind_type << Blind_MoveCount,// Attributes
      configure_ << no_configure_,// configuration
      Log_No_Transition// no_transition handler
      ), blind_//fsm name
   )

// choice of back-end
typedef msm::back::state_machine<blind_> blind;

//
// Testing utilities.
//
static char const* const state_names[] = { "BlindMovingUp", "BlindDown", "BlindSomeWhere", "BlindUp", "BlindMovingDown"};
void pstate(blind const& p) {
   std::cout << " -> " << p.current_state()[0] << "-"<< state_names[p.current_state()[0]] << std::endl;
   std::cout << " -> " << p.get_attribute(m_name) << "-"/*<< p.get_attribute(m_type)*/  << std::endl;
}
}

#endif /* BOOST_MSM_BLIND_H_ */
