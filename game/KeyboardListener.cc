#include "KeyboardListener.h"
#include <iostream>

KeyboardListener::KeyboardListener(UserSpaceship *ship, Window *win)
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
    _userSpaceship = ship;
    _window = win;
}

KeyboardListener::~KeyboardListener()
{
}

void KeyboardListener::run(KeyboardListener *listener)
{
    while (true)
    {
        // std::cout << "run keyboardListener \n";
        ALLEGRO_KEYBOARD_STATE kb;
        al_get_keyboard_state(&kb);
        listener->input(kb);
        Thread::yield();
    }
}

act::action KeyboardListener::input(ALLEGRO_KEYBOARD_STATE &kb)
{
    if (al_key_down(&kb, ALLEGRO_KEY_UP))
    {
        _userSpaceship->decreaseVerticalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_RIGHT))
    {
        _userSpaceship->increaseHorizontalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_DOWN))
    {
        _userSpaceship->increaseVerticalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_LEFT))
    {
        _userSpaceship->decreaseHorizontalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_1))
    {
        _userSpaceship->addMissile();
        return act::action::FIRE_PRIMARY;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_SPACE))
    {
        _userSpaceship->addBullet();
        return act::action::FIRE_SECONDARY;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE))
    {
        _window->setFinish(true);
        return act::action::QUIT_GAME;
    }

    return act::action::NO_ACTION;
}
