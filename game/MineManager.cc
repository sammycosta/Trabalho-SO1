#include "MineManager.h"

MineManager::MineManager()
{
    loadSprites();
    _minesTimer = new Timer(1);
    _minesTimer->create();
    _minesTimer->startTimer();
    _explosionTimer = new Timer(1);
    _explosionTimer->create();
    _explosionTimer->startTimer();
    _mine = nullptr;
    _finish = false;
}

MineManager::~MineManager()
{
    delete (_minesTimer);
    delete (_explosionTimer);
    _explosionSprite.reset();
    _bombSprite.reset();
    if (_mine != nullptr)
    {
        _mine.reset();
    }
}

void MineManager::run(MineManager *mineMan)
{
    float prevTime = 0;
    while (!mineMan->_finish)
    {
        float crtTime;
        crtTime = al_current_time();
        if (mineMan->_mine != nullptr)
        {
            mineMan->_mine->update(crtTime - prevTime);
            mineMan->_mine->updateProjectiles(crtTime - prevTime);
        }

        if (mineMan->_minesTimer->getCount() >= 30)
        {
            mineMan->_explosionTimer->srsTimer();
            mineMan->_minesTimer->srsTimer();
            if (mineMan->_mine == nullptr)
            {
                mineMan->createMine();
            }
        }

        if (mineMan->_mine != nullptr)
        {
            if (mineMan->_explosionTimer->getCount() > 5)
            {
                mineMan->_mine->setFire(true);

                if (mineMan->_explosionTimer->getCount() > 10)
                {
                    mineMan->_explosionTimer->srsTimer();
                    mineMan->_mine.reset();
                    mineMan->_mine = nullptr;
                }
            }
        }

        prevTime = crtTime;
        Thread::yield();
    }
}

void MineManager::loadSprites()
{
    _explosionSprite = std::make_shared<Sprite>("explode.png");
    _bombSprite = std::make_shared<Sprite>("spikebomb.png");
}

void MineManager::createMine()
{
    Point pt(800, 200);
    pt.y = pt.y + (rand() % 200);
    _mine = std::make_shared<Mine>(pt, al_map_rgb(204, 3, 3), Vector(-60, 0));
}

void MineManager::drawMine()
{
    if (_mine != nullptr)
    {
        // if (!_mine->getDead() || _mine->getFire())
        {
            _mine->draw(_bombSprite, _explosionSprite);
        }
        if (!_mine->getFired())
        {
            _mine->drawProjectiles();
        }
    }
}
