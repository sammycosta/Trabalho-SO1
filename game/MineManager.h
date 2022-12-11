#ifndef MINE_MANAGER_H
#define MINE_MANAGER_H

#include "Timer.h"
#include "Mine.h"
#include "thread.h"
#include "Point.h"
#include "traits.h"
__USING_API

class MineManager
{
public:
    MineManager();
    ~MineManager();
    static void run(MineManager *mineMan);
    void loadSprites();
    void createMine();
    void drawMine();

private:
    Timer *_minesTimer;
    std::shared_ptr<Sprite> _explosionSprite;
    std::shared_ptr<Sprite> _bombSprite;
    Mine *_mine;
};

#endif