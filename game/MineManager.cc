#include "MineManager.h"

MineManager::MineManager()
{
    loadSprites();
    _minesTimer = new Timer(1);
    _minesTimer->create();
    _minesTimer->startTimer();
    _mine = nullptr;
}

MineManager::~MineManager()
{
    delete (_minesTimer);
    _explosionSprite.reset();
    _bombSprite.reset();
}

void MineManager::run(MineManager *mineMan)
{
    float prevTime = 0;
    while (true)
    {
        std::cout << "run mine manager\n";
        if (mineMan->_mine != nullptr)
        {

            float crtTime;
            crtTime = al_current_time();
            mineMan->_mine->update(crtTime - prevTime);
            prevTime = crtTime;

            if (mineMan->_mine->getDead() && !mineMan->_mine->getFire())
            {
                delete (mineMan->_mine);
                mineMan->_mine = nullptr;
            }
        }

        if (mineMan->_minesTimer->getCount() >= 5)
        {
            if (mineMan->_mine == nullptr)
            {
                std::cout << "criou mina\n";
                mineMan->createMine();
            }

            if (mineMan->_minesTimer->getCount() > 10)
            {
                mineMan->_mine->setFire(true);
                mineMan->_minesTimer->srsTimer();
            }
        }
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
    _mine = new Mine(pt, al_map_rgb(204, 3, 3), Vector(-60, 0));
}

void MineManager::drawMine()
{
    if (_mine != nullptr)
    {
        std::cout << "draw mine \n";
        if (!_mine->getDead() || _mine->getFire())
        {
            _mine->draw(_bombSprite, _explosionSprite);
        }
    }
}
