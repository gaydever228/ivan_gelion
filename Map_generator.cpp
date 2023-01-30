#include "Map_generator.h"

const int MIN_LEAF_WIDTH = 2; const int MIN_LEAF_HEIGHT = 2; const int LEVEL_NUMBER = 5;  const int MAX_LEAF_NUMBER = pow(2, LEVEL_NUMBER) - 1; int leaf_number = 0;

const int ROOM_WIDTH = 2; const int ROOM_HEIGHT = 2;

const int MAP_WIDTH = 100; const int MAP_HEIGHT = 100;

Tree tr;


Leaf::Leaf(int X1, int Y1, int X2, int Y2) {	//создает лист
	r.x1 = X1; room.x1 = 0;
	r.y1 = Y1; room.y1 = 0;
	r.x2 = X2; room.x2 = 0;
	r.y2 = Y2; room.y2 = 0;
	hall.x1 = 0;
	hall.y1 = 0;
	hall.x2 = 0;
	hall.y2 = 0;
	width = r.x2 - r.x1 + 1;
	height = r.y1 - r.y2 + 1;
	leaf_number += 1;
	rooM = false;
	Left_child = nullptr;
	Right_child = nullptr;
}

Leaf::~Leaf()
{
}

void Leaf::print_leaf()
{
	cout << endl << this << endl;

	cout << "hall x1 = " << hall.x1 << endl;
	cout << "hall y1 = " << hall.y1 << endl;
	cout << "hall x2 = " << hall.x2 << endl;
	cout << "hall y2 = " << hall.y2 << endl;
	cout << endl;
	cout << "room x1 = " << room.x1 << endl;
	cout << "room y1 = " << room.y1 << endl;
	cout << "room x2 = " << room.x2 << endl;
	cout << "room y2 = " << room.y2 << endl;
	cout << endl;
	cout << "x1 = " << r.x1 << endl;
	cout << "y1 = " << r.y1 << endl;
	cout << "x2 = " << r.x2 << endl;
	cout << "y2 = " << r.y2 << endl;
	cout << "Left_child = " << Left_child << endl;
	cout << "Right_child = " << Right_child << endl;
}

bool Leaf::split()
{
	if (Right_child != nullptr || Left_child != nullptr) {	// а вдруг мы его уже разрезали...
		return false;
	}

	if (leaf_number > MAX_LEAF_NUMBER)	//	проверка на количество листьев
	{
		return false;
	}

	if (height < MIN_LEAF_HEIGHT || width < MIN_LEAF_WIDTH) {	// проверка на минимальный размер
		return false;
	}

	char direction;

	if (width >= 2 * height) {		// выбор направления разрезания	
		direction = 'v';
	}
	else {
		direction = 'h';
	}


	int x_split = rand() % (width / 3) + width / 3 + r.x1;
	int y_split = rand() % (height / 3) + height / 3 + r.y2;

	if (direction == 'v')
	{
		Left_child = new Leaf(r.x1, r.y1, x_split, r.y2);
		Right_child = new Leaf(x_split, r.y1, r.x2, r.y2);
	}
	if (direction == 'h')
	{
		Left_child = new Leaf(r.x1, y_split, r.x2, r.y2);
		Right_child = new Leaf(r.x1, r.y1, r.x2, y_split);
	}

	return true; // разрезание выполнено!
}

bool Leaf::create_room()
{

	if (Right_child == nullptr && Left_child == nullptr) {

		if (width >= MIN_LEAF_WIDTH && height >= MIN_LEAF_HEIGHT) {

			int room_width = 0; int room_height = 0; int stop = 0;

			while (room_width < ROOM_WIDTH || room_height < ROOM_HEIGHT) {
				stop++;
				room.x1 = r.x1 + rand() % (width / 3) + 2;
				room.y1 = r.y1 - rand() % (height / 3) - 2;
				room.x2 = r.x2 - rand() % (width / 3) - 2;
				room.y2 = r.y2 + rand() % (height / 3) + 2;
				room_width = room.x2 - room.x1 + 1;
				room_height = room.y1 - room.y2 + 1;
				if (stop == 1000) {
					return false;
				}
			}

			rooM = true;
		}

		return true;
	}
}

Leaf root(0, MAP_HEIGHT - 1, MAP_WIDTH - 1, 0);


Tree::Tree()
{
	n = 1;
	tree.resize(n);
	tree[0].push_back(&root);
}

Tree::~Tree()
{
}

bool Tree::generate_random_section(int x1, int x2, const int l, int& x)
{
	if (x2 - x1 + 1 < l) {
		return false;
	}
	else {
		x = rand() % (x2 - x1 + 1 - l);
		x += x1;
		return true;
	}
}

bool Tree::create_hall(rectangle& r1, rectangle& r2)
{
	rectangle result;
	rectangle extra_result;

	//////////////////////////////////////////

	if (r1.x2 < r2.x1) {	//r1 ЛЕВЕЕ r2

		if (r1.y2 <= r2.y2 && r1.y1 >= r2.y2) {		//r1 cъел r2
			generate_random_section(r1.x1, r1.x2, 0, result.x1);
			generate_random_section(r2.x1, r2.x2, 0, result.x2);
			generate_random_section(r2.y2, r2.y1, 2, result.y2);
			result.y1 = result.y2 + 1;
			halls.push_back(result);
			return true;
		}

		if (r1.y2 >= r2.y2) {		//r1 ниже r2
			generate_random_section(r1.x1, r1.x2, 0, result.x1);
			generate_random_section(r2.x1, r2.x2, 0, result.x2);
			generate_random_section(r1.y2, r1.y1, 2, result.y2);
			result.y1 = result.y2 + 1;
			halls.push_back(result);
			if (r1.y1 > r2.y1) {
				extra_result.x1 = result.x2 - 1;
				extra_result.x2 = result.x2;
				extra_result.y1 = result.y1;
				generate_random_section(r2.y2, r2.y1, 0, extra_result.y2);
				halls.push_back(extra_result);
			}
			return true;
		}
		if (r1.y1 <= r2.y1) {		//r1 выше r2
			generate_random_section(r1.x1, r1.x2, 0, result.x1);
			generate_random_section(r2.x1, r2.x2, 0, result.x2);
			generate_random_section(r1.y2, r1.y1, 2, result.y2);
			result.y1 = result.y2 + 1;
			halls.push_back(result);
			if (r1.y2 < r2.y2) {
				extra_result.x1 = result.x2 - 1;
				extra_result.x2 = result.x2;
				generate_random_section(r2.y2, r2.y1, 0, extra_result.y1);
				extra_result.y2 = result.y2;
				halls.push_back(extra_result);
			}
			return true;
		}

	}

	///////////////////////////////////////////////////////////////////////


	if (r1.x1 > r2.x2) {	//r1 ПРАВЕЕ r2

		if (r1.y2 <= r2.y2 && r1.y1 >= r2.y2) {		//r1 cъел r2
			generate_random_section(r2.x1, r2.x2, 0, result.x1);
			generate_random_section(r1.x1, r1.x2, 0, result.x2);
			generate_random_section(r2.y2, r2.y1, 2, result.y2);
			result.y1 = result.y2 + 1;
			halls.push_back(result);
			return true;
		}

		if (r1.y2 >= r2.y2) {		//r1 ниже r2
			generate_random_section(r2.x1, r2.x2, 0, result.x1);
			generate_random_section(r1.x1, r1.x2, 0, result.x2);
			generate_random_section(r1.y2, r1.y1, 2, result.y2);
			result.y1 = result.y2 + 1;
			halls.push_back(result);
			if (r1.y1 > r2.y1) {
				extra_result.x1 = result.x2 - 1;
				extra_result.x2 = result.x2;
				extra_result.y2 = result.y2;
				generate_random_section(r2.y2, r2.y1, 0, extra_result.y1);
				halls.push_back(extra_result);
			}
			return true;
		}
		if (r1.y1 <= r2.y1) {		//r1 выше r2
			generate_random_section(r2.x1, r2.x2, 0, result.x1);
			generate_random_section(r1.x1, r1.x2, 0, result.x2);
			generate_random_section(r1.y2, r1.y1, 2, result.y2);
			result.y1 = result.y2 + 1;
			halls.push_back(result);
			if (r1.y2 < r2.y2) {
				extra_result.x1 = result.x1;
				extra_result.x2 = result.x1 + 1;
				generate_random_section(r2.y2, r2.y1, 0, extra_result.y1);
				extra_result.y2 = result.y2;
				halls.push_back(extra_result);
			}
			return true;
		}

	}

	/////////////////////////////////////////////////////////////////////////////////

	if (r1.y2 > r2.y1) {	// r1 НИЖЕ r2

		if (r1.x1 <= r2.x1 && r1.x2 >= r2.x2) {		//r1 cъел r2
			generate_random_section(r1.y2, r1.y1, 0, result.y1);
			generate_random_section(r2.y2, r2.y1, 0, result.y2);
			generate_random_section(r2.x1, r2.x2, 2, result.x1);
			result.x2 = result.x1 + 1;
			halls.push_back(result);
			return true;
		}

		if (r1.x2 <= r2.x2) {	//r1 левее r2
			generate_random_section(r1.y2, r1.y1, 0, result.y1);
			generate_random_section(r2.y2, r2.y1, 0, result.y2);
			generate_random_section(r1.x1, r1.x2, 2, result.x1);
			result.x2 = result.x1 + 1;
			halls.push_back(result);
			if (r1.x1 < r2.x1) {
				extra_result.x1 = result.x1;
				generate_random_section(r2.x1, r2.x2, 0, extra_result.x2);
				extra_result.y1 = result.y2 + 1;
				extra_result.y2 = result.y2;
				halls.push_back(extra_result);
			}
			return true;
		}
		if (r1.x1 >= r2.x1) {	//r1 правее r2
			generate_random_section(r1.y2, r1.y1, 0, result.y1);
			generate_random_section(r2.y2, r2.y1, 0, result.y2);
			generate_random_section(r1.x1, r1.x2, 2, result.x1);
			result.x2 = result.x1 + 1;
			halls.push_back(result);
			if (r1.x2 > r2.x2) {
				extra_result.x1 = result.x1;
				generate_random_section(r1.x1, r1.x2, 0, extra_result.x2);
				extra_result.y1 = result.y1;
				extra_result.y2 = result.y1 - 1;
				halls.push_back(extra_result);
			}
			return true;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////

	if (r1.y1 < r2.y2) {	// r1 ВЫШЕ r2 ВРОДЕ ОК

		if (r1.x1 <= r2.x1 && r1.x2 >= r2.x2) {		//r1 cъел r2
			generate_random_section(r2.y2, r2.y1, 0, result.y1);
			generate_random_section(r1.y2, r1.y1, 0, result.y2);
			generate_random_section(r2.x1, r2.x2, 2, result.x1);
			result.x2 = result.x1 + 1;
			halls.push_back(result);
			return true;
		}

		if (r1.x2 <= r2.x2) {	//r1 левее r2
			generate_random_section(r1.x1, r1.x2, 2, result.x1);
			result.x2 = result.x1 + 1;
			generate_random_section(r2.y2, r2.y1, 0, result.y1);
			generate_random_section(r1.y2, r1.y1, 0, result.y2);
			halls.push_back(result);
			if (r1.x1 < r2.x1) {
				extra_result.x1 = result.x1;
				generate_random_section(r2.x1, r2.x2, 0, extra_result.x2);
				extra_result.y1 = result.y1;
				extra_result.y2 = result.y1 - 1;
				halls.push_back(extra_result);
			}
			return true;
		}

		if (r1.x1 >= r2.x1) {	//r1 правее r2
			generate_random_section(r1.x1, r1.x2, 2, result.x1);
			result.x2 = result.x1 + 1;
			generate_random_section(r2.y2, r2.y1, 0, result.y1);
			generate_random_section(r1.y2, r1.y1, 0, result.y2);
			halls.push_back(result);
			if (r1.x2 > r2.x2) {
				generate_random_section(r2.x1, r2.x2, 0, extra_result.x1);
				extra_result.x2 = result.x2;
				extra_result.y1 = result.y1;
				extra_result.y2 = result.y1 - 1;
				halls.push_back(extra_result);
			}
			return true;
		}
	}
	return false;
}

bool Tree::generate_tree()
{
	while (n < LEVEL_NUMBER) {
		n += 1;
		tree.resize(n);

		for (int i = 0; i < tree[n - 2].size(); i++) {			//создаются листья и записываются в вектор
			if (tree[n - 2][i]->split() == true) {
				tree[n - 1].push_back(tree[n - 2][i]->Left_child);
				tree[n - 1].push_back(tree[n - 2][i]->Right_child);
			}
		}
	}

	if (n == LEVEL_NUMBER) {

		for (int i = 0; i < tree[n - 1].size(); i++) {		// создаются комнаты у последних листьев
			if (tree[n - 1][i]->create_room() == false) {
				return false;
			};
		}

		for (int i = 1; i < tree[n - 1].size(); i++) {
			create_hall(tree[n - 1][i - 1]->room, tree[n - 1][i]->room);
		}
		return true;
	}
}

void Tree::print_tree()
{
	for (int i = 0; i < tree.size(); i++) {
		for (int j = 0; j < tree[i].size(); j++) {
			tree[i][j]->print_leaf();
			cout << endl;
		}
		cout << "====================================";
	}

	cout << endl << " Level " << n << " Leafs " << leaf_number;
}

void add_leaf(bool** M, Leaf& l)
{
	for (int i = l.r.x1; i <= l.r.x2; i++) {
		M[l.r.y1][i] = true;
	}
	for (int i = l.r.x1; i <= l.r.x2; i++) {
		M[l.r.y2][i] = true;
	}
	for (int i = l.r.y2; i <= l.r.y1; i++) {
		M[i][l.r.x1] = true;
	}
	for (int i = l.r.y2; i <= l.r.y1; i++) {
		M[i][l.r.x2] = true;
	}
}

void add_room(bool** M, Leaf& l)
{
	for (int i = l.room.y2; i <= l.room.y1; i++) {
		for (int j = l.room.x1; j <= l.room.x2; j++) {
			M[i][j] = true;
		}
	}
}

void add_hall(bool** M, rectangle& hall)
{
	for (int i = hall.y2; i <= hall.y1; i++) {
		for (int j = hall.x1; j <= hall.x2; j++) {
			M[i][j] = true;
		}
	}
}

void print_map(bool** M)
{
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			cout << M[i][j];
		}
		cout << endl;
	}
}

void create_map(vector<vector<Leaf*>>& tree, vector<rectangle> Halls, bool** Map)
{
	for (int i = 0; i < MAP_HEIGHT; i++) {
		Map[i] = new bool[MAP_WIDTH];
		for (int j = 0; j < MAP_WIDTH; j++) {
			Map[i][j] = false;
		}
	}

	for (int i = 0; i < tree.size(); i++) {
		for (int j = 0; j < tree[i].size(); j++) {
			//add_leaf(Map, *tree[i][j]);
			add_room(Map, *tree[i][j]);
		}
	}

	for (auto& i : Halls) {
		add_hall(Map, i);
	}

	//print_map(Map);
}

bool GENERATE_MAP(bool** Map)
{
	if (tr.generate_tree() == true) {
		create_map(tr.tree, tr.halls, Map);
		//print_map(Map);
		//tr.print_tree();
		return true;
	}
	else {
		cout << "Упс, что-то пошло не так..";
		return false;
	}
}
