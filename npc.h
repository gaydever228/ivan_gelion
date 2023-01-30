#pragma once
#include "Entity.h"
#include "Player.h"

class NPC : public Entity
{
public:

    float current_player_frame;
    float animation_speed;
    float ViewDistant, AttackDistant;
    int xBlocks, yBlocks;
    int damage;
    int AttackCoolDown;

    View view;

    NPC(float x, float y, float ViewDistant, int hp, float AttackDistant, int damage);
    NPC(float dist, int hp, float AttackDistant, int damage);
    ~NPC();
    void stays();
    int  Track;
    void animate(int dir);
    void interaction_with_map(bool** MAP);
    void update(float time, bool **Map) override;
    void move(float time, bool ** Map, Player & player);
    bool IsPlayerInViewField(int PlayerX, int PlayerY, bool ** Map);
    void Trace(float PlayerX, float PlayerY);
   // friend class Player;
};




