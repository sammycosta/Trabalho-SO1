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

    set_running(next);
    return CPU::switch_context(prev->_context, next->_context);
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
  _last_id--;
}

int Thread::id() { return this->_id; }

inline void Thread::dispatcher()
{

  // debug TRC
  while (Thread::_last_id > 1)
  {
    Thread *next_exec = Thread::_ready.head()->object();
    _dispatcher._state = READY;
    _ready.insert(&_dispatcher._link);
    Thread::set_running(next_exec);
    next_exec->_state = RUNNING;
    Thread::switch_context(&_dispatcher, next_exec);
    if (next_exec->_state == FINISHING)
    {
      _ready.remove(&next_exec->_link);
    }
  }
  _dispatcher._state = FINISHING;
  _ready.remove(&_dispatcher._link);
  Thread::switch_context(&_dispatcher, &_main);
}

inline void Thread::init(void (*main)(void *))
{
  // a gente deve usar o construtor pra inicializar? Como fazer isso???
  _main = Thread((void (*)())(main));
  _dispatcher = Thread(dispatcher); // como criar a dispatcher?
  _main._state = RUNNING;
  _running = &_main;

  // trocar contexto pra main
}

__END_API
