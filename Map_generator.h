#pragma once
#include "Libraries.h"

extern const int MIN_LEAF_WIDTH, MIN_LEAF_HEIGHT, LEVEL_NUMBER, MAX_LEAF_NUMBER, ROOM_WIDTH, ROOM_HEIGHT, MAP_WIDTH, MAP_HEIGHT;
extern int leaf_number;
//bool** MAP = new bool* [MAP_HEIGHT];

struct rectangle {
	int x1;
	int y1;
	int x2;
	int y2;
	int width = x2 - x1 + 1;
	int height = y1 - y2 + 1;
};

class Leaf
{

public:

	rectangle r;	//координаты листа
	rectangle room;	//координаты комнаты внутри листа
	rectangle hall;	//координаты коридора соединяющего потомков листа
	bool rooM;	//наличие команты
	int width, height;//ширина и высота листа

	Leaf* Left_child;	//левый ребенок
	Leaf* Right_child;	//правый ребенок


	Leaf(int X1, int Y1, int X2, int Y2);	//создает лист

	~Leaf();

	void print_leaf();//печатает лист

	bool split();	//разрезает лист

	bool create_room();	//создает комнату
};

class Tree {

public:

	int n;

	vector<vector<Leaf*>> tree;

	vector<rectangle> halls;

	Tree();

	~Tree();

	bool generate_random_section(int x1, int x2, const int l, int& x);

	bool create_hall(rectangle& r1, rectangle& r2); //создает коридор между двумя комнатами

	bool generate_tree(); // создает дерево комнат

	void print_tree();	// печатает дерево

};

extern Tree tr;


void add_leaf(bool** M, Leaf& l);

void add_room(bool** M, Leaf& l);  

void add_hall(bool** M, rectangle& hall);

void print_map(bool** M);

void create_map(vector<vector<Leaf*>>& tree, vector<rectangle> Halls, bool** Map);

bool GENERATE_MAP(bool** Map);