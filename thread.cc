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
  // if (this->_waiting_thread)
  // {
  //   this->_waiting_thread->resume();
  //   this->_waiting_thread = nullptr;
  // }
  for (unsigned int i = 0; i < this->_waiting.size(); i++)
  {
    this->_waiting.remove_head()->object()->resume();
  }

  _last_id--;
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
  new (&_ready) Ready_Queue();
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

  if ((_main)._state != RUNNING && _running->_state != FINISHING)
  {
    int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    _running->_link.rank(now);         // Atualiza prioridade da tarefa
    _ready.insert(&(_running->_link)); // Reinsere a que está em execução
  }

  if (_running->_state != FINISHING)
  {
    _running->_state = READY; // Atualiza READY para todas exceto se FINISHING
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
  db<Thread>(TRC) << "Join chamado pela thread " << this->_id << "\n";

  /** Blocks the current thread until the thread identified by *this finishes its execution.
The completion of the thread identified by *this synchronizes with the corresponding successful return from join().
No synchronization is performed on *this itself. Concurrently calling join() on the same thread object from multiple threads constitutes a data race that results in undefined behavior.
**/

  if (this->_state != FINISHING && this != _running)
  {
    this->_waiting.insert(&(_running->_link));
    _running->suspend();
  }
  return _exit_code; // ainda nao inicializado, onde fazer isso?
}

void Thread::suspend()
{
  db<Thread>(TRC) << "Suspend chamado \n";

  // remove da fila de prontos? coloca ela numa estrutura de suspensas? muda state?
  if (this != &_main)
  {
    _ready.remove(this);
  }
  // this->_state = SUSPENDED;
  yield();
}

void Thread::resume()
{
  db<Thread>(TRC) << "Resume chamado para thread" << this->_id << "\n";
  // devolve pra fila de prontos? onde pego a thread suspensa, nova estrutura?
  _ready.insert(&(this->_link));
  this->_state = READY;
}
__END_API
