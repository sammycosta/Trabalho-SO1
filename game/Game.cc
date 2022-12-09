#include "Game.h"

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
    KeyboardListener *keyboardListener = new KeyboardListener(_eventQueue);

    Window *window = new Window(800, 600, 60, _eventQueue, userSpaceship);

    userSpaceship->userThread = new Thread (UserSpaceship::run);
    keyboardListener->kb_thread = new Thread(KeyboardListener::run);

}

Game::~Game()
{
}