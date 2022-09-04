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
            //         ping = new CPU::Context(func_ping, (char *) ping_name.data());

            getcontext(&_context);
            _context.uc_link = 0;
            _context.uc_stack.ss_sp = malloc(STACK_SIZE);
            _context.uc_stack.ss_size = STACK_SIZE;
            _context.uc_stack.ss_flags = 0;
            _stack = (char *)_context.uc_stack.ss_sp;
            makecontext(&_context, (func)(null), sizeof...(an), an...);
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
