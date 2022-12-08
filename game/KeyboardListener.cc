#include "KeyboardListener.h"
#include <iostream>

KeyboardListener::KeyboardListener()
{
    // al_init() ??

    // install keyboard
    if (!al_install_keyboard())
    {
        std::cerr << "Could not install keyboard\n";
    }

    // register keyboard
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
}

KeyboardListener::~KeyboardListener()
{
}

void KeyboardListener::run()
{
    ALLEGRO_KEYBOARD_STATE kb;
    al_get_keyboard_state(&kb);
    input(kb);
}

act::action KeyboardListener::input(ALLEGRO_KEYBOARD_STATE &kb)
{
    if (al_key_down(&kb, ALLEGRO_KEY_UP))
    {
        this->userSpaceship->decreaseVerticalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_RIGHT))
    {
        this->userSpaceship->increaseHorizontalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_DOWN))
    {
        this->userSpaceship->increaseVerticalSpeed();
    }
    if (al_key_down(&kb, ALLEGRO_KEY_LEFT))
    {
        this->userSpaceship->decreaseHorizontalSpeed();
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
