#include <stdio.h>
#include "traits.h"
#include "system.h"
#include "debug.h"
#include "thread.h"

__BEGIN_API

void System::init(void (*main)(void *))
{
  setvbuf(stdout, 0, _IONBF, 0);
  db<System>(TRC) << "System::init() chamado\n";
  Thread::init(main);
}
__END_API
