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
Ready_Queue Thread::_ready;

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
  _last_id--;
  switch_context(this, &_dispatcher);
}

Thread::~Thread()
{
  delete _context;
}

int Thread::id() { return this->_id; }

inline void Thread::dispatcher()
{

  db<Thread>(TRC) << "Dispatcher chamado\n";

  while (_last_id > 2)
  {
    // _ready.insert((&_running)._link);
    db<Thread>(TRC) << "_ready.size(): " << Thread::_ready.size() << "\n";
    db<Thread>(TRC) << "head antes de remover: " << Thread::_ready.head()->object()->id() << "\n";
    Thread *next_exec = Thread::_ready.remove_head()->object();
    _dispatcher._state = READY;
    _ready.remove(&_dispatcher);
    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    _dispatcher._link.rank(now);
    _ready.insert(&_dispatcher._link);
    db<Thread>(TRC) << "saiu do insert\n";

    Thread::set_running(next_exec);
    next_exec->_state = RUNNING;

    Thread::switch_context(&_dispatcher, next_exec);

    if (next_exec->_state == FINISHING)
    {
      db<Thread>(TRC) << "id Thread removida: " << next_exec->_id << "\n";
      _ready.remove(next_exec);
      db<Thread>(TRC) << "_ready.size(): " << Thread::_ready.size() << "\n";
    }

    db<Thread>(TRC) << "last_id: " << Thread::_last_id << "\n";
  }
  _dispatcher._state = FINISHING;
  _ready.remove(&_dispatcher);
  db<Thread>(TRC) << "_ready.size(): " << Thread::_ready.size() << "\n";
  db<Thread>(TRC) << "voltando pra main... " << Thread::_main.id() << "\n";
  Thread::switch_context(&_dispatcher, &_main);
}

void Thread::init(void (*main)(void *))
{
  // a gente deve usar o construtor pra inicializar? Como fazer isso???
  db<Thread>(TRC) << "Thread::init foi chamado\n";
  new (&_ready) Ready_Queue();
  new (&_main) Thread(main, (void *)"main");
  new (&_dispatcher) Thread(dispatcher); // como criar a dispatcher?

  _main._state = RUNNING;
  _running = &_main;

  // trocar contexto pra main

  _main._context->load(); // Set user context -> deve começar a executar sua função
}

void Thread::yield()
{
  db<Thread>(TRC) << "Yield chamado com running sendo " << _running->_id << "\n";
  db<Thread>(TRC) << "head: " << _ready.head()->object()->id() << "\n";
  db<Thread>(TRC) << "ready_size: " << _ready.size() << "\n";
  Thread *next_exec = Thread::_ready.remove_head()->object();

  db<Thread>(TRC) << "main state: " << (_main)._state << "\n";

  if ((_main)._state != RUNNING && _running->_state != FINISHING)
  {
    // Atualiza prioridade da tarefa
    db<Thread>(TRC) << "Yield dentro do if para inserir, com running state: " << _running->_state << "\n";
    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    _running->_link.rank(now);
    _ready.insert(&(_running->_link)); // reinsere
  }
  if (_running->_state != FINISHING)
  {
    _running->_state = READY;
  }

  db<Thread>(TRC) << "passou if"
                  << "\n";
  Thread *last_running = _running;
  Thread::set_running(next_exec);
  next_exec->_state = RUNNING;
  db<Thread>(TRC) << "Yield, running agora é" << _running->_id << "\n";
  switch_context(last_running, _running);
}

__END_API
