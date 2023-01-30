#include "Pause.h"

void pause(RenderWindow& window, Timer& T, Player &P)
{
	Texture menuTexture1, menuTexture2, menuBackground;
#ifdef _WIN32
    menuTexture1.loadFromFile("Images/continue.png");
    menuTexture2.loadFromFile("Images/Exit.png");
    menuBackground.loadFromFile("Images/PauseBg.png");
#else
    menuTexture1.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/continue.png");
    menuTexture2.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/Exit.png");
    menuBackground.loadFromFile("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/PauseBg.png");
#endif // _WIN32


	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isPauseMenu = true;
	int menuNum = 0;

	//menuBg.setPosition(P.x-500, P.y-500);
	menu1.setPosition(P.x - 134, P.y-220);
	menu2.setPosition(P.x , P.y);

	//////////////////////////////лемч///////////////////
	while (isPauseMenu)
	{
		T.clock.restart();

		menuBg.setTextureRect(IntRect(0, 0, 1920, 1080));
		menu1.setTextureRect(IntRect(0, 0, 395, 60));
		menu2.setTextureRect(IntRect(0, 0, 555, 60));
		//menu1.setColor(Color::White); menu2.setColor(Color::White);
		menuNum = 0;

		if (IntRect(770, 260, 400, 60).contains(Mouse::getPosition(window))) { menu1.setTextureRect(IntRect(0, 60, 395, 60)); menuNum = 1; }
		if (IntRect(920, 480, 175, 60).contains(Mouse::getPosition(window))) { menu2.setTextureRect(IntRect(0, 60, 555, 60)); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isPauseMenu = false;
				break;
			}
			if (menuNum == 2) {
				isPauseMenu = false;
				window.close();
			}
		}
		//window.draw(menuBg);
		window.clear();
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
	////////////////////////////////////////////////////
}


void pause_game(Timer& T)
{
	bool pause = false;
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		pause = true;
	}
	while (pause == true) {
		if (Keyboard::isKeyPressed(Keyboard::O)) {
			pause = false;
		}
		T.clock.restart();
	}
}



