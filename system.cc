#include <stdio.h>
#include "traits.h"
#include "system.h"
#include "debug.h"
#include "thread.h" // pra parar de dar erro

__BEGIN_API

void System::init(void (*main)(void *))
{
  setvbuf(stdout, 0, _IONBF, 0);
  Thread::init(main);
  db<System>(TRC) << "System::init() chamado\n";
}
__END_API
