#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>

#include <memory>

#include "Point.h"
#include "Vector.h"

class Sprite;

class Enemy
{

public:
    Enemy(Point p, ALLEGRO_COLOR color, Vector s) : centre(p), color(color), speed(s), dead(false)
    {
    }

    virtual ~Enemy() {}

    void update(double dt) {}

    // /** @fn set fire
    //  * @brief used to reset the boolean flag that represents when an enemy is able to fire
    //  * @param f boolean value to Fire to
    //  */
    // virtual void setFire(bool f) = 0;

    // /** @fn getColor
    //  * @brief getter method to return the color value of an enemy
    //  */
    // virtual ALLEGRO_COLOR getColor() = 0;

    // /** @fn getProjSpeed
    //  *   @return returns a vector representing Projectile Speed
    //  */
    // virtual Vector getProjSpeed() = 0;

    // // /** @fn getSize
    // //  *   @return returns size integer
    // //  */
    // // virtual int getSize() = 0;

    bool getdAnim_complete()
    {
        return _dAnimComplete;
    }

    bool getDead()
    {
        return dead;
    }

    virtual bool getFire() = 0;

    Point getCentre()
    {
        return centre;
    }

    virtual void hit() = 0;

    virtual void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death) = 0;

    int getLives()
    {
        return lives;
    }

    ALLEGRO_COLOR color;
    Vector speed;
    bool dead;
    int lives;
    Point centre;
    bool _dAnimComplete;
};

#endif