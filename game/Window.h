#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "../Sprite.h"
#include "../library_threads/thread.h"
// #include "../Vector.h"
#include "UserSpaceship.h"

class Window
{
public:
  Window(int w, int h, int fps);
  ~Window();

  void run();

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
  ALLEGRO_TIMER *_timer;
  ALLEGRO_EVENT_QUEUE *_eventQueue;
  ALLEGRO_DISPLAY *_display;
  bool _finish;

  UserSpaceship *userSpaceship;

  Thread *thread = new Thread();
};

#endif
