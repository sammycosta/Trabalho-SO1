#include "UserSpaceship.h"

std::shared_ptr<Sprite> UserSpaceship::spaceShip;
Point UserSpaceship::centre;
Vector UserSpaceship::speed;
int UserSpaceship::row; /**<row of animation to be played */
int UserSpaceship::col; /**< column of animation to be played */
ALLEGRO_EVENT_QUEUE UserSpaceship::*_timerQueue;

UserSpaceship::UserSpaceship(ALLEGRO_EVENT_QUEUE *timerQueue)
{
    // Create Ship
    centre = Point(215, 245);
    color = al_map_rgb(0, 200, 0);
    loadSprite();
    _timerQueue = timerQueue;
}

UserSpaceship::~UserSpaceship()
{
    spaceShip.reset();
}

void UserSpaceship::run()
{
    float prevTime = 0;
    while (true)
    {
        ALLEGRO_EVENT event;
        float crtTime;

        // get event
        al_wait_for_event(_timerQueue, &event);
        // timer
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            crtTime = al_current_time();
            update(crtTime - prevTime);
            prevTime = crtTime;
        }
    }
}

void UserSpaceship::update(double dt)
{
    // Spaceship
    centre = centre + speed * dt;
    selectShipAnimation(); // must happen before we reset our speed
    speed = Vector(0, 0);  // reset our speed
    checkBoundary();
}

void UserSpaceship::increaseVerticalSpeed()
{
    speed.y += 250;
}

void UserSpaceship::increaseHorizontalSpeed()
{
    speed.x += 250;
}

void UserSpaceship::decreaseVerticalSpeed()
{
    speed.y -= 250;
}

void UserSpaceship::decreaseHorizontalSpeed()
{
    speed.x -= 250;
}

void UserSpaceship::checkBoundary()
{
    // check x bound and adjust if out
    if (centre.x > 800 - 16)
        centre.x = 800 - 16;
    else if (centre.x < 16)
        centre.x = 16;
    // check y bound and adjust if out
    if (centre.y > 600 - 16)
        centre.y = 600 - 16;
    else if (centre.y < 16)
        centre.y = 16;
}

void UserSpaceship::selectShipAnimation()
{
    if (speed.x > 0)
    {
        col = 1;
        if (speed.y > 0)
            row = 2;
        else if (speed.y < 0)
            row = 0;
        else
            row = 1;
    }
    else
    {
        col = 0;
        if (speed.y > 0)
            row = 2;
        else if (speed.y < 0)
            row = 0;
        else
            row = 1;
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

inline int UserSpaceship::getRow()
{
    return row;
}
inline int UserSpaceship::getCol()
{
    return col;
}
inline Point UserSpaceship::getCentre()
{
    return centre;
}
inline std::shared_ptr<Sprite> UserSpaceship::getSpaceShip()
{
    return spaceShip;
}