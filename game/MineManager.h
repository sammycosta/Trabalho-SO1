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

    std::shared_ptr<Mine> getMine()
    {
        return _mine;
    }

    bool mineExists()
    {
        return _mine != nullptr;
    }

    inline bool getFinish() const
    {
        return _finish;
    }

    inline void setFinish(bool finish)
    {
        _finish = finish;
    }

private:
    Timer *_minesTimer;
    Timer *_explosionTimer;
    std::shared_ptr<Sprite> _explosionSprite;
    std::shared_ptr<Sprite> _bombSprite;
    std::shared_ptr<Mine> _mine;
    bool _finish;
};

#endif