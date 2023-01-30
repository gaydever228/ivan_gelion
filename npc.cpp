#include "npc.h"
#include "Help.h"
#include "Map_generator.h"
#include "View.h"
#include <cmath>
#include <cstdlib>
#include "Libraries.h"
NPC::NPC(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage):Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/hollow.png", x, y, 128, 128)
{
    AttackCoolDown = 0;
    health = hp;
    this->x = x;
    this->y = y;
    this->ViewDistant=ViewDistant;
    this->AttackDistant = AttackDistant;
    this->damage = damage;
    current_player_frame = 0;
    animation_speed = 0.08;
    xBlocks = int(x/128);
    yBlocks = int(y/128);
    sprite.setTextureRect(IntRect(6 * w, int(current_frame)*h, w, h));
    speed = 0.2;
}
NPC::NPC(float ViewDistant, int hp, float AttackDistant, int damage):Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/hollow.png", generate_random_number(tr.tree[tr.tree.size() - 1][0]->room.x1 * 128, tr.tree[tr.tree.size() - 1][0]->room.x2 * 128), generate_random_number(tr.tree[tr.tree.size() - 1][0]->room.y2 * 128, tr.tree[tr.tree.size() - 1][0]->room.y1 * 128), 128, 128)
{

    health = hp;
    this->AttackDistant = AttackDistant;
    this->damage = damage;

    this->ViewDistant=ViewDistant;
    current_player_frame = 0;
    animation_speed = 0.01;
    xBlocks = int(x/128);
    yBlocks = int(y/128);
    sprite.setTextureRect(IntRect(6 * w, int(current_frame)*h, w, h));
    speed = 0.2;
}
int * dolg = new int[2];
NPC::~NPC()
{
}
void NPC::animate(int dir)
{


    speed = 0.1;
    if (dir == 1) {

        direction = 1; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(2 * w, int(current_frame)*h, w, h));

    };

    if (dir == 0) {
        direction = 0; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(3 * w, int(current_frame)*h, w, h));

    };

    if (dir == 3) {

        direction = 3; current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(4*w, int(current_frame)*h, w, h));

    };

    if (dir == 2) {

        direction = 2;current_frame += animation_speed;
        if (current_frame >= 4) current_frame -= 4;
        sprite.setTextureRect(IntRect(7 * w, int(current_frame)*h, w, h));

    }
}
void NPC::update(float time, bool** Map) {
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
void NPC::stays() {
    sprite.setPosition(x, y);
    cout<<"pidor stays!"<<endl;
}

void NPC::move(float timok, bool ** Map, Player & player)
{




/*
        if(direction == 0 and Map[yBlocks][xBlocks+1] == 1) {

                animate(direction);



        }
        else if(direction == 0) {
            direction = Track;
            switch (direction)
            {
            case 2:
                if(Map[yBlocks+1][xBlocks] == 1) animate(direction);
                else {
                    direction = 3;

                    animate(direction);
                }

                break;
            case 3:
                if(Map[yBlocks-1][xBlocks] == 1) animate(direction);
                else {
                    direction = 2;

                    animate(direction);
                }
                break;
            }
        }
        if(direction == 1 and Map[yBlocks][xBlocks-1] == 1) {

                animate(direction);



        }
        else if(direction == 1) {
            direction = Track;
            switch (direction)
            {
            case 2:
                if(Map[yBlocks+1][xBlocks] == 1) animate(direction);
                else {
                    direction = 3;

                    animate(direction);
                }

                break;
            case 3:
                if(Map[yBlocks-1][xBlocks] == 1) animate(direction);
                else {
                    direction = 2;

                    animate(direction);
                }
                break;
            }
        }
        if(direction == 2 and Map[yBlocks+1][xBlocks] == 1) {


                animate(direction);




        }
        else if(direction == 2) {
            direction = Track;
            switch (direction)
            {
            case 0:
                if(Map[yBlocks][xBlocks+1] == 1) animate(direction);
                else {
                    direction = 1;

                    animate(direction);
                }

                break;
            case 1:
                if(Map[yBlocks][xBlocks-1] == 1) animate(direction);
                else {
                    direction = 0;

                    animate(direction);
                }
                break;
            }
        }
        if(direction == 3 and Map[yBlocks - 1][xBlocks] == 1) {


                animate(direction);


        }
        else if(direction == 3) {
            direction = Track;
            switch (direction)
            {
            case 0:
                if(Map[yBlocks][xBlocks+1] == 1) animate(direction);
                else {
                    direction = 1;

                    animate(direction);
                }

                break;
            case 1:
                if(Map[yBlocks][xBlocks-1] == 1) animate(direction);
                else {
                    direction = 0;

                    animate(direction);
                }
                break;
            }
        }
*/

    if ((player.x - x)*(player.x - x) + (player.y - y)*(player.y - y) <= AttackDistant*AttackDistant) {
        if (AttackCoolDown %140 == 0) {
            player.health -= damage;
            cout<<"PlayerAttacked to "<<player.health<<endl;
            AttackCoolDown = 0;
        }
        AttackCoolDown += 1;
    }
    else {
        animate(direction);
    }
    update(timok, Map);
}
//PlayerX and y in pixels
void NPC::Trace(float PlayerX, float PlayerY) {
    xBlocks = int(x/128);
    yBlocks = int(y/128);
    int rasst = int(fabs(PlayerX - x) + fabs(PlayerY - y));
    if(fabs(int(PlayerX/128) - xBlocks) > fabs(int(PlayerY/128) - yBlocks)) {
        if (PlayerX < x) {
            direction = 1;
        }
        else {
            direction= 0;
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
            Track= 0;
        }
    }



    /* int * Tr = new int[rasst];
    int a, b;
    for(int i = 0; i < fabs(PlayerX - xBlocks); i++) {
        if (PlayerX < xBlocks) {
            Tr[i] = 1;
        }
        else {
            Tr[i] = 0;
        }
    }
    for(int i = fabs(PlayerX - xBlocks); i < rasst; i++) {
        if (PlayerY < yBlocks) {
            Tr[i] = 3;
        }
        else {
            Tr[i] = 2;
        }
    }
    for(int i = 0; i < rasst/7; i++) {
        a = rand() % rasst;
        b = rand() % rasst;
        Tr[a] += Tr[b];
        Tr[b] = Tr[a] - Tr[b];
        Tr[a] -= Tr[b];
    }
    for(int i = 0; i < rasst; i++) {


        cout<<Tr[i]<<" - "<<i<<"th"<<endl;
    }
    this->Track =  Tr;
    free(Tr);*/
}
void NPC::interaction_with_map(bool** MAP)
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
//PlayerX and PlayerY is in blocks
bool NPC::IsPlayerInViewField(int PlayerX, int PlayerY, bool ** Map) {
    xBlocks = int(x/128);
    yBlocks = int(y/128);
    if (PlayerX == xBlocks) {
        for (int i = 0; i < fabs(PlayerY - yBlocks); i++) {
            if (Map[int(yBlocks+copysign(i,PlayerY - yBlocks))][int(xBlocks)] == 0) {
                return false;
            }
        }
        if ((PlayerY - yBlocks) <= ViewDistant) {
            return true;
        }
        else {
            cout<<"not in a view field because distant is"<<(PlayerY - yBlocks)<<" but View distant is"<<ViewDistant<<endl;
            return false;
        }
    }
    else {
        float derivative = (PlayerY*128 - y)/(PlayerX*128 - x);
        for (int i = 0; i < fabs(PlayerX*128 - x); i ++) {
            if(Map[int(round((y+copysign(i,int(PlayerX*128 - x))*derivative)/128))][int((x+copysign(i,int(PlayerX*128 - x)))/128)] == 0) {
                cout<<"not in a view field because of wall in"<<int((x+copysign(i,int(PlayerX*128 - x))/128))<<","<<int(round((y+copysign(i,int(PlayerX*128 - x))*derivative)/128))<<" but enemy in"<<xBlocks<<yBlocks<<endl;
                return false;
            }

        }
        if ((PlayerX - xBlocks)*(PlayerX - xBlocks) + (PlayerY - yBlocks)*(PlayerY - yBlocks) <= ViewDistant*ViewDistant) {
            return true;
        }
        else {
            cout<<"not in a view field because distant is"<<(PlayerX - xBlocks)*(PlayerX - xBlocks) + (PlayerY - yBlocks)*(PlayerY - yBlocks)<<" but View distant is"<<ViewDistant*ViewDistant<<endl;

            return false;
        }
    }

}


