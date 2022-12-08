#include <iostream>
#include "traits.h"
#include "semaphore.h"

__BEGIN_API

int Semaphore::finc(volatile int &number)
{
  db<Semaphore>(TRC) << "finc chamado\n";

  return CPU::finc(number);
}

int Semaphore::fdec(volatile int &number)
{
  db<Semaphore>(TRC) << "fdec chamado\n";

  return CPU::fdec(number);
}

void Semaphore::p()
{
  db<Semaphore>(TRC) << "p chamado\n";
  if (fdec(this->value) < 1)
  {
    sleep();
  }
}

void Semaphore::v()
{
  db<Semaphore>(TRC) << "v chamado\n";
  if (finc(this->value) < 0)
  {
    wakeup();
  }
}

void Semaphore::sleep()
{
  db<Semaphore>(TRC) << "sleep chamado\n";
  Thread *to_sleep = Thread::sleep();
  this->sleep_queue.insert(to_sleep->get_link());
  Thread::yield();
}

void Semaphore::wakeup()
{
  db<Semaphore>(TRC) << "wakeup chamado\n";
  if (!this->sleep_queue.empty())
  {
    Thread *next = this->sleep_queue.remove_head()->object();
    Thread::wakeup(next);
    Thread::yield();
  }
}

void Semaphore::wakeup_all()
{
  db<Semaphore>(TRC) << "wakeup_all chamado\n";
  int size = this->sleep_queue.size();
  for (int i = 0; i < size; i++)
  {
    if (!this->sleep_queue.empty())
    {
      Thread *next = this->sleep_queue.remove_head()->object();
      Thread::wakeup(next);
    }
  }
  Thread::yield();
}

Semaphore::~Semaphore()
{
  wakeup_all();
}

__END_API