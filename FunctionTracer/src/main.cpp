/*
 * main.cpp
 *
 *  Created on: Apr 10, 2016
 *      Author: micha
 */

#include "FunctionTracer.h"

void test3()
{
   FUNCTION_TRACE
   std::cout << "test3 Ende" << std::endl;
   usleep(3000);
}

void test2()
{
   FUNCTION_TRACE
   test3();
   usleep(2000);
   std::cout << "test2 Ende" << std::endl;
}

void test1()
{
   FUNCTION_TRACE
   test2();
   usleep(1000);
   std::cout << "test Ende" << std::endl;
}

int main() {
   FUNCTION_TRACE
   cout << "!!!Hello raspberry!!!" << endl; // prints !!!Hello raspberry!!!
   test1();
   for(int i=0; i<10000000; i++)
   {
      int j=i*2;
   }
   std::cout << "main Ende" << std::endl;
   return 0;
}

