#include "Player.h"
#include "Help.h"
#include "Map_generator.h"
#include "View.h"

#ifdef _WIN32
Player::Player() :Entity("GgWalks.png", generate_random_number(tr.tree[tr.tree.size() - 1][0]->room.x1 * 128, tr.tree[tr.tree.size() - 1][0]->room.x2 * 128), generate_random_number(tr.tree[tr.tree.size() - 1][0]->room.y2 * 128, tr.tree[tr.tree.size() - 1][0]->room.y1 * 128), 128, 128)
{
	//image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
	health = 100;
	current_frame = 0;
	animation_speed = 0.07;
	is_shoot = false;
	xBlocks = int(x / 128);
	yBlocks = int(y / 128);
	sprite.setTextureRect(IntRect(7 * w, int(current_frame) * h, w, h));
	vel = 0.2;
	get_player_coordinate_for_view(x, y, view);
	Damage = 7;
}
#else
Player::Player() :Entity("/home/sergey/Desktop/4sem/kt/currentBuild/fuckGame/Images/GgWalks.png", generate_random_number(tr.tree[tr.tree.size() - 1][0]->room.x1 * 128, tr.tree[tr.tree.size() - 1][0]->room.x2 * 128), generate_random_number(tr.tree[tr.tree.size() - 1][0]->room.y2 * 128, tr.tree[tr.tree.size() - 1][0]->room.y1 * 128), 128, 128)
{
	//image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
	health = 100;
	current_frame = 0;
	animation_speed = 0.06;
	is_shoot = false;
	xBlocks = int(x / 128);
	yBlocks = int(y / 128);
	sprite.setTextureRect(IntRect(7 * w, int(current_frame) * h, w, h));
	vel = 0.24;

	get_player_coordinate_for_view(x, y, view);
	Damage = 10;
}
#endif // _WIN32



Player::~Player()
{
}

void Player::animate(char dir)
{
	if (dir == 'A') { //если нажата клавиша стрелка влево или англ буква А
		speed = vel;
		direction = 1; current_frame += 2 * animation_speed;   //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
		if (current_frame > 4) current_frame -= 4; // если пришли к третьему кадру - откидываемся назад.
		sprite.setTextureRect(IntRect(2 * w, int(current_frame) * h, w, h)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
		get_player_coordinate_for_view(x, y, view);
	};

	if (dir == 'D') { //если нажата клавиша стрелка влево или англ буква D
		speed = vel;
		direction = 0; current_frame += 2 * animation_speed;   //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
		if (current_frame > 4) current_frame -= 4; // если пришли к третьему кадру - откидываемся назад.
		sprite.setTextureRect(IntRect(3 * w, int(current_frame) * h, w, h)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
		get_player_coordinate_for_view(x, y, view);
	};

	if (dir == 'W') { //если нажата клавиша стрелка влево или англ буква W
		speed = vel;
		direction = 3; current_frame += 2 * animation_speed; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
		if (current_frame > 4) current_frame -= 4; // если пришли к третьему кадру - откидываемся назад.
		sprite.setTextureRect(IntRect(4 * w, int(current_frame) * h, w, h)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
		get_player_coordinate_for_view(x, y, view);
	};

	if (dir == 'S') { //если нажата клавиша стрелка влево или англ буква S
		speed = vel;
		direction = 2; current_frame += 2 * animation_speed;  //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
		if (current_frame > 4) current_frame -= 4; // если пришли к третьему кадру - откидываемся назад.
		sprite.setTextureRect(IntRect(7 * w, int(current_frame) * h, w, h)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
		get_player_coordinate_for_view(x, y, view);
	}
}

void Player::interaction_with_map(bool** MAP)//ф-ция взаимодействия с картой
{
	for (int i = y / 128; i < (y + h) / 128; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = x / 128; j < (x + w) / 128; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (MAP[i][j] == false)//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
			{
				if (dy > 0)//если мы шли вниз,
				{
					y = i * 128 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
				}
				if (dy < 0)
				{
					y = i * 128 + h;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
				}
				if (dx > 0)
				{
					x = j * 128 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
				}
				if (dx < 0)
				{
					x = j * 128 + w;//аналогично идем влево
				}
			}
		}
}

void Player::control()
{
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		animate('A');
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		animate('D');
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		animate('S');
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		animate('W');
	}
}

void Player::update(float time, bool** Map) {
	switch (direction)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}
	x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	y += dy * time;//аналогично по игреку
	xBlocks = int(x / 128);
	yBlocks = int(y / 128);
	speed = 0;//зануляем скорость, чтобы персонаж остановился.
	sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	interaction_with_map(Map);
	change_view(view);
	if (health <= 0) {
		is_life = false;
	}
}