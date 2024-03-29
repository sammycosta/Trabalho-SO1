#ifndef PURPLE_ENEMY_H
#define PURPLE_ENEMY_H

#include "Enemy.h"
#include "Timer.h"
#include "memory"
#include <string>
#include <list>
#include "Projectile.h"
#include "Sprite.h"
#include "Bullet.h"

class PurpleEnemy : public Enemy
{
public:
    PurpleEnemy(Point c, ALLEGRO_COLOR color, Vector s);
    ~PurpleEnemy();
    void hit();
    void draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath);
    void update(double dt);
    void deathAnimation(std::shared_ptr<Sprite> enemyDeath);
    void addProjectile();
    bool getFire();

private:
    Vector _bulletSpeed;
    int _fireSpeed;
    std::shared_ptr<Timer> _delayTimer;
    int _nDeathAnim;
};

#endif