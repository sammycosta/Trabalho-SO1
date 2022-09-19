#include <stdio.h>
#include "traits.h"
#include "system.h"
#include "debug.h"

__BEGIN_API

void System::init()
{
  setvbuf(stdout, 0, _IONBF, 0);
  db<System>(TRC) << "System::init() chamado\n";
}
__END_API
