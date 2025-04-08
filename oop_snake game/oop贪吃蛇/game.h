#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Game;

class Game {
private:
	char name[11];
	int mode;
	int map[40][40]; //0���հ� 1��ǽ 2��ʳ�� 3����
	int length;
	int lives;
	int score;
	string his_max_name;
	int his_max;
	int gameover;
public:
	friend class Wall;
	friend class Food;
	friend class Snake;

	Game(int);
	Game(istream&);
	int get_map(int, int);
	void Create_sth(int, int, int);
	int get_blank();
	int get_hp();
	void cal_length(int sign = 0);
	void Score_value();
	void HP_value();
	void length_value();
	int get_mode();
	void print_record();
	~Game();
};
