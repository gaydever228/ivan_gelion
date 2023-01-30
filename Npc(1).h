#pragma once
#include "Entity.h"
#include "Player.h"
#include "Sounds.h"
class NPC : public Entity
{
public:
    int directionCD;
    float ViewDistant, AttackDistant;
    int xBlocks, yBlocks;
    int damage;
    int AttackCoolDown;
    int HurtFrame;
    int EnType;
    bool bulletFlag;
    double vel;
    View view;

    NPC(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage);
    NPC(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage, bool gg);
    ~NPC();
    void stays();


    int stan;
    int  Track, sorryBrat;
    void animate(int dir) override;
    void interaction_with_map(bool** MAP) override;
    void update(float time, bool** Map) override;
    void move(float time, bool** Map, Player& player, Sounds& S);
    bool IsPlayerInViewField(int PlayerX, int PlayerY, bool** Map);
    void Trace(float PlayerX, float PlayerY);
    void HurtAnimate(int dir);
    // friend class Player;
};