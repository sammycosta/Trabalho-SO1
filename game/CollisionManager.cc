#include "CollisionManager.h"

CollisionManager::CollisionManager(UserSpaceship *user, EnemySpaceshipManager *enemy)
{
    _userSpaceship = user;
    _enemyManager = enemy;
}

void CollisionManager::run(CollisionManager *manager)
{
    while (true)
    {
        std::cout << "run collision manager\n";
        manager->userCollision();
        manager->enemyCollision();
        manager->userWithEnemyCollision();
        Thread::yield();
    }
}

void CollisionManager::enemyCollision()
{
    std::list<std::shared_ptr<PurpleEnemy>> purpleEnemies = _enemyManager->getPurpleEnemies();
    std::list<std::shared_ptr<Projectile>> userProj = _userSpaceship->getProj();
    if (!(purpleEnemies.empty()) && !(userProj.empty()))
    {
        for (auto p = userProj.begin(); p != userProj.end(); ++p)
        {
            for (auto enemy = purpleEnemies.begin(); enemy != purpleEnemies.end(); ++enemy)
            {
                Point projCentre = (*p)->getCentre();
                Point enemyCentre = (*enemy)->getCentre();
                int enemySize = (*enemy)->getSize();

                if ((projCentre.x > enemyCentre.x - enemySize) &&
                    (projCentre.x < enemyCentre.x + enemySize) &&
                    (projCentre.y > enemyCentre.y - enemySize) &&
                    (projCentre.y < enemyCentre.y + enemySize))
                {
                    (*p)->live = false;
                    (*enemy)->hit();
                    if ((*enemy)->getDead())
                    {
                        // updateScore(player->color);
                    }
                }
            }
        }
    }
}

void CollisionManager::userCollision()
{
    std::list<std::shared_ptr<PurpleEnemy>> purpleEnemies = _enemyManager->getPurpleEnemies();
    if (!(purpleEnemies.empty()))
    {
        for (auto en = purpleEnemies.begin(); en != purpleEnemies.end(); en++)
        {
            if ((*en)->getFire())
            {
                std::list<std::shared_ptr<Projectile>> enemyProjectiles = (*en)->getProjectiles();
                for (auto p = enemyProjectiles.begin(); p != enemyProjectiles.end(); p++)
                {
                    if (collisionPointBox((*p)->getCentre(), _userSpaceship->getCentre(), _userSpaceship->getSize()))
                    {
                        (*p)->live = false;
                        std::cout << "bala atingiu o jogador!\n";
                        _userSpaceship->hit(1);
                    }
                }
            }
        }
    }
}
void CollisionManager::userWithEnemyCollision()
{
    std::list<std::shared_ptr<PurpleEnemy>> purpleEnemies = _enemyManager->getPurpleEnemies();
    if (!purpleEnemies.empty())
        for (auto enemy = purpleEnemies.begin(); enemy != purpleEnemies.end(); ++enemy)
        {
            if (!((*enemy)->getDead()))
            {
                bool doIntersect = hitBoxesIntersect(_userSpaceship->getCentre(), _userSpaceship->getSize(), (*enemy)->getCentre(), (*enemy)->getSize());

                if (doIntersect)
                {
                    (*enemy)->hit();
                    _userSpaceship->hit(1);
                }
            }
        }
}

bool CollisionManager::hitBoxesIntersect(const Point &centre1, const int &size1,
                                         const Point &centre2, const int &size2)
{
    return (abs(centre1.x - centre2.x) < (size1 + size2) &&
            abs(centre1.y - centre2.y) < (size1 + size2));
}

bool CollisionManager::collisionPointBox(const Point &point1, const Point &point2,
                                         const int &size2)
{
    return ((point1.x > point2.x - size2) &&
            (point1.x < point2.x + size2) &&
            (point1.y > point2.y - size2) &&
            (point1.y < point2.y + size2));
}