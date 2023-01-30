#include "Menu.h"

void menu(RenderWindow& window)
{
	Texture menuTexture1, menuTexture2, menuBackground;
#ifdef _WIN32
    menuTexture1.loadFromFile("Images/NewGame.png");
    menuTexture2.loadFromFile("Images/Exit.png");
    menuBackground.loadFromFile("Images/Background1.jpg");

#else
    menuTexture1.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/NewGame.png");
    menuTexture2.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Exit.png");
    menuBackground.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Background1.jpg");

#endif // _WIN32

	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	menu1.setTextureRect(IntRect(0, 0, 375, 60));
	menu2.setTextureRect(IntRect(0, 0, 175, 60));
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(200, 400);
	menu2.setPosition(200, 600);
	menuBg.setPosition(0, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setTextureRect(IntRect(0, 0, 375, 60));
		menu2.setTextureRect(IntRect(0, 0, 175, 60));
		menu1.setColor(Color::White); menu2.setColor(Color::White);
		menuNum = 0;
		window.clear();

		if (IntRect(200, 400, 375, 60).contains(Mouse::getPosition(window))) { /*menu1.setColor(Color::Blue)*/menu1.setTextureRect(IntRect(0, 60, 375, 60));; menuNum = 1; }
		if (IntRect(200, 600, 175, 60).contains(Mouse::getPosition(window))) {/*menu2.setColor(Color::Blue)*/menu2.setTextureRect(IntRect(0, 60, 175, 60));; menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) {
				window.close();
				isMenu = false;
			}
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
	////////////////////////////////////////////////////
}
