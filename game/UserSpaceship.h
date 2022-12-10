#ifndef USER_SPACESHIP_H
#define USER_SPACESHIP_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "./library_threads/traits.h"
#include "./library_threads/thread.h"

__USING_API

class UserSpaceship
{
public:
    UserSpaceship(ALLEGRO_EVENT_QUEUE *_timerQueue);
    ~UserSpaceship();
    static void run(UserSpaceship *ship);

    void update(double dt);
    void increaseVerticalSpeed();
    void increaseHorizontalSpeed();
    void decreaseVerticalSpeed();
    void decreaseHorizontalSpeed();

    inline int getRow() const
    {
        return row;
    }
    inline int getCol() const
    {
        return col;
    }
    inline Point getCentre() const
    {
        return centre;
    }
    inline std::shared_ptr<Sprite> getSpaceShip() const
    {
        return spaceShip;
    }

    Thread *userThread;

private:
    void checkBoundary();
    void selectShipAnimation();
    void loadSprite();

    std::shared_ptr<Sprite> spaceShip;
    Point centre;
    ALLEGRO_COLOR color; /**< ship color */
    Vector speed;
    int row; /**<row of animation to be played */
    int col; /**< column of animation to be played */
    ALLEGRO_EVENT_QUEUE *_timerQueue;
};

#endif