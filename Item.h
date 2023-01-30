#ifndef ITEM_H
#define ITEM_H
#include<Entity.h>
#include "Player.h"

class Item : public Entity
{
public:
    Item(float x, float y, int type);
    Item(float x, float y);
    int HealAmount, DamageBoost, SpeedBoost;
    bool IsTaken;
    ~Item();
    int Type;
    void taken(Player& player);
    void animate(int dir) override;
};

#endif // ITEM_H
