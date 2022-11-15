#include <iostream>
#include "traits.h"
#include "semaphore.h"

__BEGIN_API

int Semaphore::finc(volatile int &number)
{
  // não sei sei se é assim
  asm("lock xadd %%ebx, %%eax"
      : "=a"(number)
      : "a"(number), "b"(1));
}

int Semaphore::fdec(volatile int &number)
{
  // não sei sei se é assim
  asm("lock xadd %%ebx, %%eax"
      : "=a"(number)
      : "a"(number), "b"(-1));
}

void Semaphore::p()
{
  // leitura precisa ser atômica?
  if (this->value > 0)
  {
    fdec(this->value);
  }
  else
  {
    sleep();
  }
}

void Semaphore::v()
{
  finc(this->value);
  wakeup();
}

void Semaphore::sleep()
{
  Thread *to_sleep = Thread::sleep();
  this->sleep_queue.insert(&(to_sleep->get_link()));
}

void Semaphore::wakeup()
{
  if (!this->sleep_queue.empty())
  {
    Thread *next = this->sleep_queue.remove_head()->object();
    Thread::wakeup(next);
  }
}

void Semaphore::wakeup_all()
{
  int size = this->sleep_queue.size();
  for (int i = 0; i < size; i++)
  {
    wakeup();
  }
}

__END_API