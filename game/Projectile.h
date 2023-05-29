#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>

#include "Point.h"
#include "Vector.h"

class Projectile
{
public:
    Point centre;
    ALLEGRO_COLOR color;
    Vector speed;
    bool live;

    Projectile(Point point, ALLEGRO_COLOR color, Vector s) : centre(point), color(color), speed(s)
    {
        live = true;
    }

    virtual ~Projectile() {}

    void update(double dt) {
        centre = centre + speed * dt;
        if ((centre.x > 800) ||
            (centre.x < 0) ||
            (centre.y > 600) ||
            (centre.y < 0))
        {
            live = false;
        }
    }

    virtual void draw(){};

    bool isAlive()
    {
        return live;
    };

    Point getCentre() {
        return centre;
    }
};

#endif