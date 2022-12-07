/**
 * @file Timer.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Timer.h"
#include <iostream>
#include <stdexcept>

Timer::Timer(int fps) : _timer(NULL), _fps(fps) {

}

Timer::~Timer() {
   if (_timer != NULL) {
      al_destroy_timer(_timer);
      //std::cout << "timer deleted\n";      
   }
}

void Timer::create() {
   if ((_timer = al_create_timer(1.0 / _fps)) == NULL) {
      std::cout << "error, timer could not be created\n";
      exit(1);
   }
}

void Timer::startTimer() {
   al_start_timer(_timer);
}

void Timer::stopTimer() {
   al_stop_timer(_timer);
}

void Timer::resetCount() {
   al_set_timer_count(_timer, 0);
}

void Timer::srsTimer() {
   stopTimer();
   resetCount();
   startTimer();
}


int Timer::getCount() const {
   return al_get_timer_count(_timer);
}

bool Timer::isRunning() const {
   return al_get_timer_started(_timer);
}

bool Timer::isCreated() const {
   if (_timer == NULL)
      return false;
   return true;
}
