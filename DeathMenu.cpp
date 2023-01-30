#include "DeathMenu.h"

void death_menu(RenderWindow& window, Player &P)
{
	Texture menuTexture1, menuBackground;
#ifdef _WIN32
    menuTexture1.loadFromFile("images/Exit.png");
	menuBackground.loadFromFile("images/GameOverScreen.png");

#else
    menuTexture1.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Exit.png");
	menuBackground.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/GameOverScreen.png");
#endif // _WIN32

	Sprite menu1(menuTexture1),menuBg(menuBackground);
	menu1.setTextureRect(IntRect(0, 0, 175, 60));
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(P.x, P.y+200);
	menuBg.setPosition(P.x-950, P.y-500);

	//////////////////////////////����///////////////////
	while (isMenu)
	{
		menu1.setTextureRect(IntRect(0, 0, 175, 60));
		menuNum = 0;
		window.clear();

		if (IntRect(910, 685, 175, 60).contains(Mouse::getPosition(window))) {menu1.setTextureRect(IntRect(0, 60, 175, 60));; menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				window.close();
				isMenu = false;
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.display();
	}
	////////////////////////////////////////////////////
}
