#include "Boss.h"
#include "Vector.h"

Boss::Boss(Point c, ALLEGRO_COLOR _color, Vector s, std::shared_ptr<Point> playerCent) : Enemy(centre, color, s)
{
    centre = c;
    color = _color;
    speed = s;

    _totalLives = 50;
    dead = false;
    _row = 0;
    _col = 0;
    lives = 30;
    _fireSpeed = 100;
    _dAnimComplete = false;
    _nDeathAnim = 0;
    _projSpeed = Vector(-400, 0);
    _playerLocation = playerCent;
    _target = false;
    _fire = false;
    _spriteIndex = 0;

    _delayTimer = new Timer(60);
    _delayTimer->create();
    _delayTimer->startTimer();
}

Boss::~Boss()
{
    delete (_delayTimer);
    _playerLocation.reset();
}

void Boss::draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death)
{
    selectSprite();
    if (!dead)
    {
        ship->draw_boss(_row, _col, 200, 200, centre, 0);
    }
    else
    {
        // boss está morto; animação de morte
        if (_nDeathAnim < 5)
        {
            death->draw_death_anim(_nDeathAnim, centre, 0);
            _nDeathAnim++;
        }

        else
            _dAnimComplete = true;
    }
}

void Boss::selectSprite()
{
    if (lives >= _totalLives)
    {
        _spriteIndex = 0;
    }
    // sprite depois que sofreu dano
    if (lives <= _totalLives && _spriteIndex < 3)
    {
        _fireSpeed = rand() % 50 + 20;
        speed = speed * 1.1; // velocidade aumenta
        _size = 70;
        _spriteIndex++;
    }
    // sprite final de dano
    if (lives <= 20 && _spriteIndex < 8)
    {
        _fireSpeed = rand() % 30 + 20;
        speed = speed * 1.1; // velocidade aumenta
        _size = 60;
        _spriteIndex++;
    }

    _row = _spriteIndex / 3;
    _col = _spriteIndex % 3;
}

void Boss::hit()
{
    if (_target)
    {
        lives -= 1;
        if (lives < 1)
        {
            dead = true;
        }
    }
}

void Boss::update(double dt)
{

    centre = centre + speed * dt;

    if (centre.x < 650 && !_target)
    {
        _target = true;
        _size = 80;    // tamanho é 80
        speed.x = 0;   // sem movimento horizontal
        speed.y = 100; // movimentação vertical
        _target = true;
    }
    // mudança de direção do movimento
    if (centre.y > 450 && speed.y > 0)
    {
        speed.y = -1 * speed.y;
    }
    if (centre.y < 150 && speed.y < 0)
    {
        speed.y = -1 * speed.y;
    }
    // verifica se pode atirar
    if (_delayTimer->getCount() > _fireSpeed)
    {
        _fire = true;
        addProjectile();
        _delayTimer->srsTimer(); // stop, reset, start
    }
    updateProjectiles(dt);
}

void Boss::addProjectile()
{
    int n = rand() % 7 + 1;
    Vector aim(0, 0);
    switch (n)
    {
    case 1:
        for (int i = -100; i <= 100; i += 20)
            addBullet(centre + Point(0, i), _projSpeed);
        break;

    case 2:
        aim.Angle((*_playerLocation), centre, 0.9);
        for (int i = -70; i <= 70; i += 20)
            addBullet(centre + Point(50, 0), aim + Vector(-30, i));
        break;
    default:
        aim.Angle(*(_playerLocation), centre + Point(0, 50), 0.9);
        addMissile(centre + Point(0, 50), aim);
        aim.Angle(*(_playerLocation), centre + Point(0, -50), 0.9);
        addMissile(centre + Point(0, -50), aim);
        break;
    }
}

void Boss::addBullet(Point c, Vector speed)
{

    _proj.push_back(std::make_shared<Bullet>(c, color, speed));
    _delayTimer->srsTimer();
}

void Boss::addMissile(Point c, Vector speed)
{

    _proj.push_back(std::make_shared<Missile>(c + Point(-20, 0), al_map_rgb(204, 3, 3), speed));
    _delayTimer->srsTimer();
}
