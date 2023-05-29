#ifndef MINE_H
#define MINE_H

#include "Enemy.h"
#include "Sprite.h"
#include "Timer.h"
#include "Projectile.h"
#include "Bullet.h"
#include <list>

class Mine : public Enemy
{
public:
    Mine(Point c, ALLEGRO_COLOR color, Vector s);
    ~Mine();

    void hit();
    void draw(std::shared_ptr<Sprite> mine, std::shared_ptr<Sprite> deathSprite);
    void deathAnimation(std::shared_ptr<Sprite> enemyDeath);
    void update(double dt);
    void addProjectile();

    bool getFire() { return _fire; }
    bool getFired() { return _fired; }

    void setFire(bool fire)
    {
        _fire = fire;
    }

private:
    bool _fire;
    bool _fired;
    int _dAnim;
    int _row, _col;
    std::shared_ptr<Timer> _delayTimer;
};

#endif