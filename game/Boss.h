#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include "Sprite.h"
#include "Timer.h"
#include "Vector.h"
#include "Projectile.h"
#include "Bullet.h"
#include "Missile.h"

class Boss : public Enemy
{
public:
    Boss(Point c, ALLEGRO_COLOR color, Vector s, std::shared_ptr<Point> playerCent);
    ~Boss();
    void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
    void deathAnim();
    void selectSprite();
    void deathAnimation(std::shared_ptr<Sprite> death);
    void update(double dt);
    void updateProjectiles(double dt);
    void drawProjectiles();
    void hit();
    void addProjectile();
    void addMissile(Point c, Vector speed);
    void addBullet(Point c, Vector speed);

    bool getFire()
    {
        return _fire;
    }

private:
    int _totalLives;
    int _row;
    int _col;
    int _spriteIndex;
    Vector _projSpeed;
    int _fireSpeed;
    Timer *_delayTimer;
    int _nDeathAnim;
    std::shared_ptr<Point> _playerLocation;
    bool _target;
    bool _fire;
};

#endif