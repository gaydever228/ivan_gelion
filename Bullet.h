#pragma once
#include "Player.h"
#include "Entity.h"
#include "Npc.h"
#include "Sounds.h"
class Bullet : public Entity
{
public:

	Image ba_image;
	Texture ba_texture;
	Sprite ba_sprite;
	bool DoesEnemyGetDamage;
	float ba_animation_speed, ba_current_frame;
	float x_shoot, y_shoot;

	Bullet(Player& P);
	Bullet(NPC* N);
	void update(float time, bool** Map);

	void animate(int dir);

	void EnemyStrike(list<NPC*> enemies);
	void PlayerStrike(Player& P);

	int damage;

	void shoot_animate(Player& P);

	void interaction_with_map(bool** MAP);
};