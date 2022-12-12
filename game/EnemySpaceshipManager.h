#ifndef ENEMY_SPACESHIP_MANAGER_H
#define ENEMY_SPACESHIP_MANAGER_H

#include <memory>
#include <list>
#include "PurpleEnemy.h"
#include "Timer.h"
#include "thread.h"
#include "Point.h"
#include "traits.h"
#include "BossManager.h"

__USING_API

class EnemySpaceshipManager
{
public:
    EnemySpaceshipManager(int fps, std::shared_ptr<Point> playerCentre);
    ~EnemySpaceshipManager();

    static void run(EnemySpaceshipManager *EnemyManager);
    void loadSprites();
    void spawnPurple();
    void addPurple(const Point &center, const ALLEGRO_COLOR &color, const Vector &speed);
    void drawEnemies();
    void updateEnemies(double dt);

    inline void setFinish(bool finish)
    {
        _finish = finish;
    }

    std::list<std::shared_ptr<Enemy>> getPurpleEnemies()
    {
        return purpleEnemies;
    }

    bool bossExists()
    {
        return _bossManager != nullptr;
    }

    BossManager *_bossManager;
    Thread *_bossManagerThread;

private:
    std::list<std::shared_ptr<Enemy>> purpleEnemies;
    std::shared_ptr<Sprite> purpleEnemySprite;
    std::shared_ptr<Sprite> enemyDeathSprite;

    std::shared_ptr<Timer> purpleSpawnTimer;
    Timer *_bossTimer;
    std::shared_ptr<Point> _playerCentre;
    bool _finish;
};

#endif