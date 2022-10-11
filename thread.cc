#include <iostream>
#include "thread.h"
#include "traits.h"
#include "list.h"

__BEGIN_API

/* Inicialização de variáveis */
typedef Ordered_List<Thread> Ready_Queue;

int Thread::_last_id = 0;
Thread *Thread::_running = nullptr;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread Thread::_dispatcher;
Ready_Queue Thread::_ready = Ready_Queue();

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
  this->_state = FINISHING;
  switch_context(this, &_dispatcher); // imagino que isso seja feito
}

int Thread::id() { return this->_id; }

inline void Thread::dispatcher()
{

  db<Thread>(TRC) << "Dispatcher chamado\n";

  while (Thread::_last_id > 1)
  {
    Thread *next_exec = Thread::_ready.head()->object();
    _dispatcher._state = READY;
    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    _dispatcher._link.rank(now);
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

void Thread::init(void (*main)(void *))
{
  // a gente deve usar o construtor pra inicializar? Como fazer isso???
  db<Thread>(TRC) << "Thread::init foi chamado\n";
  _main = Thread((void (*)())(main));
  _dispatcher = Thread(dispatcher); // como criar a dispatcher?
  _main._state = RUNNING;
  _running = &_main;
  // trocar contexto pra main
  _main._context->load(); // Set user context -> deve começar a executar sua função
}

void Thread::yield()
{
  db<Thread>(TRC) << "Yield chamado com running sendo" << _running->_id << "\n";
  if (_running->_state != FINISHING)
  {
    Thread *next_exec = Thread::_ready.head()->object();
    Ready_Queue::Element *e = Thread::_ready.head();

    // while (true)
    // {
    //   db<Thread>(TRC) << e->object()->_id << " thread na fila \n";
    //   if (e->next() == nullptr)
    //   {
    //     break;
    //   }
    //   Ready_Queue::Element *e = e->next();
    // }

    if ((&_main)->_state != RUNNING)
    {
      // Atualiza prioridade da tarefa
      int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
      _running->_link.rank(now);
    }
    _running->_state = READY;
    _ready.remove(_running);           // preciso tirar pra reinserir né?
    _ready.insert(&(_running->_link)); // reinsere
    Thread *last_running = _running;
    Thread::set_running(next_exec);
    next_exec->_state = RUNNING;
    db<Thread>(TRC) << "Yield, running agora é" << _running->_id << "\n";
    switch_context(last_running, _running);
  }
}

__END_API
