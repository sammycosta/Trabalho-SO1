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

__USING_API

class CollisionManager
{
public:
    CollisionManager(UserSpaceship *user, EnemySpaceshipManager *enemy);
    ~CollisionManager(){};

    static void run(CollisionManager *collisionManager);

private:
    void enemyCollision();
    void userCollision();

    UserSpaceship *_userSpaceship;
    EnemySpaceshipManager *_enemyManager;
};

#endif