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

        userSpaceship = new UserSpaceship(_timer, _fps);
        enemyManager = new EnemySpaceshipManager(_fps, userSpaceship->getCentreShared());
        mineManager = new MineManager();
        keyboardListener = new KeyboardListener(userSpaceship);
        window = new Window(800, 600, 60, _timer, userSpaceship, enemyManager, mineManager, keyboardListener);
        collisionManager = new CollisionManager(userSpaceship, enemyManager, mineManager);

        _windowThread = new Thread(runWindow);
        _userThread = new Thread(runUser);
        _kbThread = new Thread(runKeyboardManager);
        _enemySpaceshipManagerThread = new Thread(runEnemyManager);
        _collisionManagerThread = new Thread(runCollisionManager);
        _mineManagerThread = new Thread(runMineManager);

        _windowThread->join();
        _userThread->join();
        _kbThread->join();
        _enemySpaceshipManagerThread->join();
        _collisionManagerThread->join();
        _mineManagerThread->join();

        delete (_windowThread);
        delete (_userThread);
        delete (_kbThread);
        delete (_enemySpaceshipManagerThread);
        delete (_collisionManagerThread);
        delete (_mineManagerThread);

        delete window;
        delete enemyManager;
        delete userSpaceship;
        delete keyboardListener;
        delete mineManager;
        delete collisionManager;
    }

private:
    static void runWindow();
    static void runUser();
    static void runKeyboardManager();
    static void runEnemyManager();
    static void runMineManager();
    static void runCollisionManager();

    static ALLEGRO_TIMER *_timer;
    static int _fps;
    static ALLEGRO_EVENT_QUEUE *_eventQueue;

    static Window *window;
    static UserSpaceship *userSpaceship;
    static KeyboardListener *keyboardListener;
    static EnemySpaceshipManager *enemyManager;
    static CollisionManager *collisionManager;
    static MineManager *mineManager;

    static Thread *_windowThread;
    static Thread *_userThread;
    static Thread *_kbThread;
    static Thread *_enemySpaceshipManagerThread;
    static Thread *_collisionManagerThread;
    static Thread *_mineManagerThread;
};

#endif
