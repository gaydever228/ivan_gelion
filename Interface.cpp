#include "Interface.h"

Interface::Interface(Player &P)
{
#ifdef _WIN32
    GameOverScreen = new Entity("GameOverScreen", 0, 0, 1920, 1080);
    font.loadFromFile("fonts/19363.ttf");
    life_bar = new Text("", font, 20);
    life_bar->setFillColor(sf::Color::Color(253, 255, 109));
    life_bar->setOutlineColor(sf::Color::Black);
    life_bar->setScale(2.f, 2.f);
    //life_bar->setStyle(sf::Text::Bold);

    InterfacePannel = new Entity("interface.png", 0, 0, 512, 200);
    Weapon = new Entity("weapons.png", 0, 0, 48, 72);
#else
    GameOverScreen = new Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/GameOverScreen.png", 0, 0, 1920, 1080);
    font.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/fonts/19363.ttf");
    life_bar = new Text("", font, 20);
    //life_bar->setFillColor(sf::Color::Color(253, 255, 109));
    life_bar->setOutlineColor(sf::Color::Black);
    life_bar->setScale(2.f, 2.f);
    //life_bar->setStyle(sf::Text::Bold);

    InterfacePannel = new Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/interface.png", 0, 0, 512, 200);
    Weapon = new Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/weapons.png", 0, 0, 48, 72);
#endif // _WIN32

    Weapon->sprite.setTextureRect(IntRect(0, 0, 48, 72));
    //Weapon->sprite.setScale(5.f, 5.f);
}

Interface::~Interface()
{
	delete(InterfacePannel, Weapon);
}

void Interface::render(Player &P, RenderWindow &window)
{
	ostringstream player_health;
	player_health << P.health;
	life_bar->setString(player_health.str());
	if (P.health > 99) {
		life_bar->setPosition(P.x - 575, P.y + 525);
	}
	if (P.health > 9 && P.health < 100) {
		life_bar->setPosition(P.x - 565, P.y + 525);
	}
	if (P.health < 10) {
		life_bar->setPosition(P.x - 555, P.y + 525);
	}

	InterfacePannel->sprite.setPosition(P.x-900, P.y+395);
	Weapon->sprite.setPosition(P.x - 755, P.y + 490);

	window.draw(InterfacePannel->sprite);
	window.draw(Weapon->sprite);
	window.draw(*life_bar);
}


