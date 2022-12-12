#include "Mine.h"

Mine::Mine(Point centre, ALLEGRO_COLOR color, Vector s) : Enemy(centre, color, s)
{
    _row = 0;
    _col = 0;
    lives = 3;
    _size = 20;
    _dAnim = 0;
    _dAnimComplete = false;
    _fire = false;
    _fired = false;
    dead = false;

    _delayTimer = std::make_shared<Timer>(60);
    _delayTimer->create();
    _delayTimer->startTimer();
}

Mine::~Mine()
{
}

void Mine::hit()
{
    lives = lives - 1;
    _col++;
    if (lives < 1)
        dead = true;
}

void Mine::draw(std::shared_ptr<Sprite> mine, std::shared_ptr<Sprite> death)
{
    if (!dead)
    {
        mine->draw_region(_row, _col, 40, 41, centre, 0);
    }
    else
    {
        if (_dAnim < 5)
            deathAnimation(death);
        else
        {
            _dAnimComplete = true;
            _fire = false;
        }
    }
}

void Mine::deathAnimation(std::shared_ptr<Sprite> enemyDeath)
{

    enemyDeath->draw_death_anim(_dAnim, centre, 0);
    _dAnim++;
}

void Mine::update(double dt)
{
    centre = centre + speed * dt;
    if (centre.x < 0)
        dead = true;
    if (centre.x < 670 && _row == 0)
    {
        _row++;
    }
    if (centre.x < 540 && _row == 1)
    {
        _row++;
    }
    if (_fire)
    {
        addProjectile();
        dead = true;
    }
}

void Mine::addProjectile()
{
    if (_delayTimer->getCount() > 3)
    {
        for (int i = -500; i <= 500; i += 325)
        {
            for (int j = -500; j <= 500; j += 325)
            {
                _proj.push_back(std::make_shared<Bullet>(centre, color, Vector(i, j)));
            }
        }
        _delayTimer->srsTimer();
    }
}

void Mine::updateProjectiles(double dt)
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

void Mine::drawProjectiles()
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
