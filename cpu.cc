#include "cpu.h"
#include <iostream>

__BEGIN_API

/* Salva contexto na variável _context da classe */
void CPU::Context::save()
{
    getcontext(&(this->_context));
}

/* Carrega contexto que está salvo na variável _context da classe */
void CPU::Context::load()
{
    setcontext(&(this->_context));
}

/* Destrutor */
CPU::Context::~Context()
{
    // if ponteiro válido:
    if (this->_stack != nullptr)
    {
        delete (this->_stack);
    }
}

/* Irá trocar o contexto usando os dois contextos recebidos como parâmetro (de “from” para “to”). */
void CPU::switch_context(Context *from, Context *to)
{
    if (from != nullptr && to != nullptr)
    {
        // Salva o contexto atual em “a” (primeiro argumento) e restaura o contexto previamente salvo em “b” (segundo argumento)
        swapcontext(&(from->_context), &(to->_context));
    }
}

__END_API
