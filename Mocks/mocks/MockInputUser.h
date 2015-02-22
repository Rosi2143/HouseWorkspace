#include "iInputUser.h"
#include "gmock/gmock.h"

class MockInputUser: public iInputUser {
   public:
      MockInputUser(unsigned int Id, std::string Name) :
            iInputUser(Id, Name), test(23) {
      }
      MockInputUser(const MockInputUser& other) :
            iInputUser(other._Id, other._Name), test(other.test) {
      }
      ~MockInputUser() {
      }
      MOCK_METHOD1(OnPress, void(int time));
      MOCK_METHOD1(OnRelease, void(int time));
      MOCK_METHOD1(OnShortPress, void(int time));
      MOCK_METHOD1(OnLongPress, void(int time));
      MOCK_METHOD1(OnVeryLongPress, void(int time));
      MOCK_METHOD1(OnBlocked, void(int time));
      int test;
   };
