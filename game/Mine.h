#ifndef MINE_H
#define MINE_H

#include "Enemy.h"
#include "Sprite.h"
#include "Timer.h"

class Mine : public Enemy
{
public:
    Mine(Point c, ALLEGRO_COLOR color, Vector s);
    ~Mine();

    void hit();
    // trocar nome em enemy de ship?
    void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
    void deathAnimation(std::shared_ptr<Sprite> enemyDeath);
    void update(double dt);

    bool getFire() { return _fire; }
    void setFire(bool fire)
    {
        _fire = fire;
    }

private:
    bool _fire;
    int _dAnim;
    int _row, _col;
    // std::shared_ptr<Timer> fireTimer;

};

#endif