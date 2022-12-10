#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "Action.h"
#include "UserSpaceship.h"

class KeyboardListener
{
public:
    KeyboardListener(ALLEGRO_EVENT_QUEUE *timerQueue);
    ~KeyboardListener();

    static void run(KeyboardListener *listener);

    Thread *kb_thread;

private:
    act::action input(ALLEGRO_KEYBOARD_STATE &);
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    ALLEGRO_EVENT_QUEUE *_timerQueue;

    UserSpaceship *userSpaceship;
};

#endif