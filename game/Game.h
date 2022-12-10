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
    }

private:
    static bool _finish;
    static Window *window;
    static UserSpaceship *userSpaceship;
    static KeyboardListener *keyboardListener;
    static ALLEGRO_TIMER *_timer;
    static int _fps;
    static ALLEGRO_EVENT_QUEUE *_eventQueue;
};

#endif
