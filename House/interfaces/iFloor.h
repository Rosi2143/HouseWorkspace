/*
 * iFloor.h
 *
 *  Created on: Jan 25, 2015
 *      Author: micha
 */

#ifndef IFLOOR_H
#define IFLOOR_H


class iFloor: public Base {
public:
      iFloor(unsigned int Id, std::string Name, const Room* pRoom):Base(Id, Name, pRoom){};
      iFloor(const iBlind& light);  // copy constructor
      virtual ~iFloor();

      // access functions
      virtual unsigned int getVersion() const = 0;
      virtual std::string  getName() const = 0;

      virtual unsigned int getNumberOfRooms() const = 0;
      virtual const Room& getRoom(std::string name) const = 0;

      // handling Switches
      virtual unsigned int getNumberOfSwitches() const = 0;
      virtual const Switch& getSwitch(unsigned int ID) const = 0;

      // construction functions
      virtual void addFloor(const Floor& _Floor) = 0;
protected:
      iFloor(): Base(0, "", nullptr){
         std::cout << "Wrong default constructor iFloor";
      }
};

#endif /* IFLOOR_H */
