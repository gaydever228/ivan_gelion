#include "Npc.h"
#include "Help.h"
#include "Map_generator.h"
#include "View.h"
#include <cmath>
#include <cstdlib>
#include "Libraries.h"
#include "Sounds.h"
#include "Npc.h"
#include "Hollow.h"

#ifdef _WIN32
Hollow::Hollow(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage) :NPC( x,  y,  ViewDistant,  hp,  AttackDistant,  damage)
{
    AttackCoolDown = 0;
    health = hp;
    this->x = x;
    this->y = y;
    this->ViewDistant = ViewDistant;
    this->AttackDistant = AttackDistant;
    this->damage = damage;
    animation_speed = 0.1;
    current_frame = 0;
    speed = 0.1;
    xBlocks = int(x / 128);
    yBlocks = int(y / 128);
    sprite.setTextureRect(IntRect(7*w, int(current_frame) * h, w, h));
    is_life = 1;
    stan = 0;
}
#else
Hollow::Hollow(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage) :NPC( x,  y,  ViewDistant,  hp,  AttackDistant,  damage)
{

    AttackCoolDown = 0;
    health = hp;
    this->x = x;
    this->y = y;
    this->ViewDistant = ViewDistant;
    this->AttackDistant = AttackDistant;
    this->damage = damage;
    animation_speed = 0.1;
    current_frame = 0;
    HurtFrame = 0;
    speed = 0.05;
    xBlocks = int(x / 128);
    yBlocks = int(y / 128);
    sprite.setTextureRect(IntRect(7*w, int(current_frame) * h, w, h));
    is_life = 1;
    stan = 0;

}
#endif // _WIN32



Hollow::~Hollow()
{
}
void Hollow::animate(int dir)
{


    if (dir == 1) {

        direction = 1; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(2 * w, int(current_frame) * h, w, h));

    };

    if (dir == 0) {
        direction = 0; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(3 * w, int(current_frame) * h, w, h));

    };

    if (dir == 3) {

        direction = 3; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(4 * w, int(current_frame) * h, w, h));

    };

    if (dir == 2) {

        direction = 2; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(7 * w, int(current_frame) * h, w, h));

    }
}

void Hollow::HurtAnimate(int dir)
{


    if (dir == 1) {

        direction = 1; current_frame += 2*animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(6 * w, int(current_frame) * h, w, h));

    };

    if (dir == 0) {
        direction = 0; current_frame += 2*animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(0, int(current_frame) * h, w, h));

    };

    if (dir == 3) {

        direction = 3; current_frame += 2*animation_speed;
        if (current_frame >= 4) HurtFrame -= 4;
        sprite.setTextureRect(IntRect(5 * w, int(current_frame) * h, w, h));

    };

    if (dir == 2) {

        direction = 2; current_frame += 2*animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect( w, int(current_frame) * h, w, h));

    }
}
void Hollow::move(float timok, bool** Map, Player& player, Sounds& S)
{
    if(IsPlayerInViewField(int(player.x/128), int(player.y/128), Map)) {
        cout<<"stan ="<<stan<<endl;
        if(stan > 0){
            if(stan == 20) {
                S.damaged(x , y, (player.x-x)*(player.x-x)+(player.y-y)*(player.y-y));
            }
            HurtAnimate(direction);
            stan -= 1;

        }

        else {
            if ((player.x - x) * (player.x - x) + (player.y - y) * (player.y - y) <= AttackDistant * AttackDistant) {
                if (AttackCoolDown % 140 == 0) {
                    player.health -= damage;
                    cout << "PlayerAttacked to " << player.health << endl;
                    AttackCoolDown = 0;
                }
                AttackCoolDown += 1;
            }
            else {
            speed = 0.04;

            animate(direction);
            }

        }

}
    update(timok, Map);
    if (health <= 0) {
        is_life = 0;
    }
}
void Hollow::update(float time, bool** Map) {
    switch (direction)
    {
    case 0: dx = speed; dy = 0; break;
    case 1: dx = -speed; dy = 0; break;
    case 2: dx = 0; dy = speed; break;
    case 3: dx = 0; dy = -speed; break;
    }

    x += dx * time;
    y += dy * time;

    speed = 0;
    sprite.setPosition(x, y);
    interaction_with_map(Map);
}
void Hollow::stays() {
    sprite.setPosition(x, y);
    cout << "kkk stays!" << endl;
}
void Hollow::Trace(float PlayerX, float PlayerY) {
    xBlocks = int(x / 128);
    yBlocks = int(y / 128);
    int rasst = int(fabs(PlayerX - x) + fabs(PlayerY - y));
    if (fabs(int(PlayerX / 64 - x/64)) > fabs(int(PlayerY /64 - y/64))) {
        if (PlayerX < x) {
            direction = 1;
        }
        else {
            direction = 0;
        }
        if (PlayerY < y) {
            Track = 3;
        }
        else {
            Track = 2;
        }
    }
    else {
        if (PlayerY < y) {
            direction = 3;
        }
        else {
            direction = 2;
        }
        if (PlayerX < x) {
            Track = 1;
        }
        else {
            Track = 0;
        }
    }
}
void Hollow::interaction_with_map(bool** MAP)
{
    for (int i = y / 128; i < (y + h) / 128; i++)
        for (int j = x / 128; j < (x + w) / 128; j++)
        {
            if (MAP[i][j] == false)
            {
                if (dy > 0)
                {
                    y = i * 128 - h;
                }
                if (dy < 0)
                {
                    y = i * 128 + 128;
                }
                if (dx > 0)
                {
                    x = j * 128 - w;
                }
                if (dx < 0)
                {
                    x = j * 128 + 128;
                }
            }
        }
}

bool Hollow::IsPlayerInViewField(int PlayerX, int PlayerY, bool** Map) {
    xBlocks = int(x / 128);
    yBlocks = int(y / 128);
    if (PlayerX == xBlocks) {
        for (int i = 0; i < fabs(PlayerY - yBlocks); i++) {
            if (Map[int(yBlocks + copysign(i, PlayerY - yBlocks))][int(xBlocks)] == 0) {
                return false;
            }
        }
        if ((PlayerY - yBlocks) <= ViewDistant) {
            return true;
        }
        else {
           // cout << "not in a view field because distant is" << (PlayerY - yBlocks) << " but View distant is" << ViewDistant << endl;
            return false;
        }
    }
    else {
        float derivative = (PlayerY * 128 - y) / (PlayerX * 128 - x);
        for (int i = 0; i < fabs(PlayerX * 128 - x); i++) {
            if (Map[int(round((y + copysign(i, int(PlayerX * 128 - x)) * derivative) / 128))][int((x + copysign(i, int(PlayerX * 128 - x))) / 128)] == 0) {
               // cout << "not in a view field because of wall in" << int((x + copysign(i, int(PlayerX * 128 - x))) / 128) << "," << int(round((y + copysign(i, int(PlayerX * 128 - x)) * derivative) / 128)) << " but enemy in" << xBlocks << yBlocks << endl;
                return false;
            }

        }
        if ((PlayerX - xBlocks) * (PlayerX - xBlocks) + (PlayerY - yBlocks) * (PlayerY - yBlocks) <= ViewDistant * ViewDistant) {
            return true;
        }
        else {
            //cout << "not in a view field because distant is" << (PlayerX - xBlocks) * (PlayerX - xBlocks) + (PlayerY - yBlocks) * (PlayerY - yBlocks) << " but View distant is" << ViewDistant * ViewDistant << endl;

            return false;
        }
    }
}
