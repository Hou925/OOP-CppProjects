#include<iostream>
#include<fstream>
#include"game.h"
#include "objects.h"

using namespace std;

//���������ʳ��
void Food::new_food(Game& G) {
	int num = rand() % 5 + 1;
	for (int i = 0; i < num; i++) {
		int x = rand() % 38 + 1;
		int y = rand() % 38 + 1;
		while (G.get_map(x, y) != 0) {
			x = rand() % 38 + 1;
			y = rand() % 38 + 1;
		}
		create(x, y, G);
	}
}


Food::Food(Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	new_food(G);
}

Food::Food(istream& fin, Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	int x, y;
	while (1) {
		fin >> x;
		if (x == -1)
			break;
		fin >> y;
		create(x, y, G);
	}
}

//�ض���������ʳ��ͼ��
void Food::create(int x, int y, Game& G) {
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
	G.Create_sth(x, y, 2);
}

//�Ե�ʳ��
void Food::refresh(int x, int y, Game& G)
{
	G.Create_sth(x, y, 0);
	node* p = head;
	while (!(p->x == x && p->y == y))
		p = p->next;
	//��Ҫ�Ѹ�ʳ��ǰ��ָ��������

	//���һ��ʳ��ʱˢ��ʳ��
	if (p == head && p == tail) {
		head = NULL, tail = NULL;
		delete p;
		new_food(G);
	}
	else if (p == head) {
		head = p->next;
		delete p;
	}
	else if (p == tail) {
		node* q = head;
		while (q->next != p)
			q = q->next;
		tail = q;
		q->next = NULL;
		delete p;
	}
	else {
		node* q = head;
		for (q; q->next != NULL; q = q->next) {
			if (q->next == p) {
				q->next = p->next;
				delete p;
				break;
			}
		}
	}
}


Food::~Food() {
	if (!destructed) {
		ofstream fin("./file//last_game.txt", ios::app);
		if (!fin.is_open()) {
			exit(1);
		}
		node* p = head, * q;
		while (p != NULL) {
			fin << p->x << " " << p->y << " ";
			q = p;
			p = p->next;
			delete q;
		}
		fin << "-1" << endl;
		fin.close();
	}
	destructed = 1;
}
