#include "Window.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

Window::Window(int w, int h, int fps, ALLEGRO_TIMER *timer, UserSpaceship *userspaceship,
               EnemySpaceshipManager *enemyShip, MineManager *mineManager,
               KeyboardListener *keyboardListener) : _displayWidth(w),
                                                     _displayHeight(h),
                                                     _fps(fps)

{
    _timer = timer;
    _userSpaceship = userspaceship;
    _enemyShip = enemyShip;
    _mineManager = mineManager;
    _keyboardListener = keyboardListener;

    if ((_display = al_create_display(_displayWidth, _displayHeight)) == NULL)
    {
        std::cout << "Cannot initialize the display\n";
        exit(1);
    }
    // initialize addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    // fila de display
    if ((_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }
    al_register_event_source(_eventQueue, al_get_display_event_source(_display));
    al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());

    loadBackgroundSprite();
    _finish = false;
}

Window::~Window()
{
    // if (_timer != NULL)
    //     al_destroy_timer(_timer);
    if (_eventQueue != NULL)
        al_destroy_event_queue(_eventQueue);
    if (_display != NULL)
        al_destroy_display(_display);

    bg.reset();
    fg.reset();
}

void Window::run(Window *win)
{
    float prevTime = 0;
    while (!win->_finish)
    {
        win->gameLoop(prevTime);
        Thread::yield();
    }
}

void Window::gameLoop(float &prevTime)
{

    ALLEGRO_EVENT event;
    bool redraw = true;
    float crtTime;

    // get event
    al_wait_for_event(_eventQueue, &event);

    // _display closes
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        setFinish(true);
    }

    if (_userSpaceship->isDead() || _keyboardListener->getFinish() || _enemyShip->getFinish())
    {
        setFinish(true);
        return;
    }

    // timer
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        crtTime = al_current_time();
        update(crtTime - prevTime);
        prevTime = crtTime;
        redraw = true;
    }

    // render
    if (redraw && al_is_event_queue_empty(_eventQueue))
    {
        redraw = false;
        draw();
        al_flip_display();
    }
}

void Window::draw()
{
    drawBackground();
    drawShip(0);
    _enemyShip->drawEnemies();
    _mineManager->drawMine();

    if (_enemyShip->_bossManager != nullptr && _enemyShip->_bossManager->getBoss())
    {
        _enemyShip->_bossManager->drawBoss();
    }
}

void Window::drawShip(int flags)
{
    std::shared_ptr<Sprite> sprite = _userSpaceship->getSpaceShip();
    int row = _userSpaceship->getRow();
    int col = _userSpaceship->getCol();
    Point centre = _userSpaceship->getCentre();
    sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
    _userSpaceship->drawProjectiles();
    _userSpaceship->drawLivesBar();
}

void Window::drawBackground()
{
    bg->draw_parallax_background(bgMid.x, 0);
}

void Window::loadBackgroundSprite()
{
    // represents the middle of the image width-wise, and top height-wise
    bgMid = Point(0, 0);
    fgMid = Point(800, 0);
    fg2Mid = Point(300, 300);
    bgSpeed = Vector(50, 0);
    fgSpeed = Vector(-90, 0);

    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));
    // sprites
    bg = std::make_shared<Sprite>("BGstars.png"); // fundo da tela - background
    // delete path
    al_destroy_path(path);
}

void Window::update(double dt)
{
    // background
    bgMid = bgMid + bgSpeed * dt;
    if (bgMid.x >= 800)
    {
        bgMid.x = 0;
    }
}
