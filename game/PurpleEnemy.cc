#include "PurpleEnemy.h"
#include "Bullet.h"

PurpleEnemy::PurpleEnemy(Point c, ALLEGRO_COLOR color, Vector s) : Enemy(c, color, s)
{
    _fireSpeed = rand() % 50 + 30;
    _bulletSpeed = Vector(-400, 0);
    lives = 1;
    _delayTimer = std::make_shared<Timer>(60);
    _delayTimer->create();
    _delayTimer->startTimer();
    _dAnimComplete = false;
    _size = 20;
}

PurpleEnemy::~PurpleEnemy()
{
    _delayTimer.reset();
}

void PurpleEnemy::hit()
{
    lives = lives - 1;
    if (lives < 1)
    {
        dead = true;
    }
}

void PurpleEnemy::update(double dt)
{
    centre = centre + speed * dt;

    updateProjectiles(dt);

    if (centre.x < 0)
    {
        dead = true;
        return;
    }
}

void PurpleEnemy::draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath)
{
    if (dead == false)
    {
        enemyShip->draw_tinted(centre, color, 0);
    }
    else
    {
        if (_nDeathAnim < 5)
            deathAnimation(enemyDeath);
        else
            _dAnimComplete = true;
    }
    drawProjectiles();
}

void PurpleEnemy::deathAnimation(std::shared_ptr<Sprite> enemyDeath)
{
    enemyDeath->draw_death_anim(_nDeathAnim, centre, 0);
    _nDeathAnim++;
}

void PurpleEnemy::addProjectile()
{
    if (_delayTimer->getCount() > _fireSpeed)
    {
        _proj.push_back(std::make_shared<Bullet>(centre + Point(-20, 0), color, _bulletSpeed + Vector(0, 40)));
        _proj.push_back(std::make_shared<Bullet>(centre + Point(-20, 0), color, _bulletSpeed + Vector(0, -40)));
        _delayTimer->srsTimer();
    }
}

bool PurpleEnemy::getFire()
{
    return !_proj.empty();
}
