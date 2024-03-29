#include "EnemySpaceshipManager.h"

EnemySpaceshipManager::EnemySpaceshipManager(int fps, std::shared_ptr<Point> playerCentre)
{
    _playerCentre = playerCentre;
    _bossManager = nullptr;

    loadSprites();

    purpleSpawnTimer = std::make_shared<Timer>(fps);
    purpleSpawnTimer->create();
    purpleSpawnTimer->startTimer();

    _bossTimer = new Timer(1);
    _bossTimer->create();
    _bossTimer->startTimer();
    _finish = false;
}

EnemySpaceshipManager::~EnemySpaceshipManager()
{
    purpleEnemies.clear();
    purpleEnemySprite.reset();
    enemyDeathSprite.reset();
    purpleSpawnTimer.reset();
    delete _bossTimer;
    _playerCentre.reset();
}

void EnemySpaceshipManager::run(EnemySpaceshipManager *enemyManager)
{
    float prevTime = 0;
    while (!enemyManager->_finish)
    {
        float crtTime;

        crtTime = al_current_time();
        enemyManager->updateEnemies(crtTime - prevTime);

        if (enemyManager->purpleSpawnTimer->getCount() > 200 && !enemyManager->bossExists())
        {
            enemyManager->spawnPurple();
            enemyManager->purpleSpawnTimer->srsTimer();
        }

        if (enemyManager->_bossTimer->getCount() > 60 && !enemyManager->bossExists())
        {
            enemyManager->_bossManager = new BossManager(enemyManager->_playerCentre, prevTime);
            enemyManager->_bossManagerThread = new Thread(EnemySpaceshipManager::callRunBoss, enemyManager);
        }

        prevTime = crtTime;

        Thread::yield();

        if (enemyManager->bossExists() && enemyManager->getPurpleEnemies().empty())
        {
            enemyManager->_bossManagerThread->join();
        }
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
    std::list<std::shared_ptr<Enemy>> newPe;
    if (!purpleEnemies.empty())
    {
        for (auto p = purpleEnemies.begin(); p != purpleEnemies.end(); ++p)
        {
            (*p)->update(dt);

            (*p)->addProjectile();

            if (!((*p)->getDead()))
            {
                newPe.push_back(*p);
            }
        }
        purpleEnemies.clear();
        purpleEnemies.assign(newPe.begin(), newPe.end());
    }
}

void EnemySpaceshipManager::callRunBoss(EnemySpaceshipManager *manager)
{
    BossManager::run(manager->_bossManager);

    manager->setFinish(true);
    delete manager->_bossManager;
    manager->_bossManagerThread->thread_exit(6);
}