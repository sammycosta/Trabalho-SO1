#include "BossManager.h"

BossManager::BossManager(std::shared_ptr<Point> playerCentre, float prevTime)
{
    loadSprites();
    _boss = std::make_shared<Boss>(Point(850, 300), al_map_rgb(155, 0, 0), Vector(-50, 0), playerCentre);
    _prevTime = prevTime;
    _finish = false;
}
BossManager::~BossManager()
{
    _deathSprite.reset();
    _bossSprite.reset();
    _boss.reset();
}

void BossManager::run(BossManager *bossManager)
{
    // classe só entra aqui no momento que o boss deve aparece
    float prevTime = bossManager->_prevTime;
    while (!bossManager->_boss->getDead() && !bossManager->_finish)
    {
        float crtTime;
        crtTime = al_current_time();
        double dt = crtTime - prevTime;
        bossManager->_boss->update(dt);
        bossManager->_boss->updateProjectiles(dt);
        prevTime = crtTime;
        Thread::yield();
    }
}

void BossManager::loadSprites()
{
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    _bossSprite = std::make_shared<Sprite>("bossv2.png");
    _deathSprite = std::make_shared<Sprite>("explode.png");

    al_destroy_path(path);
}

void BossManager::drawBoss()
{
    _boss->draw(_bossSprite, _deathSprite);
    _boss->drawProjectiles();
}