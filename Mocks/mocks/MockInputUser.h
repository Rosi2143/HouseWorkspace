#include "iInputUser.h"
#include "gmock/gmock.h"

class MockInputUser: public iInputUser {
   public:
      MockInputUser(unsigned int Id, std::string Name, iRoom* pRoom) :
            iInputUser(Id, Name, pRoom) {
      }
      MockInputUser(const MockInputUser& other) :
            iInputUser(other._Id, other._Name, other._pRoom) {
      }
      ~MockInputUser() {
      }
      MOCK_METHOD1(OnPress, void(int time));
      MOCK_METHOD1(OnRelease, void(int time));
      MOCK_METHOD1(OnShortPress, void(int time));
      MOCK_METHOD1(OnLongPress, void(int time));
      MOCK_METHOD1(OnVeryLongPress, void(int time));
      MOCK_METHOD1(OnBlocked, void(int time));
   };
