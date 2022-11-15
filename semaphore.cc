#include <iostream>
#include "traits.h"
#include "semaphore.h"

__BEGIN_API

int Semaphore::finc(volatile int &number)
{
  // não sei sei se é assim
  db<Semaphore>(TRC) << "finc chamado\n";
  int one = 1;
  /*__asm__("lock;"
          "xadd %%ebx, %%eax"
          : "=a"(number)
          : "a"(number), "b"(one)
          : "memory"); */
  __asm__("lock;"
          "xadd %[first], %[second]"
          : [first] "+r"(number)
          : [second] "r"(one));
  return number;
}

int Semaphore::fdec(volatile int &number)
{
  // não sei sei se é assim
  db<Semaphore>(TRC) << "fdec chamado\n";

  int minus_one = -1;
  // __asm__("lock;"
  //         "xadd %%ebx, %%eax"
  //         : "=a"(number)
  //         : "a"(number), "b"(minus_one)
  //         : "memory");
  __asm__("lock;"
          "xadd %[first], %[second]"
          : [first] "+r"(number)
          : [second] "r"(minus_one));

  return number;
}

void Semaphore::p()
{
  // leitura precisa ser atômica?
  db<Semaphore>(TRC) << "p chamado\n";
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
  db<Semaphore>(TRC) << "v chamado\n";
  finc(this->value);
  wakeup();
}

void Semaphore::sleep()
{
  db<Semaphore>(TRC) << "sleep chamado\n";
  Thread *to_sleep = Thread::sleep();
  this->sleep_queue.insert(to_sleep->get_link());
  Thread::yield(); // Pensamentos
}

void Semaphore::wakeup()
{
  db<Semaphore>(TRC) << "wakeup chamado\n";
  if (!this->sleep_queue.empty())
  {
    Thread *next = this->sleep_queue.remove_head()->object();
    Thread::wakeup(next);
  }
}

void Semaphore::wakeup_all()
{
  db<Semaphore>(TRC) << "wakeup_all chamado\n";
  int size = this->sleep_queue.size();
  for (int i = 0; i < size; i++)
  {
    wakeup();
  }
}

Semaphore::~Semaphore()
{
  wakeup_all();
}

__END_API