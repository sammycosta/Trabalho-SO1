/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "Sprite.h"
#include "Vector.h"
#include "Action.h"

// forward declarations
class Menu;
class Root;

class Engine
{

public:
   Engine(int w, int h, int fps);
   ~Engine();

   void init();
   void run();
   void draw(); // WINDOW
   void update(double dt); 

   void gameLoop(float &prevTime); // WINDOW

   act::action input(ALLEGRO_KEYBOARD_STATE &);              // KEYBOARD_LISTENER
   void drawShip(std::shared_ptr<Sprite> sprite, int flags); // WINDOW
   void drawBackground();                                    // WINDOW

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
   void loadSprites();
   // Checks data of the spaceship
   void checkBoundary();       // USER_SPACESHIP
   void selectShipAnimation(); // USER_SPACESHIP
   std::shared_ptr<Sprite> spaceShip;
   // USER_SPACESHIP
   Point centre; /**< ship position */
   // USER_SPACESHIP
   ALLEGRO_COLOR color; /**< ship color */
   // USER_SPACESHIP
   Vector speed; /**< movement speed in any direction */
   // USER_SPACESHIP
   int row; /**<row of animation to be played */
   // USER_SPACESHIP
   int col; /**< column of animation to be played */
   // USER_SPACESHIP

   // WINDOW
   // Background
   Point bgMid; /**<point used by the background to draw from */
   Point fgMid;
   Point fg2Mid;
   Vector bgSpeed; /**<background movement speed */
   Vector fgSpeed;
   std::shared_ptr<Sprite> bg; /**<shared pointer to background animation */
   std::shared_ptr<Sprite> fg;

   // general game variables
   int _displayWidth;  // WINDOW
   int _displayHeight; // WINDOW
   int _fps;           // WINDOW
   // allegro objects
   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *_eventQueue;
   ALLEGRO_DISPLAY *_display; // WINDOW

   bool _finish;
};

#endif
