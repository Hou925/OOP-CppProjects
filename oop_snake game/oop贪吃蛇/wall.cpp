#include "objects.h"
#include"game.h"
#include<iostream>
#include<fstream>

using namespace std;

Wall::Wall(Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	for (int i = 0; i < 40; i++)
		G.Create_sth(i, 0, 1);
	for (int i = 0; i < 40; i++)
		G.Create_sth(39, i, 1);
	for (int i = 39; i >= 0; i--)
		G.Create_sth(i, 39, 1);
	for (int i = 39; i >= 0; i--)
		G.Create_sth(0, i, 1);
}

Wall::Wall(istream& fin, Game& G) {
	for (int i = 0; i < 40; i++)
		G.Create_sth(i, 0, 1);
	for (int i = 0; i < 40; i++)
		G.Create_sth(39, i, 1);
	for (int i = 39; i >= 0; i--)
		G.Create_sth(i, 39, 1);
	for (int i = 39; i >= 0; i--)
		G.Create_sth(0, i, 1);
	head = NULL, tail = NULL;
	destructed = 0;
	int x, y;
	while (1) {
		fin >> x;
		if (x == -1) break;
		fin >> y;
		create(x, y, G);
	}
}

void Wall::create(int x, int y, Game& G) {
	node* p = new node;
	p->x = x;
	p->y = y;
	if (head == NULL)
		head = p, tail = p;
	else {
		tail->next = p;
		p->next = NULL;
		tail = p;
	}
	G.Create_sth(x, y, 1);
}


Wall::~Wall() {
	if (!destructed) {
		ofstream fl("./file//last_game.txt", ios::app);
		if (!fl.is_open()) {
			cout << "fail" << endl;
			exit(1);
		}
		node* p = head, * q;
		while (p != NULL) {
			fl << p->x << " " << p->y << " ";
			q = p;
			p = p->next;
			delete q;
		}
		fl << "-1" << endl;
		fl.close();
	}
	destructed = 1;
}
