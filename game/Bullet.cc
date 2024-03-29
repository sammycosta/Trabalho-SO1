#include "Bullet.h"

Bullet::Bullet(Point c, ALLEGRO_COLOR color, Vector s) : Projectile(c, color, s)
{
    centre = centre + speed * 0.1;
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
    Point tracer = centre + speed * (-0.05);
    al_draw_line(centre.x, centre.y,
                 tracer.x, tracer.y,
                 color, 3);
}
