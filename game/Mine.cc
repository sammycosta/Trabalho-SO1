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
    dead = false;
    // _fireTimer = std::make_shared<Timer> (60);
    // _fireTimer>create();
    // _fireT->startTimer();
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
    if (centre.x < 400 && _fire)
    {
        std::cout << "minaaaaaaaaaa atirando\n";
        dead = true;
    }
}