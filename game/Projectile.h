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

    virtual void update(double dt) {}

    virtual void draw(){};

    bool isAlive()
    {
        return live;
    };
};

#endif