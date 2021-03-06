#include <iSwitchIn.h>
#include "gmock/gmock.h"

class MockBaseSwitchIn: public IBaseSwitchIn {
   public:
      MOCK_METHOD0(OnPress, void());
      MOCK_METHOD0(OnRelease, void());
      MOCK_CONST_METHOD0(getState, SwitchInState());
      MOCK_METHOD2(addAction, void(const SwitchInState& state, t_SwitchInActionFunction Function));
   };

class MockSwitchIn: public iSwitchIn {
   public:
      MOCK_METHOD1(=, operator iSwitchIn&(const iSwitchIn& other));
      MOCK_METHOD0(OnPress, void());
      MOCK_METHOD0(OnRelease, void());
      MOCK_CONST_METHOD0(getState, SwitchInState());
      MOCK_CONST_METHOD0(getRoom, const iRoom*());
      MOCK_CONST_METHOD0(getActionMap, const ActionFunctionMap());
      MOCK_METHOD2(addAction, void(const SwitchInState& state, t_SwitchInActionFunction Function));
   };
