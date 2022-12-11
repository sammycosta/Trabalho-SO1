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
}

PurpleEnemy::~PurpleEnemy()
{
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

void PurpleEnemy::addBullet()
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

void PurpleEnemy::updateProjectiles(double dt)
{
    std::list<std::shared_ptr<Projectile>> newProj;
    if (_proj.empty() == false)
    {
        for (auto p = _proj.begin(); p != _proj.end(); ++p)
        {
            p->get()->update(dt);
            if (p->get()->isAlive())
            {
                newProj.push_back(*p);
            }
        }
        _proj.clear();
        _proj.assign(newProj.begin(), newProj.end());
    }
}

void PurpleEnemy::drawProjectiles()
{
    if (_proj.empty() == false)
    {
        for (auto p = _proj.begin(); p != _proj.end(); ++p)
        {
            if (p->get()->isAlive())
            {
                p->get()->draw();
            }
        }
    }
}