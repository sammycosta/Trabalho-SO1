#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "Window.h"
#include "UserSpaceship.h"
#include "KeyboardListener.h"
#include "traits.h"
#include "thread.h"
#include "EnemySpaceshipManager.h"
#include "CollisionManager.h"
#include "MineManager.h"
#include "BossManager.h"

__USING_API

class Game
{
public:
    Game() {}
    ~Game() {}
    static void run()
    {
        al_init();
        // initialize our timers
        _fps = 60;
        if ((_timer = al_create_timer(1.0 / _fps)) == NULL)
        {
            std::cout << "error, could not create timer\n";
            exit(1);
        }
        if ((_eventQueue = al_create_event_queue()) == NULL)
        {
            std::cout << "error, could not create event queue\n";
            exit(1);
        }
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
        al_start_timer(_timer);

        UserSpaceship *userSpaceship = new UserSpaceship(_timer, _fps);
        EnemySpaceshipManager *enemyManager = new EnemySpaceshipManager(_fps, userSpaceship->getCentreShared());
        MineManager *mineManager = new MineManager();
        Window *window = new Window(800, 600, 60, _timer, userSpaceship, enemyManager, mineManager);
        KeyboardListener *keyboardListener = new KeyboardListener(userSpaceship, window);
        CollisionManager *collisionManager = new CollisionManager(userSpaceship, enemyManager, mineManager);
        // BossManager *bossManager = new BossManager();

        _windowThread = new Thread(Window::run, window);
        _userThread = new Thread(UserSpaceship::run, userSpaceship);
        _kbThread = new Thread(KeyboardListener::run, keyboardListener);
        _enemySpaceshipManagerThread = new Thread(EnemySpaceshipManager::run, enemyManager);
        _collisionManagerThread = new Thread(CollisionManager::run, collisionManager);
        _mineManagerThread = new Thread(MineManager::run, mineManager);
        // _bossManagerThread = new Thread(BossManager::run, bossManager);

        int ec;
        ec = _windowThread->join();
        ec = _userThread->join();
        ec = _kbThread->join();
        ec = _enemySpaceshipManagerThread->join();
        ec = _collisionManagerThread->join();
        ec = _mineManagerThread->join();
        // ec = _bossManagerThread->join();
        std::cout << "chegou no fim do game.h ! \n";
        delete (_windowThread);
        delete (_userThread);
        delete (_kbThread);
        delete (_enemySpaceshipManagerThread);
        delete (_collisionManagerThread);
        delete (_mineManagerThread);

        delete window;
        delete userSpaceship;
        delete keyboardListener;
        delete enemyManager;
        delete collisionManager;
        delete mineManager;

    }

private:
    static bool _finish;
    static Window *window;
    static UserSpaceship *userSpaceship;
    static KeyboardListener *keyboardListener;
    static ALLEGRO_TIMER *_timer;
    static int _fps;
    static ALLEGRO_EVENT_QUEUE *_eventQueue;
    static Thread *_windowThread;
    static Thread *_userThread;
    static Thread *_kbThread;
    static Thread *_enemySpaceshipManagerThread;
    static Thread *_collisionManagerThread;
    static Thread *_mineManagerThread;
    // static Thread *_bossManagerThread;
};

#endif
