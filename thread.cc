#include <iostream>
#include "thread.h"
#include "traits.h"

__BEGIN_API

int Thread::_last_id = 0;
Thread *Thread::_running = nullptr;

int Thread::switch_context(Thread *prev, Thread *next)
{
  if (prev && next)
  {
    db<Thread>(TRC) << "Thread::switch_context() da Thread " << prev->id() << " para a Thread " << next->id() << "\n";

    CPU::switch_context(prev->_context, next->_context);
    set_running(next);
    return 0;
  }
  else
  {
    db<Thread>(ERR) << "Erro em Thread::switch_context()\n";
    return -1;
  }
}

void Thread::thread_exit(int exit_code)
{
  db<Thread>(TRC) << "Thread::thread_exit() chamado para a Thread" << this->id() << "\n";
  delete (this->context());
}

int Thread::id() { return this->_id; }

__END_API
