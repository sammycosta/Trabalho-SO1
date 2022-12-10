#include "Missile.h"
#include <cmath>
#include "Sprite.h"

Missile::Missile(Point c, ALLEGRO_COLOR color, Vector s) : Projectile(c, color, s)
{
    _angle = atan(speed.y / speed.x) - 4.71;
    centre = centre + speed * 0.1;
    _imageNum = 0;
    load_sprites();
}

Missile::~Missile()
{
}

// void Missile::update(double dt)
// {
// }

void Missile::draw()
{
    std::cout << "draw missile\n";
    _spritesVector[_imageNum]->draw_rotated(centre, _angle, 0);
    _imageNum = (_imageNum + 1) % 8;
}

void Missile::load_sprites()
{
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));
    _spritesVector.push_back(std::make_shared<Sprite>("m1.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m2.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m3.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m4.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m5.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m6.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m7.png"));
    _spritesVector.push_back(std::make_shared<Sprite>("m8.png"));
    al_destroy_path(path);
}
