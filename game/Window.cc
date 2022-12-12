#include "Window.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

Window::Window(int w, int h, int fps, ALLEGRO_TIMER *timer, UserSpaceship *userspaceship,
               EnemySpaceshipManager *enemyM, MineManager *mineManager) : _displayWidth(w),
                                                                          _displayHeight(h),
                                                                          _fps(fps)

{
    _timer = timer;
    userSpaceship = userspaceship;
    enemyShip = enemyM;
    mineMan = mineManager;

    _gameOverTimer = new Timer(fps);
    _gameOverTimer->create();

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

    std::cout << "vai fazer o font\n";
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    _font = al_load_font("DavidCLM-BoldItalic.ttf", 64, 0);

    al_destroy_path(path);
    loadBackgroundSprite();
    std::cout << "window\n";
}

Window::~Window()
{
    // if (_timer != NULL)
    //     al_destroy_timer(_timer);
    if (_eventQueue != NULL)
        al_destroy_event_queue(_eventQueue);
    if (_display != NULL)
        al_destroy_display(_display);

    delete (_gameOverTimer);

    bg.reset();
    fg.reset();
}

void Window::run(Window *win)
{
    float prevTime = 0;
    while (!win->_finish)
    {
        // std::cout << "run window \n";
        win->gameLoop(prevTime);
        Thread::yield();
    }
    win->gameOver();
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
        _finish = true;
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

    if (userSpaceship->isDead())
    {
        _finish = true;
    }

    if(enemyShip->bossExists() && enemyShip->_bossManager->getBoss()->getDead()) {
        std::cout << "DA EXIT PELO WINDOW \n";
        enemyShip->_bossManagerThread->thread_exit(0);
    }
}

void Window::draw()
{
    drawBackground();
    drawShip(0);
    // std::cout << "draw window\n";
    enemyShip->drawEnemies();
    mineMan->drawMine();

    if (enemyShip->_bossManager != nullptr && enemyShip->_bossManager->getBoss())
    {
        std::cout << "draw boss\n";
        enemyShip->_bossManager->drawBoss(); // ver quando vou injetar bossManager na window..
    }
}

void Window::drawShip(int flags)
{
    std::shared_ptr<Sprite> sprite = userSpaceship->getSpaceShip();
    int row = userSpaceship->getRow();
    int col = userSpaceship->getCol();
    Point centre = userSpaceship->getCentre();
    sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
    userSpaceship->drawProjectiles();
    userSpaceship->drawLivesBar();
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

void Window::gameOver()
{
    if (!_gameOverTimer->isRunning())
    {
        // start timer and update scores
        _gameOverTimer->startTimer();
    }
    while (_gameOverTimer->getCount() < 100)
    {
        // game over message
        std::cout << "game over \n";
        drawTextCentered(al_map_rgb(255, 0, 0), "GAME OVER");
    }
}

void Window::drawTextCentered(const ALLEGRO_COLOR &color, const std::string &message)
{
    al_draw_text(_font, color, 400, 300, ALLEGRO_ALIGN_CENTRE, message.c_str());
}
