#include "EnemySpaceshipManager.h"

EnemySpaceshipManager::EnemySpaceshipManager(int fps)
{
    loadSprites();

    purpleSpawnTimer = std::make_shared<Timer>(fps);
    purpleSpawnTimer->create();
    purpleSpawnTimer->startTimer();
}

EnemySpaceshipManager::~EnemySpaceshipManager()
{
}

void EnemySpaceshipManager::run(EnemySpaceshipManager *EnemyManager)
{
    float prevTime = 0;
    while (true)
    {
        std::cout << "run enemy manager\n";
        float crtTime;

        crtTime = al_current_time();
        EnemyManager->updateEnemies(crtTime - prevTime);
        prevTime = crtTime;

        // regra random
        if (EnemyManager->purpleSpawnTimer->getCount() > 20 && EnemyManager->purpleEnemies.size() < 3)
        {
            EnemyManager->spawnPurple();
            EnemyManager->purpleSpawnTimer->srsTimer();
        }

        Thread::yield();
    }
}

void EnemySpaceshipManager::loadSprites()
{
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "/resources");
    al_change_directory(al_path_cstr(path, '/'));

    purpleEnemySprite = std::make_shared<Sprite>("EnemyBasic.png");
    enemyDeathSprite = std::make_shared<Sprite>("explode.png");

    al_destroy_path(path);
}

void EnemySpaceshipManager::spawnPurple()
{
    addPurple(Point(800, 300), al_map_rgb(246, 64, 234), Vector(-180, 0));
    addPurple(Point(900, 350), al_map_rgb(246, 64, 234), Vector(-180, 0));
    addPurple(Point(900, 250), al_map_rgb(246, 64, 234), Vector(-180, 0));
    addPurple(Point(1000, 400), al_map_rgb(246, 64, 234), Vector(-180, 0));
    addPurple(Point(1000, 200), al_map_rgb(246, 64, 234), Vector(-180, 0));
    addPurple(Point(1100, 100), al_map_rgb(246, 64, 234), Vector(-180, 0));
    addPurple(Point(1100, 500), al_map_rgb(246, 64, 234), Vector(-180, 0));
}

void EnemySpaceshipManager::addPurple(const Point &center, const ALLEGRO_COLOR &color, const Vector &speed)
{
    purpleEnemies.push_back(std::make_shared<PurpleEnemy>(center, color, speed));
}

void EnemySpaceshipManager::drawEnemies()
{
    if (purpleEnemies.empty() == false)
    {
        for (auto p = purpleEnemies.begin(); p != purpleEnemies.end(); ++p)
        {
            if ((*p)->getLives() > 0 || (*p)->getdAnim_complete() != true)
            {
                (*p)->draw(purpleEnemySprite, enemyDeathSprite);
            }
        }
    }
}

void EnemySpaceshipManager::updateEnemies(double dt)
{
    std::list<std::shared_ptr<PurpleEnemy>> newPe;
    if (!purpleEnemies.empty())
    {
        for (auto p = purpleEnemies.begin(); p != purpleEnemies.end(); ++p)
        {
            (*p)->update(dt);

            (*p)->addBullet();

            if (!((*p)->getDead()))
            {
                newPe.push_back(*p);
            }
        }
        purpleEnemies.clear();
        purpleEnemies.assign(newPe.begin(), newPe.end());
    }
}