#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "UserSpaceship.h"

class KeyboardListener
{
public:
    KeyboardListener(UserSpaceship *ship);
    ~KeyboardListener();

    static void run(KeyboardListener *listener);

    inline bool getFinish() const
    {
        return _finish;
    }

    inline void setFinish(bool finish)
    {
        _finish = finish;
    }

private:
    void input(ALLEGRO_KEYBOARD_STATE &);
    ALLEGRO_EVENT_QUEUE *_eventQueue;

    UserSpaceship *_userSpaceship;
    bool _finish;
};

#endif