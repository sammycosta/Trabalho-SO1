#include <iostream>
#include "thread.h"
#include "traits.h"

__BEGIN_API

int Thread::_last_id = 0;
Thread *Thread::_running = nullptr;
Thread *Thread::_main = nullptr;

int Thread::switch_context(Thread *prev, Thread *next)
{
  if (prev && next)
  {
    CPU::switch_context(prev->_context, next->_context);
    set_running(next);
    return 1;
  }
  else
  {
    db<Thread>(ERR) << "Erro na troca de contexto!\n";
    return -1;
  }
}

void Thread::thread_exit(int exit_code)
{
  db<Thread>(TRC) << "Thread " << this->id() << " finalizada\n";
  delete (this->context());
  set_running(nullptr); // setar o running pra nulo, mesmo?
}

int Thread::id() { return this->_id; }

__END_API
