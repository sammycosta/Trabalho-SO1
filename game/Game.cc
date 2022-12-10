#include "Game.h"

bool Game::_finish;
Window *Game::window;
UserSpaceship *Game::userSpaceship;
KeyboardListener *Game::keyboardListener;
ALLEGRO_TIMER *Game::_timer;
int Game::_fps;
ALLEGRO_EVENT_QUEUE *Game::_eventQueue;
Thread *Game::_window_thread;
Thread *Game::_userThread;
Thread *Game::_kb_thread;

/*

Game::Game()
{
    al_init();
    // initialize our timers
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

    UserSpaceship *userSpaceship = new UserSpaceship(_eventQueue);
    std::cout << "game\n";
    KeyboardListener *keyboardListener = new KeyboardListener(_eventQueue);

    Window *window = new Window(800, 600, 60, _eventQueue, userSpaceship);

    userSpaceship->userThread = new Thread(UserSpaceship::run, userSpaceship);
    keyboardListener->kb_thread = new Thread(KeyboardListener::run, keyboardListener);
    Thread::yield();
}

Game::~Game()
{
}

void Game::run()
{
    al_init();
    // initialize our timers
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

    UserSpaceship *userSpaceship = new UserSpaceship(_eventQueue);
    std::cout << "game\n";
    KeyboardListener *keyboardListener = new KeyboardListener(_eventQueue);

    Window *window = new Window(800, 600, 60, _eventQueue, userSpaceship);

    userSpaceship->userThread = new Thread(UserSpaceship::run, userSpaceship);
    keyboardListener->kb_thread = new Thread(KeyboardListener::run, keyboardListener);
    Thread::yield();
}

*/
