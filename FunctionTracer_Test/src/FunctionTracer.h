/*
 * FunctionTace.h
 *
 *  Created on: Apr 10, 2016
 *      Author: micha
 */

#ifndef FUNCTIONTRACER_H_
#define FUNCTIONTRACER_H_

#include <string>
#include <iostream>
#include <memory>

#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

#include <map>
#include <mutex> //cpp11
#include <iostream>

#include <time.h>

void SetTraceLevel(int level);

template<class K, class V, class Compare = std::less<K>,
      class Allocator = std::allocator<std::pair<const K, V> > >
class guarded_map {
   private:
      std::map<K, V, Compare, Allocator> _map;
      std::mutex _m;

   public:
      void set(K key, V value) {
         std::lock_guard < std::mutex > lk(this->_m);
         this->_map[key] = value;
      }

      V & get(K key) {
         std::lock_guard < std::mutex > lk(this->_m);
         return this->_map[key];
      }

      bool empty() {
         std::lock_guard < std::mutex > lk(this->_m);
         return this->_map.empty();
      }

      // other public methods you need to implement
};

class FunctionTracer {
   public:
      FunctionTracer(std::string name, int Counter) :
            _sFunctionName(name), _EntryTraceDone(false), _ExitTraceDone(false), _Counter(
                  Counter){
         Constructor();
      }
      ~FunctionTracer() {
         Destructor();
      }

#ifdef UNIT_TEST
      public:
#else
   protected:
#endif
      std::string _sFunctionName;
      std::string _sIndent;
      bool _EntryTraceDone, _ExitTraceDone;
      int _Counter;
      int _ThreadId;
      int _Clock_EntryTime;
      timespec _Entry_Cpu_Time, _Entry_Clock_Time;
      int _Cpu_Time_Used_ms, _Clock_Time_Used_ms;

      void Constructor();
      void Destructor();
};

class Counter {
   public:
      Counter();
      ~Counter() {Destructor();};
      int getCounter(){return _Counter;}
#ifdef UNIT_TEST
      public:
#else
      private:
#endif
      int _Counter;
      int _ThreadId;

      void Destructor();
};

//#define FUNCTION_TRACE FunctionTracer fct(__FUNCTION__);

extern guarded_map<int, int> FunctionTraceCounter;
extern int FunctionTrace_TraceLevel;
#define FUNCTION_TRACE_TEST(ARG)  unique_ptr<FunctionTracer> p ## ARG; \
                        Counter counter ## ARG; \
                        int CounterValue ## ARG = counter ## ARG.getCounter(); \
                        if (CounterValue ## ARG <= FunctionTrace_TraceLevel){ \
                           p ## ARG = unique_ptr<FunctionTracer> (new FunctionTracer(__FUNCTION__, CounterValue ## ARG)); \
                        }
#define FUNCTION_TRACE_TEST_END(ARG)  p ## ARG->Destructor(); \
                                      counter ## ARG.Destructor();

#define FUNCTION_TRACE  FUNCTION_TRACE_TEST(0)

#endif /* FUNCTIONTRACER_H_ */
