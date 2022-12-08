#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime>
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;

public:
    typedef Ordered_List<Thread> Ready_Queue;

    // Thread State
    enum State
    {
        RUNNING,
        READY,
        FINISHING,
        SUSPENDED,
        WAITING
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */
    Thread() {}

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */
    template <typename... Tn>
    Thread(void (*entry)(Tn...), Tn... an);

    /*
     * Retorna a Thread que está em execução.
     */
    static Thread *running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */
    static int switch_context(Thread *prev, Thread *next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main.
     */
    void thread_exit(int exit_code);

    /*
     * Retorna o ID da thread.
     */
    int id();

    /*
     * Retorna o contexto da thread.
     */
    Context *context() { return this->_context; }

    /*
     * Atualiza atributo que guarda a Thread em execução (running)
     @param Thread*
     */
    static void set_running(Thread *now_running) { _running = now_running; };

    /*
     * Daspachante (disptacher) de threads.
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher();

    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield();

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */
    ~Thread();

    /*
     * Este método deve suspender a thread em execução até que a thread “alvo” finalize.
     * O inteiro retornado por join() é o argumento recebido por thread_exit(), ou seja, exit_code (novo atributo _exit_code necessário na classe
     * Thread – pergunta: quando o atributo _exit_code deve ser inicializado?).
     * Como tratar a suspensão e o resumo de uma Thread?
     */
    int join();

    /*
     * Suspende a Thread até que resume() seja chamado.
     * Como tratar as Threads suspensas dentro do SO?
     * Deve-se usar uma nova fila?
     * Deve-se fazer alguma alteração no estado (enum State) da Thread?
     */
    void suspend();

    /*
     * Coloca uma Thread que estava suspensa de volta para a fila de prontos.
     */
    void resume();

    Ready_Queue::Element *get_link();

    static Thread *sleep();

    static void wakeup(Thread *t);

private:
    int _id;
    Context *volatile _context;
    static Thread *_running;

    static Thread _main;
    static CPU::Context _main_context;
    static Thread _dispatcher;
    static Ready_Queue _ready;
    Ready_Queue::Element _link;
    volatile State _state;
    static int _last_id;
    int _exit_code;
    Ordered_List<Thread> _suspended_queue;
};

template <typename... Tn>
inline Thread::Thread(void (*entry)(Tn...), Tn... an) : _link(this, std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())
{
    this->_context = new Context(entry, an...);
    if (this->_context)
    {
        this->_id = _last_id;
        _last_id++;

        if (this->_id > 0)
        {
            this->_state = READY;
            _ready.insert(&_link);
        }

        db<Thread>(TRC) << "Thread::Construiu Thread " << this->_id << "\n";
        db<Thread>(TRC) << "Contador: " << _last_id << "\n";
    }
    else
    {
        db<Thread>(ERR) << "Erro no construtor Thread::Thread()\n"
                        << "\n";
        exit(-1);
    }
}

__END_API

#endif
