#include <iostream>
#include "thread.h"
#include "traits.h"
#include "list.h"

__BEGIN_API

/* Inicialização de variáveis */

int Thread::_last_id = 0;
Thread *Thread::_running = nullptr;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread Thread::_dispatcher;
Thread::Ready_Queue Thread::_ready;

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
  this->_exit_code = exit_code;
  _last_id--;

  Thread *to_resume = _waiting_thread;

  if (to_resume)
  {
    if (to_resume == &_main)
    {
      // Se é a main, não posso reinseri-la na fila
      (&_main)->_state = RUNNING;
      switch_context(this, &_main);
    }
    else
    {
      to_resume->resume();
    }
  }
  yield();
}

Thread::~Thread()
{
  delete _context;
}

int Thread::id() { return this->_id; }

inline void Thread::dispatcher()
{

  while (_last_id > 2)
  {
    db<Thread>(TRC) << "Início do loop dispatcher\n";
    db<Thread>(TRC) << "Head antes de remover: " << Thread::_ready.head()->object()->id() << "\n";
    Thread *next_running = Thread::_ready.remove_head()->object(); // escolhe a próxima thread para executar
    _dispatcher._state = READY;
    _ready.insert(&_dispatcher._link); // reinsire dispatcher na fila

    Thread::set_running(next_running);
    next_running->_state = RUNNING;

    Thread::switch_context(&_dispatcher, next_running);

    if (next_running->_state == FINISHING)
    {
      db<Thread>(TRC) << "id Thread removida: " << next_running->_id << "\n";
      _ready.remove(next_running);
    }
  }

  _dispatcher._state = FINISHING;
  _ready.remove(&_dispatcher);
  db<Thread>(TRC) << "_ready.size(): " << Thread::_ready.size() << "\n";
  db<Thread>(TRC) << "Voltando pra main... " << Thread::_main.id() << "\n";
  Thread::switch_context(&_dispatcher, &_main);
}

void Thread::init(void (*main)(void *))
{
  db<Thread>(TRC) << "Thread::init foi chamado\n";
  new (&_main) Thread(main, (void *)"main");
  new (&_dispatcher) Thread(dispatcher);
  new (&_main_context) CPU::Context();

  _running = &_main;
  _main._state = RUNNING;

  CPU::switch_context(&_main_context, _main.context());
}

void Thread::yield()
{
  db<Thread>(TRC) << "Yield chamado com running sendo " << _running->_id << "\n";

  Thread *next_running = Thread::_ready.remove_head()->object();

  if ((_main)._state != RUNNING && _running->_state == RUNNING)
  {
    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    _running->_link.rank(now);         // Atualiza prioridade da tarefa
    _ready.insert(&(_running->_link)); // Reinsere a que está em execução
  }

  // mudei os if que checa finishing ou suspendo pra == running p nao adicionar waiting
  if (_running->_state == RUNNING)
  {
    _running->_state = READY; // Atualiza READY para todas exceto se FINISHING ou SUSPENDED ou WAITING
  }

  Thread *last_running = _running;
  Thread::set_running(next_running);
  next_running->_state = RUNNING;
  _ready.remove(_running); // Removo a proxima a executar da fila de prontos
  db<Thread>(TRC) << "Finalizando yield, running agora será " << _running->_id << "\n";
  switch_context(last_running, _running);
}

int Thread::join()
{
  db<Thread>(TRC) << "Join chamado com this sendo " << this->_id << " e running sendo " << _running->_id << "\n";

  if (this->_state != FINISHING && this != _running && _waiting_thread == nullptr)
  {
    this->_waiting_thread = _running;
    _running->suspend();
  }
  else
  {
    db<Thread>(ERR) << "Erro ao fazer join";
    return -1;
  }

  return _exit_code;
}

void Thread::suspend()
{
  db<Thread>(TRC) << "Suspend chamado para thread " << this->_id << "\n";
  if (this != &_main)
  {
    _ready.remove(this);
  }
  this->_state = SUSPENDED;
  yield();
}

void Thread::resume()
{
  db<Thread>(TRC) << "Resume chamado para thread" << this->_id << "\n";
  if (this->_state == SUSPENDED)
  {
    _ready.insert(&(this->_link));
    this->_state = READY;
  }
}

Thread::Ready_Queue::Element *Thread::get_link()
{
  return &(this->_link);
}

Thread *Thread::sleep()
{
  _running->_state = WAITING;
  if (_running != &_main)
  {
    _ready.remove(_running);
  }
  return _running;
}

void Thread::wakeup(Thread *t)
{
  t->_state = READY;
  _ready.insert(&(t->_link));
}

__END_API
