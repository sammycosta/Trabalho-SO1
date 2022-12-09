#ifndef USER_SPACESHIP_H
#define USER_SPACESHIP_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "../Sprite.h"
#include "../Vector.h"
#include "../Action.h"
#include "../library_threads/traits.h"
#include "../library_threads/thread.h"

__USING_API

class UserSpaceship
{
public:
    UserSpaceship(ALLEGRO_EVENT_QUEUE *_timerQueue);
    ~UserSpaceship();
    static void run();

    static void update(double dt);
    void increaseVerticalSpeed();
    void increaseHorizontalSpeed();
    void decreaseVerticalSpeed();
    void decreaseHorizontalSpeed();

    static inline int getRow();
    static inline int getCol();
    static inline Point getCentre();
    static inline std::shared_ptr<Sprite> getSpaceShip();

    Thread *userThread;

private:
    static void checkBoundary();
    static void selectShipAnimation();
    void loadSprite();

    static std::shared_ptr<Sprite> spaceShip;
    static Point centre;
    ALLEGRO_COLOR color; /**< ship color */
    static Vector speed;
    static int row; /**<row of animation to be played */
    static int col; /**< column of animation to be played */
    static ALLEGRO_EVENT_QUEUE *_timerQueue;
};

#endif