#include "Game.h"

bool Game::_finish;
Window *Game::window;
UserSpaceship *Game::userSpaceship;
KeyboardListener *Game::keyboardListener;
ALLEGRO_TIMER *Game::_timer;
int Game::_fps;
ALLEGRO_EVENT_QUEUE *Game::_eventQueue;
Thread *Game::_windowThread;
Thread *Game::_userThread;
Thread *Game::_kbThread;
Thread *Game::_enemySpaceshipManagerThread;
Thread *Game::_collisionManagerThread;
Thread *Game::_mineManagerThread;

