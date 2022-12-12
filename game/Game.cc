#include "Game.h"

bool Game::_finish;
Window *Game::window;
UserSpaceship *Game::userSpaceship;
KeyboardListener *Game::keyboardListener;
EnemySpaceshipManager *Game::enemyManager;
CollisionManager *Game::collisionManager;
MineManager *Game::mineManager;

ALLEGRO_TIMER *Game::_timer;
int Game::_fps;
ALLEGRO_EVENT_QUEUE *Game::_eventQueue;
Thread *Game::_windowThread;
Thread *Game::_userThread;
Thread *Game::_kbThread;
Thread *Game::_enemySpaceshipManagerThread;
Thread *Game::_collisionManagerThread;
Thread *Game::_mineManagerThread;
// Thread *Game::_bossManagerThread;

void Game::runWindow()
{
    Window::run(window);
    delete window;
    _windowThread->thread_exit(0);
}
void Game::runUser()
{
    UserSpaceship::run(userSpaceship);
    delete userSpaceship;
    _userThread->thread_exit(1);
}
void Game::runKeyboardManager()
{
    KeyboardListener::run(keyboardListener);
    delete keyboardListener;
    _kbThread->thread_exit(2);
}
void Game::runEnemyManager()
{
    EnemySpaceshipManager::run(enemyManager);
    delete enemyManager;
    _enemySpaceshipManagerThread->thread_exit(3);
}
void Game::runMineManager()
{
    MineManager::run(mineManager);
    delete mineManager;
    _mineManagerThread->thread_exit(4);
}

void Game::runCollisionManager()
{
    CollisionManager::run(collisionManager);
    delete collisionManager;
    _collisionManagerThread->thread_exit(5);
}