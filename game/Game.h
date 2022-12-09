#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "Window.h"
#include "UserSpaceship.h"
#include "KeyboardListener.h"
#include "../library_threads/traits.h"
#include "../library_threads/thread.h"

__USING_API

class Game
{
public:
    Game();
    ~Game();

private:
    bool _finish;
    Window *window;
    UserSpaceship *userSpaceship;
    KeyboardListener *keyboardListener;
    ALLEGRO_TIMER *_timer;
    int _fps;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
};

#endif
