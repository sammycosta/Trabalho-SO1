#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Semaphore
{
public:
    typedef Ordered_List<Thread> Sleep_Queue;

    Semaphore(int v = 1)
    {
        this->value = v;
    };

    ~Semaphore();

    /* Este método deve implementar a operação p (ou sleep) de um semáforo. Deve-se decrementar o
     * inteiro do semáforo de forma atômica (utilizando fdec) e colocar a Thread para
     * dormir caso a mesma não conseguir acessar o semáforo (já existir em uso por outra Thread). */
    void p();

    /* Este método deve implementar a operação v (ou wakeup) de um semáforo. Deve-se
     * incrementar o inteiro do semáforo de forma atômica (utilizando finc) e acordar
     * uma Thread que estiver dormindo no semáforo.*/
    void v();

private:
    // Atomic operations

    /* Incremento atômico utilizando xadd e lock do assembly */
    int finc(volatile int &number);

    /* Decremento atômico utilizando xadd e lock do assembly */
    int fdec(volatile int &number);

    // Thread operations

    /* O método sleep() deve colocar a Thread que não conseguir acessar o semáforo para dormir e
     * mudar seu estado para WAITING (note que WAITING é diferente de SUSPENDED do trabalho
     * trabalho anterior).*/
    void sleep();

    /* O método wakeup() deve acordar uma Thread que estava dormindo no semáforo. */
    void wakeup();

    /* O método wakeup_all() deve acordar todas as Thread que estavam dormindo no semáforo. */
    void wakeup_all();

private:
    // DECLARAÇÃO DOS ATRIBUTOS DO SEMÁFORO

    volatile int value; // adicionei
    Sleep_Queue sleep_queue;
};

__END_API

#endif
