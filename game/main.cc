/**
 * @file main.cc
 * @brief
 *
 */

#include "Game.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include "system.h"

int main()
{
    srand(time(0));

    System::init((void (*)(void *)) & Game::run);

    return 0;
}
