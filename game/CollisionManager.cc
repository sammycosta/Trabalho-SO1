#include "CollisionManager.h"

CollisionManager::CollisionManager(UserSpaceship *user, EnemySpaceshipManager *enemy,
                                   MineManager *mineMan)
{
    _userSpaceship = user;
    _enemyManager = enemy;
    _mineManager = mineMan;
}

void CollisionManager::run(CollisionManager *manager)
{
    bool condition = true;
    while (manager->_finish && condition)
    {
        manager->userCollision();
        manager->enemyCollision();
        manager->userWithEnemyCollision();
        Thread::yield();
        condition = manager->_userSpaceship != nullptr && manager->_enemyManager != nullptr && manager->_mineManager != nullptr;
    }
}

void CollisionManager::enemyCollision()
{
    std::list<std::shared_ptr<Enemy>> enemies = _enemyManager->getPurpleEnemies();
    if (_mineManager->mineExists())
    {
        enemies.push_back(_mineManager->getMine());
    }

    if (_enemyManager->_bossManager != nullptr && (_enemyManager->_bossManager->getBoss() != nullptr))
    {
        std::shared_ptr<Enemy> boss = _enemyManager->_bossManager->getBoss();
        enemies.push_back(boss);
    }

    std::list<std::shared_ptr<Projectile>> userProj = _userSpaceship->getProj();
    if (!(enemies.empty()) && !(userProj.empty()))
    {
        for (auto p = userProj.begin(); p != userProj.end(); ++p)
        {
            for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
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
    enemies.clear();
    userProj.clear();
}

void CollisionManager::userCollision()
{
    std::list<std::shared_ptr<Enemy>> enemies = _enemyManager->getPurpleEnemies();

    if (_mineManager->mineExists())
    {
        std::shared_ptr<Enemy> mine = _mineManager->getMine();
        enemies.push_back(mine);
    }

    if (_enemyManager->_bossManager != nullptr && _enemyManager->_bossManager->getBoss())
    {
        std::shared_ptr<Enemy> boss = _enemyManager->_bossManager->getBoss();
        enemies.push_back(boss);
    }

    if (!(enemies.empty()))
    {
        // std::cout << enemies.size() << "\n";

        for (auto en = enemies.begin(); en != enemies.end(); en++)
        {

            std::list<std::shared_ptr<Projectile>> enemyProjectiles = (*en)->getProjectiles();
            // std::cout << enemyProjectiles.size() << "\n";
            for (auto p = enemyProjectiles.begin(); p != enemyProjectiles.end(); p++)
            {
                // std::cout << "analisando balinha \n";
                if (collisionPointBox((*p)->getCentre(), _userSpaceship->getCentre(), _userSpaceship->getSize()))
                {
                    (*p)->live = false;
                    std::cout << "bala atingiu o jogador!\n";
                    _userSpaceship->hit(1);
                }
            }
            enemyProjectiles.clear();
        }
    }
    enemies.clear();
}
void CollisionManager::userWithEnemyCollision()
{
    std::list<std::shared_ptr<Enemy>> enemies = _enemyManager->getPurpleEnemies();

    if (_mineManager->mineExists())
    {
        std::shared_ptr<Enemy> mine = _mineManager->getMine();
        enemies.push_back(mine);
    }

    if (_enemyManager->_bossManager != nullptr && _enemyManager->_bossManager->getBoss())
    {
        std::shared_ptr<Enemy> boss = _enemyManager->_bossManager->getBoss();
        enemies.push_back(boss);
    }

    if (!enemies.empty())
        for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
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
    enemies.clear();
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