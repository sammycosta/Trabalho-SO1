#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include "traits.h"

__BEGIN_API

class CPU
{
public:
    class Context
    {
    private:
        static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;

    public:
        Context() { _stack = 0; }

        /* construtor parametrizado que recebe uma função
como primeiro parâmetro e os argumentos para essa função na seguinte. A declaração, para
quem tem dificuldades com C++, usa variadic templates. A função passada como parâmetro é a
função executada no contexto. Esse construtor deve alocar memória para a pilha do novo
contexto a ser criado, além de inicializar todos os campos da estrutura ucontext_t (através do
atributo _context) e criar um novo contexto usando makecontext().*/
        template <typename... Tn>
        Context(void (*func)(Tn...), Tn... an)
        {
            // if pra ver se função válida?

            this->_stack = new char[STACK_SIZE];
            getcontext(&_context);
            this->_context.uc_link = 0;
            this->_context.uc_stack.ss_sp = (void *)(this->_stack);
            this->_context.uc_stack.ss_size = STACK_SIZE;
            this->_context.uc_stack.ss_flags = 0;
            makecontext(&_context, (void(*)())(func), sizeof...(an), an...);
        }
        // usar makecontext(ucontext_t *, (void *)(), int, ...); ?

        ~Context();

        void save();
        void load();

    private:
        char *_stack;

    public:
        ucontext_t _context;
    };

public:
    static void switch_context(Context *from, Context *to);
};

__END_API

#endif
