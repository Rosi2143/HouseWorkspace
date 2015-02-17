#include "iFloor.h"
#include "gmock/gmock.h"

class MockFloor : public iFloor {
 public:
  MOCK_CONST_METHOD0(getNumberOfRooms,
      unsigned int());
  MOCK_CONST_METHOD1(getRoom,
      const Room&(std::string name));
  MOCK_METHOD1(addRoom,
      void(const Room& _Room));
};
