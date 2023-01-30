#include "Bullet.h"
#include "Map_generator.h"


#ifdef _WIN32
Bullet::Bullet(Player& P) :Entity("Bullet.png", P.x, P.y, 12, 38) {
    ba_image.loadFromFile("Images/Shooting.png");
    ba_texture.loadFromImage(ba_image);
    ba_sprite.setTexture(ba_texture);
    ba_animation_speed = 0.00001;
    ba_current_frame = 0;
    x_shoot = P.x;
    y_shoot = P.y;
    damage = P.Damage;
    is_bullet = true;
    speed = 0.5;
    direction = P.direction;
    current_frame = 0;
    animation_speed = 0.1;
    DoesEnemyGetDamage = 1;
}
Bullet::Bullet(NPC* N) :Entity("BulletEnemy.png", (*N).x, (*N).y, 12, 38) {
    x_shoot = (*N).x;
    y_shoot = (*N).y;
    this->damage = (*N).damage;
    is_bullet = true;
    speed = 0.25;
    direction = (*N).Track;
    current_frame = 0;
    animation_speed = 0.1;
    DoesEnemyGetDamage = 0;
}
#else

Bullet::Bullet(Player& P) :Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Bullet.png", P.x, P.y, 12, 38) {
    ba_image.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Shooting.png");
    ba_texture.loadFromImage(ba_image);
    ba_sprite.setTexture(ba_texture);
    ba_animation_speed = 0.00001;
    ba_current_frame = 0;
    x_shoot = P.x;
    y_shoot = P.y;
    damage = P.Damage;
    is_bullet = true;
    speed = 0.5;
    direction = P.direction;
    current_frame = 0;
    animation_speed = 0.1;
    DoesEnemyGetDamage = 1;
}
Bullet::Bullet(NPC* N) :Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/BulletEnemy.png", (*N).x, (*N).y, 12, 38) {
    ba_image.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Shooting.png");
    ba_texture.loadFromImage(ba_image);
    ba_sprite.setTexture(ba_texture);
    ba_animation_speed = 0.00001;
    ba_current_frame = 0;
    x_shoot = (*N).x;
    y_shoot = (*N).y;
    this->damage = (*N).damage;
    is_bullet = true;
    speed = 0.25;
    direction = (*N).Track;
    current_frame = 0;
    animation_speed = 0.1;
    DoesEnemyGetDamage = 0;
}
#endif // _WIN32

void Bullet::shoot_animate(Player& P) {
    while (ba_current_frame < 3) {
        if (P.direction == 0) {
            ba_sprite.setTextureRect(IntRect(10, int(ba_current_frame) * 12, 10, 12));
            ba_sprite.setPosition(P.x + 86, P.y + 40);
        }
        if (P.direction == 1) {
            ba_sprite.setTextureRect(IntRect(0, int(ba_current_frame) * 12, 10, 12));
            ba_sprite.setPosition(P.x + 32, P.y + 40);
        }
        if (P.direction == 2) {
            ba_sprite.setTextureRect(IntRect(20, int(ba_current_frame) * 14, 6, 14));
            ba_sprite.setPosition(P.x + 61, P.y + 40);
        }
        ba_current_frame += ba_animation_speed;
    }
    if (P.direction == 0) {
        ba_sprite.setTextureRect(IntRect(10, 24, 10, 12));
        ba_sprite.setPosition(P.x + 86, P.y + 40);
    }
    if (P.direction == 1) {
        ba_sprite.setTextureRect(IntRect(0, 24, 10, 12));
        ba_sprite.setPosition(P.x + 32, P.y + 40);
    }
    if (P.direction == 2) {
        ba_sprite.setTextureRect(IntRect(20, 28, 6, 14));
        ba_sprite.setPosition(P.x + 61, P.y + 40);
    }
}

void Bullet::interaction_with_map(bool** MAP)
{
    for (int i = y / 128; i < (y + h) / 128; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
        for (int j = x / 128; j < (x + w) / 128; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
        {
            if (MAP[i][j] == false)//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
            {

                is_life = false;
            }
        }
}
void Bullet::EnemyStrike(list<NPC*> enemies) {
    list<NPC*>::iterator EnIt;
    for (EnIt = enemies.begin(); EnIt != enemies.end(); EnIt++) {
        if ((*EnIt)->x + 20 > x and (*EnIt)->x - 20 < x and (*EnIt)->y + 100 > y and (*EnIt)->y - 20 < y and DoesEnemyGetDamage == 1) {
            (*EnIt)->health -= damage;
            (*EnIt)->stan += 21;
            //cout<<"stanned";
            (*EnIt)->current_frame = 0;
            is_life = 0;
        }
    }
}
void Bullet::PlayerStrike(Player& P) {
    if (P.x + 25 > x and P.x - 25 < x and P.y + 85 > y and P.y - 50 < y and DoesEnemyGetDamage == 0) {
        P.health -= damage;
        is_life = 0;
    }
}
void Bullet::animate(int dir) {
    current_frame += animation_speed;
    if (current_frame > 2) current_frame -= 2;
    sprite.setTextureRect(IntRect(0, int(current_frame) * h / 2, w, h / 2));
}

void Bullet::update(float time, bool** Map)
{
    switch (direction)
    {
    case 0: dx = speed; dy = 0; break;
    case 1: dx = -speed; dy = 0; break;
    case 2: dx = 0; dy = speed; break;
    case 3: dx = 0; dy = -speed; break;
    }
    x += dx * time;//само движение пули по х
    y += dy * time;//по у

    sprite.setTextureRect(IntRect(0, h / 2, w, h / 2));
    if (direction == 0) {
        sprite.setPosition(x + 100, y + 40);
        sprite.setRotation(90);
    }
    if (direction == 1) {
        sprite.setPosition(x + 20, y + 50);
        sprite.setRotation(270);
    }
    if (direction == 2) {
        sprite.setPosition(x + 70, y + 50);
        sprite.setRotation(180);
    }
    if (direction == 3) {
        sprite.setPosition(x + 58, y);
        sprite.setRotation(0);
    }
    animate(direction);
    interaction_with_map(Map);
}