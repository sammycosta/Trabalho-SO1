#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "Action.h"
#include "UserSpaceship.h"
#include "Window.h"

class KeyboardListener
{
public:
    KeyboardListener(UserSpaceship *ship, Window *win);
    ~KeyboardListener();

    static void run(KeyboardListener *listener);

private:
    act::action input(ALLEGRO_KEYBOARD_STATE &);
    ALLEGRO_EVENT_QUEUE *_eventQueue;

    UserSpaceship *_userSpaceship;
    Window *_window;
};

#endif