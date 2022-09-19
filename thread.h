#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;

public:
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
     * Qualquer outro método que você achar necessário para a solução.
     */

    Context *context()
    {
        return this->_context;
    }

private:
    int _id;                    // contém o ID da Thread.
    Context *volatile _context; //  contém o contexto da Thread.
    static Thread *_running;    // ponteiro para a Thread que estiver em execução.
    // Toda vez que uma nova Thread for executada, este ponteiro deve ser atualizado.

    /*
     * Qualquer outro atributo que você achar necessário para a solução.
     */
};

template <typename... Tn>
inline Thread::Thread(void (*entry)(Tn...), Tn... an)
{
    // provavelmente falta mais algumas coisas (ponteiro pra função? id? running?)
    this->_running = entry;
    this->_context = new Context(entry, an...);
    // não sei se funciona!
}
__END_API

#endif