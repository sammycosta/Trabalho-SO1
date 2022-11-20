#include "cpu.h"
#include <iostream>

__BEGIN_API

/* Salva contexto na variável _context da classe */
void CPU::Context::save()
{
    getcontext(&(this->_context));
    db<CPU>(TRC) << "CPU::Context::save() chamado\n";
}

/* Carrega contexto que está salvo na variável _context da classe */
void CPU::Context::load()
{
    if (&this->_context != nullptr)
    {
        setcontext(&(this->_context));
    }
    db<CPU>(TRC) << "CPU::Context::load() chamado\n";
}

/* Destrutor */
CPU::Context::~Context()
{
    if (this->_stack != nullptr)
    {
        db<CPU>(TRC) << "CPU::Context::~Context() chamado\n";
        delete (this->_stack);
    }
    else
    {
        db<CPU>(WRN) << "CPU::Context::~Context() Tentou deletar ponteiro nulo\n";
    }
}

/* Irá trocar o contexto usando os dois contextos recebidos como parâmetro (de “from” para “to”). */
int CPU::switch_context(Context *from, Context *to)
{
    if (from != nullptr && to != nullptr)
    {
        // Salva o contexto atual em “a” (primeiro argumento) e restaura o contexto previamente salvo em “b” (segundo argumento)
        swapcontext(&(from->_context), &(to->_context));
        return 0;
    }
    else
    {
        db<CPU>(ERR) << "Erro em CPU::Context::switch_context()\n";
        return -1;
    }
}

int CPU::finc(volatile int &number)
{
    int sum = 1;
    __asm__ __volatile__("lock xadd %0, %2"
                         : "=a"(number)
                         : "a"(number), "m"(sum)
                         : "memory");

    db<CPU>(TRC) << "CPU::finc() sum = " << sum << "\n";
    return sum;
}

int CPU::fdec(volatile int &number)
{

    int sum = -1;
    __asm__ __volatile__("lock xadd %0, %2"
                         : "=a"(number)
                         : "a"(number), "m"(sum)
                         : "memory");

    db<CPU>(TRC) << "CPU::fdec() sum = " << sum << "\n";
    return sum;
}

__END_API
