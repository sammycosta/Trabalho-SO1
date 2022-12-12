#ifndef BOSS_MANAGER_H
#define BOSS_MANAGER_H

#include <memory>
#include <list>
#include "Timer.h"
#include "thread.h"
#include "Point.h"
#include "traits.h"
#include "Boss.h"

__USING_API

class BossManager
{
public:
    BossManager(std::shared_ptr<Point> playerCentre, float prevtime);
    ~BossManager();

    static void run(BossManager *bossManager);
    void loadSprites();
    void drawBoss();

    std::shared_ptr<Boss> getBoss()
    {
        return _boss;
    }

private:
    std::shared_ptr<Sprite> _deathSprite;
    std::shared_ptr<Sprite> _bossSprite;
    std::shared_ptr<Boss> _boss;
    float _prevTime;
};

#endif