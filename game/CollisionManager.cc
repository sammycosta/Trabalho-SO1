#include "CollisionManager.h"

CollisionManager::CollisionManager(UserSpaceship *user, EnemySpaceshipManager *enemy)
{
    _userSpaceship = user;
    _enemyManager = enemy;
}

void CollisionManager::run(CollisionManager *manager)
{
}

void CollisionManager::enemyCollision()
{
    std::list<std::shared_ptr<PurpleEnemy>> purpleEnemies = _enemyManager->getPurpleEnemies();
    std::list<std::shared_ptr<Projectile>> userProj = _userSpaceship->getProj();
    if (!(purpleEnemies.empty()) && !(userProj.empty()))
    {
    }
}