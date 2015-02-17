#include "Floor.h"
#include "gmock/gmock.h"

class MockFloor : public Floor {
 public:
  MOCK_CONST_METHOD0(getNumberOfRooms,
      unsigned int());
  MOCK_CONST_METHOD1(getRoom,
      const Room&(std::string name));
  MOCK_METHOD1(addRoom,
      void(const Room& _Room));
};
