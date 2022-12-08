#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

class Window {
  public:
  Window(int w, int h, int fps);
  ~Window();

  void run();

  void gameLoop();
  
  void drawShip(std::shared_ptr<Sprite> sprite, int flags);
  void drawBackground();
}

#endif
