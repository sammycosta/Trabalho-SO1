/**
 * @file Timer.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef TIMER_H
#define TIMER_H

#include <allegro5/allegro.h>

class Timer {

  public:
   Timer(int fps);
   ~Timer();

   void create();

   void startTimer();
   void stopTimer();
   void resetCount();

   void srsTimer(); // stop, reset, start
   
   int getCount() const;
   bool isRunning() const;
   bool isCreated() const;

  private:
   ALLEGRO_TIMER* _timer;
   int _fps;
   
};

#endif
