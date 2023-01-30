#pragma once
#include "Entity.h"


class Player : public Entity
{
public:

	View view;
	bool is_shoot;

	Player();
	~Player();
	int Damage;
	void animate(char dir);
	void update(float time, bool** Map);
	void interaction_with_map(bool** MAP);
	void control();
	float vel;
};