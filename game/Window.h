#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "Vector.h"
#include "Point.h"
#include "UserSpaceship.h"
#include "traits.h"
#include "KeyboardListener.h"
#include "thread.h"
#include "EnemySpaceshipManager.h"
#include "MineManager.h"
#include "BossManager.h"
#include "Timer.h"

__USING_API

class Window
{
public:
  Window(int w, int h, int fps, ALLEGRO_TIMER *_timer, UserSpaceship *userspaceship,
         EnemySpaceshipManager *enemyShip, MineManager *mineManager, KeyboardListener *KeyboardListener);
  ~Window();

  static void run(Window *win);

  void gameLoop(float &prevTime);
  void draw();
  void drawShip(int flags);
  void drawBackground();
  void loadBackgroundSprite();
  void update(double dt);

  inline int getWidth() const
  {
    return _displayWidth;
  }
  inline int getHeight() const
  {
    return _displayHeight;
  }
  inline int getFps() const
  {
    return _fps;
  }

  inline void setFinish(bool finish)
  {
    _finish = finish;
    _userSpaceship->setFinish(true);
    _enemyShip->setFinish(true);
    _mineManager->setFinish(true);
    _keyboardListener->setFinish(true);
    if (_enemyShip != nullptr && _enemyShip->_bossManager != nullptr)
    {
      _enemyShip->_bossManager->setFinish(true);
    }
  }

private:
  Point bgMid; /**<point used by the background to draw from */
  Point fgMid;
  Point fg2Mid;
  Vector bgSpeed; /**<background movement speed */
  Vector fgSpeed;
  std::shared_ptr<Sprite> bg; /**<shared pointer to background animation */
  std::shared_ptr<Sprite> fg;

  int _displayWidth;
  int _displayHeight;
  int _fps;
  ALLEGRO_EVENT_QUEUE *_eventQueue;
  ALLEGRO_TIMER *_timer;
  ALLEGRO_DISPLAY *_display;
  bool _finish;

  UserSpaceship *_userSpaceship;
  EnemySpaceshipManager *_enemyShip;
  MineManager *_mineManager;
  KeyboardListener *_keyboardListener;
};

#endif
