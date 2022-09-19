#include <iostream>
#include "thread.h"
#include "traits.h"

__BEGIN_API

int Thread::_last_id = -1;
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
    return -1; // Erro. Opção: Try/Catch?
  }
}

void Thread::thread_exit(int exit_code)
{
  db<Thread>(TRC) << "Thread " << this->id() << " finalizada\n";
  switch_context(this, main());
  delete (this->context());
  // o controle deve retornar a main. ou seja...?
  // como retornar o controle???
}

int Thread::id() { return this->_id; }

__END_API
