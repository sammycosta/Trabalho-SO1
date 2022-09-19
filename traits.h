#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API    \
    namespace SOLUTION \
    {
#define __END_API }
#define __USING_API using namespace SOLUTION;

__BEGIN_API

class CPU; // declaração das classes criadas nos trabalhos devem ser colocadas aqui
class Debug;
class Thread;
class System;

// declaração da classe Traits
template <typename T>
struct Traits
{
    static const bool debugged = false;
};

template <>
struct Traits<CPU>
{
    // Adicionar aqui a declaração do tamanho da Pilha
    static const unsigned int STACK_SIZE = 64000;
};

template <>
struct Traits<Debug> : public Traits<void>
{
    // Os níveis de debug devem ser declarados e habilitados no arquivo traits.h
    static const bool error = true;
    static const bool warning = false;
    static const bool info = false;
    static const bool trace = true;
};

template <>
struct Traits<System> : public Traits<void>
{
    static const bool debugged = false;
};

template <>
struct Traits<Thread> : public Traits<void>
{
    static const bool debugged = true;
};

__END_API

#endif
