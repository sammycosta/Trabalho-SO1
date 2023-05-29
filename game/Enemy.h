#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>

#include <memory>

#include "Point.h"
#include "Vector.h"
#include "Projectile.h"
#include <list>

class Sprite;

class Enemy
{

public:
    Enemy(Point p, ALLEGRO_COLOR color, Vector s) : centre(p), color(color), speed(s), dead(false)
    {
    }

    virtual ~Enemy() {}

    virtual void update(double dt) {}

    virtual void hit() = 0;

    virtual void draw(std::shared_ptr<Sprite> sprite, std::shared_ptr<Sprite> deathSprite) = 0;

    virtual bool getFire() = 0;

    virtual void addProjectile() = 0;

    bool getdAnim_complete()
    {
        return _dAnimComplete;
    }

    bool getDead()
    {
        return dead;
    }

    Point getCentre()
    {
        return centre;
    }

    int getLives()
    {
        return lives;
    }

    int getSize()
    {
        return _size;
    }

    std::list<std::shared_ptr<Projectile>> getProjectiles()
    {
        return _proj;
    }

    ALLEGRO_COLOR getColor() {
        return color;
    }

    void updateProjectiles(double dt)
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

    void drawProjectiles()
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

    Point centre;
    ALLEGRO_COLOR color;
    Vector speed;
    bool dead;
    int lives;
    bool _dAnimComplete;
    int _size;
    std::list<std::shared_ptr<Projectile>> _proj;
};

#endif