#include "UserSpaceship.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

UserSpaceship::UserSpaceship(ALLEGRO_TIMER *timer, int fps)
{
    al_init();
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
    _lives = 3;
    _totalLives = 3;
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
        // std::cout << "run userSpaceship \n";
        float crtTime;
        crtTime = al_current_time();
        ship->update(crtTime - prevTime);
        prevTime = crtTime;
        Thread::yield();
    }
}

void UserSpaceship::update(double dt)
{
    // Spaceship
    Point centreP = (*centre);
    centreP = centreP + speed * dt;
    centre = std::make_shared<Point>(centreP.x, centreP.y);
    selectShipAnimation();
    speed = Vector(0, 0);
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
    Point centreP = (*centre);
    if (centreP.x > 800 - 16)
        centreP.x = 800 - 16;
    else if (centreP.x < 16)
        centreP.x = 16;

    if (centreP.y > 600 - 16)
        centreP.y = 600 - 16;
    else if (centreP.y < 16)
        centreP.y = 16;
    centre = std::make_shared<Point>(centreP.x, centreP.y);
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
    centre = std::make_shared<Point>(215, 245);
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
        Point p = ((*centre) + Point(-20, 0));
        _proj.push_back(std::make_shared<Bullet>(p, color, projectileSpeed));
        _bulletTimer->srsTimer();
    }
}

void UserSpaceship::addMissile()
{
    if (_missileTimer->getCount() > 20)
    {
        Point p = ((*centre) + Point(-20, 0));
        _proj.push_back(std::make_shared<Missile>(p, color, projectileSpeed));
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
    //_lives -= damage;
    if (_lives <= 0)
    {
        _dead = true;
    }
}

void UserSpaceship::drawLivesBar()
{
    int displayWidth = 800;
    if (_lives > 0)
    {
        al_draw_rectangle(displayWidth - 70, 50, displayWidth - 50, 70,
                          al_map_rgb(0, 255, 0), 5);
    }
    if (_lives > 1)
    {
        al_draw_rectangle(displayWidth - 110, 50, displayWidth - 90, 70,
                          al_map_rgb(0, 255, 0), 5);
    }
    if (_lives > 2)
    {
        al_draw_rectangle(displayWidth - 150, 50, displayWidth - 130, 70,
                          al_map_rgb(0, 255, 0), 5);
    }

    Point centreP = (*centre);
    al_draw_line(centreP.x - _size * 2, centreP.y + _size * 2,
                 (centreP.x - _size * 2) + (_lives) * (_size * 1.5),
                 centreP.y + _size * 2,
                 al_map_rgb(255 * (1.0 - _lives / _totalLives),
                            200 * (_lives),
                            0),
                 5);
}
