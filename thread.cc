#include <iostream>
#include "thread.h"
#include "traits.h"

__BEGIN_API

int Thread::switch_context(Thread *prev, Thread *next)
{
  if (prev && next)
  {
    CPU::switch_context(prev->_context, next->_context);
  }
  else
  {
    return -1; // Erro. Opção: Try/Catch?
  }
}

void Thread::thread_exit(int exit_code)
{
  delete (this->context());
  // como retornar o controle???
}

int Thread::id() { return this->_id; }

__END_API
