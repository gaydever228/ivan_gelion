#pragma once
#include "Libraries.h"
#include "Entity.h"
#include "Player.h"

class Interface
{
public:

	Entity *InterfacePannel;
	Entity *Weapon;
	Entity *GameOverScreen;

	Font font;
	Text *life_bar;  

	Interface(Player &P);
	~Interface();

	void render(Player &P, RenderWindow& window);
};