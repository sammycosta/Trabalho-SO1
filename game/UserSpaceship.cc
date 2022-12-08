#include "UserSpaceship.h"

UserSpaceship::UserSpaceship()
{
    // Create Ship
    this->centre = Point(215, 245);
    this->color = al_map_rgb(0, 200, 0);
    loadSprite();
}

UserSpaceship::~UserSpaceship()
{
    spaceShip.reset();
}

void UserSpaceship::run()
{
}

void UserSpaceship::update(double dt)
{
    // Spaceship
    this->centre = this->centre + this->speed * dt;
    selectShipAnimation();      // must happen before we reset our speed
    this->speed = Vector(0, 0); // reset our speed
    checkBoundary();
}

void UserSpaceship::increaseVerticalSpeed()
{
    this->speed.y += 250;
}

void UserSpaceship::increaseHorizontalSpeed()
{
    this->speed.x += 250;
}

void UserSpaceship::decreaseVerticalSpeed()
{
    this->speed.y -= 250;
}

void UserSpaceship::decreaseHorizontalSpeed()
{
    this->speed.x -= 250;
}

void UserSpaceship::checkBoundary()
{
    // check x bound and adjust if out
    if (this->centre.x > 800 - 16)
        this->centre.x = 800 - 16;
    else if (this->centre.x < 16)
        this->centre.x = 16;
    // check y bound and adjust if out
    if (this->centre.y > 600 - 16)
        this->centre.y = 600 - 16;
    else if (this->centre.y < 16)
        this->centre.y = 16;
}

void UserSpaceship::selectShipAnimation()
{
    if (this->speed.x > 0)
    {
        this->col = 1;
        if (this->speed.y > 0)
            this->row = 2;
        else if (this->speed.y < 0)
            this->row = 0;
        else
            this->row = 1;
    }
    else
    {
        this->col = 0;
        if (this->speed.y > 0)
            this->row = 2;
        else if (this->speed.y < 0)
            this->row = 0;
        else
            this->row = 1;
    }
}

void UserSpaceship::loadSprite()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));
    // sprites
    spaceShip = std::make_shared<Sprite>("Sprite2.png"); // espaçonave do usuário
    // delete path
    al_destroy_path(path);
}