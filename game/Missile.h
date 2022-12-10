#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"
#include "Sprite.h"
#include <memory>
#include <vector>

class Missile : public Projectile
{
private:
    std::vector<std::shared_ptr<Sprite>> _spritesVector;
    double _angle;
    int _imageNum;

public:
    Missile(Point point, ALLEGRO_COLOR color, Vector s);
    ~Missile();
    // void update(double dt);
    void draw();
    void load_sprites();
};

#endif