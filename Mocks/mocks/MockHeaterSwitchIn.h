#include "iHeater.h"
#include "gmock/gmock.h"

class MockHeaterSwitchIn : public iHeaterSwitchIn {
 public:
  MOCK_METHOD1(=,               operator HeaterSwitchIn&(const HeaterSwitchIn& other));
  MOCK_CONST_METHOD0(getState,   HeaterState());
  MOCK_METHOD0(toggleState,      HeaterState());
};
