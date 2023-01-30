#ifndef HOLLOW_H
#define HOLLOW_H
#include "Entity.h"
#include "Player.h"
#include "Sounds.h"
#include "Npc.h"
class Hollow : public NPC
{
public:



    Hollow(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage);

    ~Hollow();
    void stays() override;


    int stan;
    int  Track;
    void animate(int dir) override;
    void interaction_with_map(bool** MAP) override;
    void update(float time, bool** Map) override;
    void move(float time, bool** Map, Player& player, Sounds& S) override;
    bool IsPlayerInViewField(int PlayerX, int PlayerY, bool** Map) override;
    void Trace(float PlayerX, float PlayerY) override;
    void HurtAnimate(int dir) override;
};


#endif // HOLLOW_H
