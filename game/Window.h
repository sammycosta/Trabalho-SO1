#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "../Vector.h"
#include "../Point.h"
#include "UserSpaceship.h"
#include "../library_threads/traits.h"
#include "../library_threads/thread.h"

__USING_API

class Window
{
public:
  Window(int w, int h, int fps, ALLEGRO_EVENT_QUEUE *timerQueue, UserSpaceship *userspaceship);
  ~Window();

  static void run();

  static void gameLoop(float &prevTime);
  static void draw();
  static void drawShip(int flags);
  static void drawBackground();
  void loadBackgroundSprite();
  static void update(double dt);

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

  Thread *window_thread;

private:
  static Point bgMid; /**<point used by the background to draw from */
  static Point fgMid;
  static Point fg2Mid;
  static Vector bgSpeed; /**<background movement speed */
  static Vector fgSpeed;
  static std::shared_ptr<Sprite> bg; /**<shared pointer to background animation */
  static std::shared_ptr<Sprite> fg;

  int _displayWidth;
  int _displayHeight;
  int _fps;
  static ALLEGRO_EVENT_QUEUE *_eventQueue;
  static ALLEGRO_EVENT_QUEUE *_timerQueue;
  ALLEGRO_DISPLAY *_display;
  static bool _finish;

  static UserSpaceship *userSpaceship;
};

#endif
