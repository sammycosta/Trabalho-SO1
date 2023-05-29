#ifndef BULLET_H
#define BULLET_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "Point.h"
#include "Projectile.h"

class Bullet : public Projectile
{
public:
    Bullet(Point point, ALLEGRO_COLOR color, Vector s);
    ~Bullet();
    // void update(double dt);
    void draw();

private:
};

#endif