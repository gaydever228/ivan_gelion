#include "Help.h"
//#include "Map_generator.h"


int generate_random_number(int x1, int x2)
{
		int x = 0;
		x = rand()%(x2 - x1);
		x += x1;
		return x;
}

bool wall_or_not(bool** MAP, int x, int y)
{
	if (x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1) {
		for (int i = y - 1; i <= y + 1; i++) {
			for (int j = x - 1; j <= x + 1; j++) {
				if (MAP[i][j] == true) {
					if (i != x || j != y) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool super_floor_or_not(bool** MAP, int x, int y)
{
	if (x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1) {
		if (MAP[y - 1][x] == false) {
			return true;
		}
		else {
			return false;
		}
	}
}

void map_draw(bool** MAP,  Map& M, int i, int j) {
			if (MAP[i][j] == true) {
				if (super_floor_or_not(MAP, j, i) == true) {
					M.sprite.setTextureRect(IntRect(256, 0, 128, 128));
				}
				else if (super_floor_or_not(MAP, j, i) == false) {
					M.sprite.setTextureRect(IntRect(0, 0, 128, 128));
				}
			}

			if (MAP[i][j] == false) {
				if (wall_or_not(MAP, j, i) == true) {
					M.sprite.setTextureRect(IntRect(128, 0, 128, 128));
				}
				else if (wall_or_not(MAP, j, i) == false) {
					M.sprite.setTextureRect(IntRect(384, 0, 128, 128));
				}
			}
			M.sprite.setPosition(j * 128, i * 128);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
}

void bullets_clear(list<Bullet*> bullets, list<Bullet*> ::iterator BuIt) {
	if (bullets.size() > 0) {
		for (BuIt = bullets.begin(); BuIt != bullets.end(); BuIt++) {
			(*BuIt)->ba_sprite.setPosition(0, 0);
		}
	}
}
