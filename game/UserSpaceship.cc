#include "UserSpaceship.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

UserSpaceship::UserSpaceship(ALLEGRO_TIMER *timer, int fps)
{
    al_init();
    // initialize addons
    al_init_primitives_addon();
    al_init_image_addon();
    if ((_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }
    // Create Ship
    loadSprite();
    _timer = timer;
    projectileSpeed = Vector(500, 0);

    _bulletTimer = new Timer(fps);
    _bulletTimer->create();
    _bulletTimer->startTimer();

    _missileTimer = new Timer(fps);
    _missileTimer->create();
    _missileTimer->startTimer();

    _size = 16;
    _lives = 9;
    _totalLives = 9;
    _dead = false;
}

UserSpaceship::~UserSpaceship()
{
    spaceShip.reset();
    delete (_bulletTimer);
    delete (_missileTimer);
}

void UserSpaceship::run(UserSpaceship *ship)
{
    float prevTime = 0;
    while (true)
    {
        ALLEGRO_EVENT event;
        float crtTime;

        // get event
        // al_wait_for_event(ship->_eventQueue, &event);
        // timer
        // if (event.type == ALLEGRO_EVENT_TIMER)
        // {
        //     std::cout << "run userSpaceship \n";
        //     crtTime = al_current_time();
        //     ship->update(crtTime - prevTime);
        //     prevTime = crtTime;
        // }

        // std::cout << "run userSpaceship \n";
        crtTime = al_current_time();
        ship->update(crtTime - prevTime);
        prevTime = crtTime;
        Thread::yield();
    }
}

void UserSpaceship::update(double dt)
{
    // Spaceship
    centre = centre + speed * dt;
    selectShipAnimation(); // must happen before we reset our speed
    speed = Vector(0, 0);  // reset our speed
    checkBoundary();
    updateProjectiles(dt);
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
    centre = Point(215, 245);
    color = al_map_rgb(0, 200, 0);
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "/resources");
    al_change_directory(al_path_cstr(path, '/'));
    // sprites
    spaceShip = std::make_shared<Sprite>("Sprite2.png"); // espaçonave do usuário
    // delete path
    al_destroy_path(path);
}

void UserSpaceship::updateProjectiles(double dt)
{
    std::list<std::shared_ptr<Projectile>> newProj;
    if (_proj.empty() == false)
    {
        for (auto p = _proj.begin(); p != _proj.end(); ++p)
        {
            p->get()->update(dt);
            if (p->get()->isAlive())
            {
                newProj.push_back(*p);
            }
        }
        _proj.clear();
        _proj.assign(newProj.begin(), newProj.end());
    }
}

void UserSpaceship::addBullet()
{
    if (_bulletTimer->getCount() > 6)
    {
        _proj.push_back(std::make_shared<Bullet>(centre + Point(-20, 0), color, projectileSpeed));
        _bulletTimer->srsTimer();
    }
}

void UserSpaceship::addMissile()
{
    if (_missileTimer->getCount() > 20)
    {
        _proj.push_back(std::make_shared<Missile>(centre + Point(-20, 0), color, projectileSpeed));
        _missileTimer->srsTimer();
    }
}

void UserSpaceship::drawProjectiles()
{
    if (_proj.empty() == false)
    {
        for (auto p = _proj.begin(); p != _proj.end(); ++p)
        {
            if (p->get()->isAlive())
            {
                p->get()->draw();
            }
        }
    }
}

void UserSpaceship::hit(const int &damage)
{
    std::cout << _lives << " LEVOU HIIIIIIIIIIIIIIT\n";
    _lives -= damage;
    if (_lives <= 0)
    {
        _dead = true;
    }
}

void UserSpaceship::drawLivesBar()
{
    // ALLEGRO_COLOR barColor;

    // if (_lives > 4)
    // {
    //     barColor =
    // } else {

    // }

    al_draw_line(centre.x - _size * 2, centre.y + _size * 2,
                 (centre.x - _size * 2) + (_lives / _totalLives) * (_size * 4),
                 centre.y + _size * 2,
                 al_map_rgb(255 * (1.0 - _lives / _totalLives),
                            200 * (_lives / _totalLives),
                            0),
                 5);
}
