// Copyright 2010 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// statechart: http://www.boost.org/doc/libs/1_60_0/libs/msm/doc/images/SimpleTutorial.jpg
#include "Boost_MSM_Blinds.h"

using namespace BlindsSm;

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::StrCaseEq;

// statechart: http://www.boost.org/doc/libs/1_60_0/libs/msm/doc/images/SimpleTutorial.jpg

#ifdef COLLAPSE
void test()
{
   // statechart: http://www.boost.org/doc/libs/1_60_0/libs/msm/doc/images/SimpleTutorial.jpg
   blind _blind;
   // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
   _blind.start();
   pstate(_blind);
   // go to MovingUp
   _blind.process_event(UpPressed);
   pstate(_blind);
   // go to Up
   _blind.process_event(FullTimerExpired);
   pstate(_blind);
   // GoTo MovingDown
   _blind.process_event(DownPressed);
   pstate(_blind);
   // go to down
   _blind.process_event(FullTimerExpired);
   pstate(_blind);
}

int main() {
test();
return 0;
}
#else

TEST(House, TraceLevel0_inactive) {
   blind _blind;
   _blind.start();
   pstate(_blind);
   ASSERT_EQ(NULL, 0);
}
#endif
