//============================================================================
// Name        : FunctionTracer.cpp
// Author      : Michael Rossner
// Version     :
// Copyright   : LGPL2
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "FunctionTracer.h"

guarded_map<int, int> FunctionTraceCounter;
int FunctionTrace_TraceLevel = 0;

void SetTraceLevel(int level){
   FunctionTrace_TraceLevel = level;
}
void FunctionTracer::Constructor(){
   _ThreadId = getpid();
   _sIndent = std::string((size_t)(_Counter*2), '-');
   #ifndef UNIT_TEST
      std::cout << _sIndent << "FunctionTracer Entry:" << _sFunctionName << " - ThreadId = " << _ThreadId << " - CallDepth = " << _Counter << std::endl;
   #endif
   if(-1 == clock_gettime(CLOCK_MONOTONIC_COARSE, &_Entry_Clock_Time)) {
      perror( "clock gettime CLOCK_MONOTONIC_COARSE" );
   }
   if (-1 == clock_gettime(CLOCK_THREAD_CPUTIME_ID, &_Entry_Cpu_Time)) {
      perror( "clock gettime CLOCK_THREAD_CPUTIME_ID" );
   }
   _EntryTraceDone = true;

}
void FunctionTracer::Destructor(){
   timespec Cpu_Time, Clock_Time;
   if (-1 == clock_gettime(CLOCK_MONOTONIC_COARSE, &Clock_Time)){
      perror("clock_gettime CLOCK_MONOTONIC_COARSE");
   }
   if (-1 == clock_gettime(CLOCK_THREAD_CPUTIME_ID, &Cpu_Time)){
      perror("clock_gettime CLOCK_THREAD_CPUTIME_ID");
   }
   _Clock_Time_Used_ms = (Clock_Time.tv_sec - _Entry_Clock_Time.tv_sec) * 1000 + ( Clock_Time.tv_nsec - _Entry_Clock_Time.tv_nsec) / 1000 / 1000;
   _Cpu_Time_Used_ms = ( Cpu_Time.tv_sec - _Entry_Cpu_Time.tv_sec) * 1000 + ( Cpu_Time.tv_nsec - _Entry_Cpu_Time.tv_nsec) / 1000 / 1000;
   #ifndef UNIT_TEST
      std::cout << _sIndent << "FunctionTracer Exit :" << _sFunctionName << " - ThreadId = " << _ThreadId << " - CallDepth = " << _Counter << std::endl;
      std::cout << _sIndent << "Function used CPU for " << _Cpu_Time_Used_ms << "ms" << std::endl;
      std::cout << _sIndent << "Function Duration     " << _Clock_Time_Used_ms  << "ms" << std::endl;
   #endif
   _ExitTraceDone = true;
}

Counter::Counter() {
   _ThreadId = getpid();
   _Counter = FunctionTraceCounter.get(_ThreadId);
   _Counter++;
   FunctionTraceCounter.set(_ThreadId, _Counter);
}

void Counter::Destructor() {
   _Counter--;
   FunctionTraceCounter.set(_ThreadId, _Counter);
}
