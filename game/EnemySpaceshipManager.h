#ifndef ENEMY_SPACESHIP_MANAGER_H
#define ENEMY_SPACESHIP_MANAGER_H

#include <memory>
#include <list>
#include "PurpleEnemy.h"
#include "Timer.h"
#include "thread.h"
#include "Point.h"
#include "traits.h"

__USING_API

class EnemySpaceshipManager
{
public:
    EnemySpaceshipManager(int fps);
    ~EnemySpaceshipManager();

    static void run(EnemySpaceshipManager *EnemyManager);
    void loadSprites();
    void spawnPurple();
    void addPurple(const Point &center, const ALLEGRO_COLOR &color, const Vector &speed);
    void drawEnemies();
    void updateEnemies(double dt);

private:
    std::list<std::shared_ptr<PurpleEnemy>> purpleEnemies;
    std::shared_ptr<Sprite> purpleEnemySprite;
    std::shared_ptr<Sprite> enemyDeathSprite;

    std::shared_ptr<Timer> purpleSpawnTimer;
};

#endif