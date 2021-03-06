/**************************************************

 file: main.c
 purpose: simple demo that demonstrates the timer-function

 **************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <boost/program_options.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Timer.h"

void timer_handler(int);
void timer_handler2(int);

int var = 0;

int main(int argc, char* argv[]) {
   // Declare the supported options.
   int verbose = 0;
   boost::program_options::options_description desc("Allowed options");
   desc.add_options()("help", "produce help message")("verbose",
         boost::program_options::value<int>(&verbose)->default_value(0),
         "set verbose level");

   boost::mutex io_mutex;
   boost::asio::io_service io_service;

   boost::program_options::variables_map CommandLineOptions;
   boost::program_options::store(
         boost::program_options::parse_command_line(argc, argv, desc),
         CommandLineOptions);
   boost::program_options::notify(CommandLineOptions);

   if (CommandLineOptions.count("help")) {
      std::cout << "tests the timer and command line option boost library\n";
      return 1;
   }

   std::cout << verbose;

   Timer timer(io_service, io_mutex, verbose);
   std::vector<int> times;
   times.push_back(1000);
   times.push_back(5000);
   times.push_back(4000);
   times.push_back(20000);
   times.push_back(50000);
   times.push_back(500);

   int timerid = 100;
   for (int time : times) {
      if (0
            != timer.start_timer(time /*time in ms */, timerid++ /* TimerId */,
                  &timer_handler /* HandlerFunction */)) {
         printf("\n timer error\n");
         return (1);
      }
      if (0
            != timer.start_timer(time + 1000 /*time in ms */,
                  100 + timerid++ /* TimerId */,
                  &timer_handler2 /* HandlerFunction */)) {
         printf("\n timer error\n");
         return (1);
      }
   }

   boost::posix_time::ptime t_now(
         boost::posix_time::microsec_clock::local_time()
               + boost::posix_time::milliseconds(7000));
   if (0
         != timer.start_timer(t_now /*time in ms */,
               200 + timerid++ /* TimerId */,
               &timer_handler /* HandlerFunction */)) {
      printf("\n timer error\n");
      return (1);
   }

   printf("\npress ctl-c to quit.\n");

   while (1) {
      if (var > 2 * times.size() - 1) {
         break;
      }
   }

   printf("\ndone. Quitting.\n");

   timer.stop_timer();

   return (0);
}

void timer_handler(int arg) {
   printf("timer: var is %i -- arg is %i\n", var++, arg);
   std::cout
         << boost::posix_time::to_simple_string(
               boost::posix_time::microsec_clock::local_time()) << std::endl;
}

void timer_handler2(int arg) {
   printf("\ttimer2: var2 is %i -- arg2 is %i\n", var++, arg);
   std::cout << "\t"
         << boost::posix_time::to_simple_string(
               boost::posix_time::microsec_clock::local_time()) << std::endl;
}
