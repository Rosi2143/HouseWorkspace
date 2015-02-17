#include "Heater.h"
#include "gmock/gmock.h"

class MockHeater : public Heater {
 public:
  MOCK_CONST_METHOD0(getState,
      HeaterState());
  MOCK_METHOD0(toggleState,
      HeaterState());
};
