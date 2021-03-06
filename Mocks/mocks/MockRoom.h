#include <iSwitchIn.h>
#include "iRoom.h"
#include "gmock/gmock.h"

class MockRoom : public iRoom {
 public:
   MockRoom(unsigned int Id, std::string Name, const iFloor* pFloor) : iRoom(Id, Name, pFloor){}
   ~MockRoom(){}
//   MOCK_CONST_METHOD1(getLight,      const iLight*(std::string Name));
//   MOCK_CONST_METHOD1(getHeater,     const iHeater*(std::string Name));
//   MOCK_CONST_METHOD1(getBlind,      const iBlind*(std::string Name));
   MOCK_CONST_METHOD1(getSwitchIn,   const iSwitchIn*(std::string Name));
   MOCK_CONST_METHOD0(getTimeRef,    const iTime*());
//   MOCK_METHOD1(addLight,            void(const iLight& Light));
//   MOCK_METHOD1(addHeater,           void(const iHeater& Heater));
//   MOCK_METHOD1(addBlind,            void(const iBlind& Blind));
   MOCK_METHOD1(addSwitchIn,         void(const iSwitchIn& Switch));
   MOCK_CONST_METHOD0(getNumberOfSwitches, unsigned int());
};
