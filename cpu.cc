#include "cpu.h"
#include <iostream>

__BEGIN_API

/* Salva contexto na variável _context da classe */
void CPU::Context::save()
{
    // adicionar implementação
    getcontext(&(this->_context));
}

/* Carrega contexto que está salvo na variável _context da classe */
void CPU::Context::load()
{
    // adicionar implementação
    setcontext(&(this->_context));
}

// destrutor
CPU::Context::~Context()
{
    // adicionar implementação
    // if ponteiro válido:
    delete(_stack);
}

/* irá trocar o contexto usando os dois contextos recebidos como parâmetro (de “from” para “to”). */
void CPU::switch_context(Context *from, Context *to)
{
    // implementação do método
    // Salva o contexto atual em “a” (primeiro argumento) e restaura o contexto previamente salvo em “b” (segundo argumento)
    swapcontext(&(from->_context), &(to->_context)); // ACHO que é assim
}

__END_API
