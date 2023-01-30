#include "Item.h"
#include "Player.h"
#ifdef _WIN32
Item::Item(float x, float y, int type) :Entity("Images/bible.png", x, y, 64, 64)
{
    Type = 0;
    this->x=x;
    this->y=y;
    current_frame = 0;
    HealAmount = 0;
    DamageBoost = 2;
    animation_speed = 0.05;
    IsTaken = 0;
}
Item::Item(float x, float y) :Entity("Images/heal.png", x, y, 64, 64)
{
    Type = 1;
    HealAmount = 50;
    this->x=x;
    animation_speed = 0.05;
    this->y=y;
    current_frame = 0;
    IsTaken = 0;
}
#else
Item::Item(float x, float y, int type) :Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/bible.png", x, y, 64, 64)
{
    Type = 0;
    this->x=x;
    this->y=y;
    current_frame = 0;
    HealAmount = 0;
    DamageBoost = 2;
    animation_speed = 0.05;
    IsTaken = 0;
}
Item::Item(float x, float y) :Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/heal.png", x, y, 64, 64)
{
    Type = 1;
    HealAmount = 50;
    this->x=x;
    animation_speed = 0.05;
    this->y=y;
    current_frame = 0;
    IsTaken = 0;
}
#endif // _WIN32

Item::~Item()
{
}
void Item::animate(int dir) {
    current_frame += animation_speed;
    if (current_frame >= 3) current_frame -= 3;
    sprite.setTextureRect(IntRect(0, int(current_frame) * h, w, h));
}

void Item::taken(Player& player) {
    if (Type == 1) {
        animate(1);
    }
    if(player.x + 40 > x and player.x - 30 < x and player.y + 100 > y and player.y - 60 < y) {
        if(Type == 1) {
            player.health += HealAmount;
        }
        else if (Type == 0) {
            player.Damage += DamageBoost;
        }
        cout<<"Taken!!"<<endl;
        IsTaken = 1;
    }

}
