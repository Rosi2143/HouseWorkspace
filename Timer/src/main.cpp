/**************************************************

file: main.c
purpose: simple demo that demonstrates the timer-function

**************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Timer.h"


void timer_handler(int);

int var=0;
Timer timer;

int main(void)
{
  if(0 != timer.start_timer(1000 /*time in ms */,
                            1 /* TimerId */,
                            &timer_handler /* HandlerFunction */))
  {
    printf("\n timer error\n");
    return(1);
  }

  printf("\npress ctl-c to quit.\n");

  while(1)
  {
    if(var > 50)
    {
      break;
    }
  }

  timer.stop_timer();

  return(0);
}

void timer_handler(int arg)
{
  printf("timer: var is %i\n", var++);
}
