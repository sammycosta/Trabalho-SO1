#include "KeyboardListener.h"
#include <iostream>

KeyboardListener::KeyboardListener(ALLEGRO_EVENT_QUEUE *timerQueue)
{
    // al_init() ??

    // create keyboard listener queue for keyboard event
    if ((_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }

    // install keyboard
    if (!al_install_keyboard())
    {
        std::cerr << "Could not install keyboard\n";
    }

    // register keyboard
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());

    _timerQueue = timerQueue;
}

KeyboardListener::~KeyboardListener()
{
}

void KeyboardListener::run(KeyboardListener *listener)
{
    while (true)
    {
        ALLEGRO_KEYBOARD_STATE kb;
        al_get_keyboard_state(&kb); // de onde ele pega?? se não usa a fila
        listener->input(kb);
        Thread::yield();
    }
}

act::action KeyboardListener::input(ALLEGRO_KEYBOARD_STATE &kb)
{
    if (al_key_down(&kb, ALLEGRO_KEY_UP))
    {
        userSpaceship->decreaseVerticalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_RIGHT))
    {
        userSpaceship->increaseHorizontalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_DOWN))
    {
        userSpaceship->increaseVerticalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_LEFT))
    {
        userSpaceship->decreaseHorizontalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_1))
    {
        std::cout << "missel\n";
        return act::action::FIRE_PRIMARY;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_SPACE))
    {
        std::cout << "tiro normal\n";
        return act::action::FIRE_SECONDARY;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE))
    {
        std::cout << "sair\n";
        return act::action::QUIT_GAME;
    }

    return act::action::NO_ACTION;
}
