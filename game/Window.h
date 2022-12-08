#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "../Sprite.h"
#include "Vector.h"
#include "UserSpaceship.h"

class Window
{
public:
  Window(int w, int h, int fps);
  ~Window();

  void run();

  void gameLoop();
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
  ALLEGRO_DISPLAY *_display;

  UserSpaceship *userSpaceship;
};

#endif
