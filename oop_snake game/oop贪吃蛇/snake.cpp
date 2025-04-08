#include "objects.h"
#include<iostream>
#include<fstream>

using namespace std;

Snake::Snake(Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	last_x = -1, last_y = -1;
	int x, y;
	while (1) {
		x = rand() % 38 + 1;
		y = rand() % 38 + 1;
		dir = rand() % 4;
		//取随机坐标和方向，判断不能生成蛇就重新取数
		if (dir == 0) {
			if (G.get_map(x, y) != 0 || G.get_map(x + 1, y) != 0 || G.get_map(x + 2, y) != 0)
				continue;
			else {
				create(x, y, G);
				create(x + 1, y, G);
				create(x + 2, y, G);
				break;
			}
		}
		else if (dir == 1) {
			if (G.get_map(x, y) != 0 || G.get_map(x - 1, y) != 0 || G.get_map(x - 2, y) != 0)
				continue;
			else {
				create(x, y, G);
				create(x - 1, y, G);
				create(x - 2, y, G);
				break;
			}
		}
		else if (dir == 2) {
			if (G.get_map(x, y) != 0 || G.get_map(x, y + 1) != 0 || G.get_map(x, y + 2) != 0)
				continue;
			else {
				create(x, y, G);
				create(x, y + 1, G);
				create(x, y + 2, G);
				break;
			}
		}
		else if (dir == 3) {
			if (G.get_map(x, y) != 0 || G.get_map(x, y - 1) != 0 || G.get_map(x, y - 2) != 0)
				continue;
			else {
				create(x, y, G);
				create(x, y - 1, G);
				create(x, y - 2, G);
				break;
			}
		}
	}
}

Snake::Snake(istream& in, Game& G) {
	head = NULL, tail = NULL;
	destructed = 0;
	in >> dir >> last_x >> last_y;
	int x, y;
	while (1) {
		in >> x;
		if (x == -1) break;
		in >> y;
		create(x, y, G);
	}
}



void Snake::create(int x, int y, Game& G) {
	node* p = new node;
	p->x = x, p->y = y;
	if (head == NULL)
		head = p, tail = p;
	else {
		tail->next = p;
		p->next = NULL;
		tail = p;
	}
	G.Create_sth(x, y, 3);
}

node* Snake::snake_head() {
	return head;
}


void Snake::move(int direction, Game& G)
{
	if (direction != -1)
		dir = direction;
	last_x = tail->x;
	last_y = tail->y;
	G.Create_sth(tail->x, tail->y, 0);

	//去掉尾部
	node* p = tail;
	node* q = head;
	while (q->next != tail)
		q = q->next;
	tail = q;
	q->next = NULL;
	delete p;

	//增加头部
	int d_of_x[4] = { -1,1,0,0 }, d_of_y[4] = { 0,0,-1,1 };
	int hx = head->x, hy = head->y;
	node* cur = new node;
	cur->x = hx + d_of_x[dir];
	cur->y = hy + d_of_y[dir];
	cur->next = head;
	head = cur;
}

//上一步被消除的尾巴在吃到食物后恢复
void Snake::recover(Game& G) {
	create(last_x, last_y, G);
}

//对死亡小蛇进行处理，按照模式变成对应物体
bool Snake::reset(Game& G, Food& F, Wall& W, int type) {
	node* p = head, * q;
	while (p != NULL) {
		q = p->next;
		if (p != head) {
			G.Create_sth(p->x, p->y, 0); //进行一些擦白
			if (type == 1)
				W.create(p->x, p->y, G);
			else if (type == 2)
				F.create(p->x, p->y, G);
		}
		delete p;
		p = q;
	}
	//先判断剩余空间能不能生成新的小蛇
	bool ade = 0; //是否有足够的空间
	//纵向判断
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40 - 2; j++) {
			if (G.get_map(i, j) == 0 && G.get_map(i, j + 1) == 0 && G.get_map(i, j + 2) == 0) {
				ade = 1;
				break;
			}
		}
		if (ade == 1) break;
	}
	//横向判断
	if (!ade) {
		for (int j = 0; j < 40; j++) {
			for (int i = 0; i < 40 - 2; i++) {
				if (G.get_map(i, j) == 0 && G.get_map(i + 1, j) == 0 && G.get_map(i + 2, j) == 0) {
					ade = 1;
					break;
				}
			}
			if (ade == 1)break;
		}
	}
	if (!ade)return 0;
	
	//生成新蛇
	head = NULL, tail = NULL;
	int x, y;
	while (1) {
		x = rand() % 38 + 1;
		y = rand() % 38 + 1;
		dir = rand() % 4;
		//取随机坐标和方向，判断不能生成蛇就重新取数
		if (dir == 0) {
			if (G.get_map(x, y) != 0 || G.get_map(x + 1, y) != 0 || G.get_map(x + 2, y) != 0)
				continue;
			else {
				create(x, y, G);
				create(x + 1, y, G);
				create(x + 2, y, G);
				break;
			}
		}
		else if (dir == 1) {
			if (G.get_map(x, y) != 0 || G.get_map(x - 1, y) != 0 || G.get_map(x - 2, y) != 0)
				continue;
			else {
				create(x, y, G);
				create(x - 1, y, G);
				create(x - 2, y, G);
				break;
			}
		}
		else if (dir == 2) {
			if (G.get_map(x, y) != 0 || G.get_map(x, y + 1) != 0 || G.get_map(x, y + 2) != 0)
				continue;
			else {
				create(x, y, G);
				create(x, y + 1, G);
				create(x, y + 2, G);
				break;
			}
		}
		else if (dir == 3) {
			if (G.get_map(x, y) != 0 || G.get_map(x, y - 1) != 0 || G.get_map(x, y - 2) != 0)
				continue;
			else {
				create(x, y, G);
				create(x, y - 1, G);
				create(x, y - 2, G);
				break;
			}
		}
	}
	return 1;
}


int Snake::get_dir() {
	return dir;
}


Snake::~Snake() {
	if (!destructed) {
		ofstream fl("./file//last_game.txt", ios::app);
		if (!fl.is_open()) {
			cout << "文件打开失败" << endl;
			exit(1);
		}
		fl << dir << " " << last_x << " " << last_y << endl;
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


