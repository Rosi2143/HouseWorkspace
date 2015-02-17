#include "iHeater.h"
#include "gmock/gmock.h"

class MockHeater : public Heater {
 public:
  MOCK_METHOD1(=,               operator iHeater&(const iHeater& other));
  MOCK_CONST_METHOD0(getState,   HeaterState());
  MOCK_METHOD0(toggleState,      HeaterState());
};
