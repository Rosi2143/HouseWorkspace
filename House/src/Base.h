/*
 * Base.h
 *
 *  Created on: Feb 12, 2015
 *      Author: micha
 */

#ifndef SRC_BASE_H_
#define SRC_BASE_H_


class Base
{
   public:
      Base(unsigned int _Id, std::string _Name):Name(_Name), Id(_Id){};
      Base( const Base &_base):Name(_base.getName(), Id(_base.getId())){}  // copy constructor
      virtual ~Base();

      // access functions
      std::string getName() const {
         return Name;
      }
      unsigned int getId() const {
         return Id;
      }

   protected:
      std::string Name;
      unsigned int Id;

};


#endif /* SRC_BASE_H_ */