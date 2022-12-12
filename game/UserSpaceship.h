#ifndef USER_SPACESHIP_H
#define USER_SPACESHIP_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include <list>

#include <iostream>
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "traits.h"
#include "thread.h"
#include "Projectile.h"
#include "Bullet.h"
#include "Timer.h"
#include "Missile.h"

__USING_API

class UserSpaceship
{
public:
    UserSpaceship(ALLEGRO_TIMER *timer, int fps);
    ~UserSpaceship();
    static void run(UserSpaceship *ship);

    void update(double dt);
    void increaseVerticalSpeed();
    void increaseHorizontalSpeed();
    void decreaseVerticalSpeed();
    void decreaseHorizontalSpeed();
    void addBullet();
    void addMissile();
    void hit(const int &damage);

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
        return *(centre);
    }

    inline std::shared_ptr<Point> getCentreShared () const {
        return centre;
    }

    inline std::shared_ptr<Sprite> getSpaceShip() const
    {
        return spaceShip;
    }
    inline std::list<std::shared_ptr<Projectile>> getProj() const
    {
        return _proj;
    }
    inline int getSize() const
    {
        return _size;
    }
    inline bool isDead() const
    {
        return _dead;
    }

    void drawProjectiles();
    void drawLivesBar();

private:
    void checkBoundary();
    void selectShipAnimation();
    void loadSprite();
    void updateProjectiles(double dt);

    std::shared_ptr<Sprite> spaceShip;
    std::shared_ptr<Point> centre;
    ALLEGRO_COLOR color; /**< ship color */
    Vector speed;
    int row; /**<row of animation to be played */
    int col; /**< column of animation to be played */
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;

    std::list<std::shared_ptr<Projectile>> _proj;
    Vector projectileSpeed;
    Timer *_bulletTimer;
    Timer *_missileTimer;
    int _size;
    int _lives;
    int _totalLives;
    bool _dead;
};

#endif