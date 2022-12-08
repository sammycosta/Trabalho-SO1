#include "Window.h"

Window::Window(int w, int h, int fps) : _displayWidth(w), _displayHeight(h),
                                        _fps(fps)

{
}

Window::~Window()
{
    if (_display != NULL)
        al_destroy_display(_display);

    bg.reset();
}

void Window::run()
{
}

void Window::gameLoop()
{
}

void Window::draw()
{
    drawBackground();
    drawShip(0);
}

void Window::drawShip(int flags)
{
    std::shared_ptr<Sprite> sprite = this->userSpaceship->getSpaceShip();
    int row = this->userSpaceship->getRow();
    int col = this->userSpaceship->getCol();
    Point centre = this->userSpaceship->getCentre();
    sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
}

void Window::drawBackground()
{
    bg->draw_parallax_background(bgMid.x, 0);
}

void Window::loadBackgroundSprite()
{
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
    this->userSpaceship->update(dt);
    // background
    bgMid = bgMid + bgSpeed * dt;
    if (bgMid.x >= 800)
    {
        bgMid.x = 0;
    }
}