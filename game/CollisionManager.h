#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <memory>
#include <list>
#include "Timer.h"
#include "thread.h"
#include "Point.h"
#include "traits.h"
#include "UserSpaceship.h"
#include "EnemySpaceshipManager.h"
#include "MineManager.h"
#include "BossManager.h"

__USING_API

class CollisionManager
{
public:
    CollisionManager(UserSpaceship *user, EnemySpaceshipManager *enemy, MineManager *mineMan);
    ~CollisionManager(){};

    static void run(CollisionManager *collisionManager);

    inline void setFinish(bool finish)
    {
        _finish = finish;
    }

private:
    void enemyCollision();
    void userCollision();
    void userWithEnemyCollision();

    bool hitBoxesIntersect(const Point &centre1, const int &size1,
                           const Point &centre2, const int &size2);

    bool collisionPointBox(const Point &point1, const Point &point2,
                           const int &size2);

    UserSpaceship *_userSpaceship;
    EnemySpaceshipManager *_enemyManager;
    MineManager *_mineManager;
    bool _finish;
};

#endif