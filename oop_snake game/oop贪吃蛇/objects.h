#pragma once
#include<iostream>
#include<fstream>
#include"game.h"
using namespace std;

class Snake;
class Wall;
class Food;

struct node {
	int x, y;
	node* next;
};

class Snake {
private:
	node* head, * tail;
	int dir;  //0×ó£¬1ÓÒ£¬2ÉÏ£¬3ÏÂ
	int last_x;
	int last_y;
	bool destructed;
public:
	Snake(Game&);
	Snake(istream&, Game&);
	void create(int, int, Game&);
	node* snake_head();
	void move(int, Game&);
	void recover(Game&);
	bool reset(Game&, Food&, Wall&, int);
	int get_dir();
	~Snake();
};

class Wall {
private:
	node* head, * tail;
	bool destructed;

public:
	Wall(Game&);
	Wall(istream&, Game&);
	void create(int, int, Game&);
	~Wall();
};

class Food {
private:
	node* head, * tail;
	bool destructed;

public:
	Food(Game&);
	Food(istream&, Game&);
	void create(int, int, Game&);
	void refresh(int, int, Game&);
	void new_food(Game&);
	~Food();
};