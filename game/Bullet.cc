#include "Bullet.h"

Bullet::Bullet(Point c, ALLEGRO_COLOR color, Vector s) : Projectile(c, color, s)
{
    centre = centre + speed * 0.1;
}

Bullet::~Bullet()
{
}

void Bullet::update(double dt)
{
    centre = centre + speed * dt;
    if ((centre.x > 800) ||
        (centre.x < 0) ||
        (centre.y > 600) ||
        (centre.y < 0))
    {
        live = false;
    }
}

void Bullet::draw()
{
    std::cout << "draw do bullet\n";
    Point tracer = centre + speed * (-0.05);
    al_draw_line(centre.x, centre.y,
                 tracer.x, tracer.y,
                 color, 3);
}
