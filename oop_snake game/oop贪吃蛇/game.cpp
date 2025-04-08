#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<graphics.h>
#include<fstream>
#include<conio.h>
#include "game.h"

using namespace std;


Game::Game(int mode)
{
	RECT R1 = { 300,250,900,350 };
	RECT R2 = { 200,350,1000,450 };
	RECT R3 = { 200,550,1000,650 };

	//�����û���
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 48;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f); //����������ʽ
	settextcolor(RGB(0, 139, 139));
	setbkcolor(WHITE);
	drawtext(_T("�������û���"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("��10�ַ����ڣ���enter������"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	TCHAR s[11];
	for (int i = 0; i < 10; i++) {
		name[i] = _getch();
		name[i + 1] = '\0';
		if (name[i] == 13) {
			name[i] = '\0';
			break;
		}	
		s[i] = name[i];
		s[i + 1] = '\0';
		//�������
		drawtext(s, &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	cleardevice();

	this->mode = mode;
	length = 3;
	lives = 6;
	score = -10;  //��ʼʱ���10
	gameover = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++)
			map[i][j] = 0;
	}

	ifstream fin;
	if (mode == 1) 
		fin.open("./file//max1.txt");
	else if (mode == 2) 
		fin.open("./file//max2.txt");
	else if (mode == 3) 
		fin.open("./file//max3.txt");
	if (!fin.is_open())
		exit(1);
	fin >> his_max >> his_max_name;
	fin.close();
}

//���ƹ��캯��
Game::Game(istream& fin)
{
	ifstream fin1;
	fin >> mode;

	if (mode == 1)
		fin1.open("./file//max1.txt");
	else if (mode == 2)
		fin1.open("./file//max2.txt");
	else if (mode == 3)
		fin1.open("./file//max3.txt");
	if (!fin1.is_open())
		exit(1);

	fin1 >> his_max >> his_max_name;
	fin1.close();

	fin >> length >> lives >> score;
	fin >> name;
	score -= 10;
	gameover = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++)
			map[i][j] = 0;
	}

}

//��ȡ���������
int Game::get_map(int x, int y) {
	return map[x][y];
}

//��ȡģʽ
int Game::get_mode() {
	return mode;
}

//��ȡ�հ׸�����
int Game::get_blank()
{
	int cnt = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (map[i][j] == 0)
				cnt++;
		}
	}
	return cnt;
}

//��ȡ����ֵ
int Game::get_hp()
{
	return lives;
}

void Game::cal_length(int sign)
{
	if (sign == 0)
		length++;
	else
		length = 3;
}

//���ݲ������¾��󣬴�ӡͼ��
void Game::Create_sth(int x, int y, int type)
{
	map[x][y] = type;
	IMAGE pic;

	IMAGE pic_wall;
	loadimage(&pic, _T("./images//wall.jpg"), 20, 20);
	switch (type) {
	case 0://�հ�
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillrectangle(x * 20, y * 20, x * 20 + 20, y * 20 + 20);
		break;
	case 1: //ǽ
		putimage(x * 20, y * 20, &pic);
		break;
	case 2: //ʳ��
		setlinecolor(RGB(128,0,0));
		setfillcolor(RGB(128, 0, 0));
		fillrectangle(x * 20, y * 20, x * 20 + 20, y * 20 + 20);
		break;
	case 3: //��
		setlinecolor(RGB(0, 139, 139));
		setfillcolor(RGB(0, 139, 139));
		fillcircle(x * 20 + 8, y * 20 + 8, 8);
		break;
	}
}

//������ʾ
void Game::length_value()
{
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), length); // ��ʽ���ַ���
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	settextstyle(&f);
	settextcolor(BLACK);
	f.lfHeight = 35, f.lfWeight = 35;
	//���
	RECT R = { 800,400,1000,450 };
	drawtext(_T("Length:"), &R, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	//��ֵ
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(1050, 400, 1200, 450);
	RECT R1 = { 1050,400,1200,450 };
	drawtext(s, &R1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

//��������
void Game::Score_value()
{
	score += 10;
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	settextcolor(BLACK);
	f.lfHeight = 35, f.lfWeight = 35;
	settextstyle(&f);
	//������ַ������
	RECT R1 = { 800,500,1200,550 };
	drawtext(_T("Score"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//����ת�����ַ���
	TCHAR s[20];         // EasyX����������Ҫ���ַ�����������
	_stprintf_s(s, _T("%d"), score); // ��ʽ���ַ���
	RECT R = { 800,550,1200,600 };
	drawtext(s, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//��ʷ��߷ֵĴ�����
	RECT R_name1 = { 800,700,1200,750 };
	drawtext(_T("High Score Maker��"), &R_name1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	TCHAR s_name[20];         // EasyX����������Ҫ���ַ�����������
	int i = 0;
	for (i = 0; i < his_max_name.size(); i++) {
		s_name[i] = his_max_name[i];
	}
	s_name[i] = '\0';

	//�����ʷ��߷ֿ��
	RECT R_hm0 = { 800,600,1200,650 };
	drawtext(_T("All-Time High Score"), &R_hm0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//�Ƚ�������
	if (his_max <= score) {
		his_max = score;
		for (i = 0; name[i]!='\0'; i++) {
			s_name[i] = name[i];
		}
		s_name[i] = '\0';
	}
		
	//��߷�ת�����ַ���
	_stprintf_s(s, _T("%d"), his_max); // ��ʽ���ַ���
	RECT R_hm1 = { 800,650,1200,700 };
	drawtext(s, &R_hm1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT R_name2 = { 800,750,1200,800 };
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(800, 750, 1200, 800);
	drawtext(s_name, &R_name2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

//ʣ����������
void Game::HP_value()
{
	lives--;
	char hp = char(lives + 48);
	//���
	RECT R = { 800,450,1000,500 };
	drawtext(_T("HP:"), &R, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	//��ֵ
	RECT R1 = { 1050,450,1200,500 };
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(1050, 450, 1200, 500);
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	settextstyle(&f);
	settextcolor(BLACK);
	f.lfHeight = 35, f.lfWeight = 35;
	drawtext(hp, &R1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

//���������¼
void Game::print_record()
{
	//Ϊ��ʷ����¼����Ϣ
	ofstream fout;
	fout.open("./file//history.txt", ios::app);
	if (!fout.is_open())
		exit(1);
	fout << mode << " " << name << " " << score << endl;
	fout.close();
}


Game::~Game() {
	if (gameover == 0) {
		ofstream fout;
		//Ϊ������Ϸ¼����Ϣ
		fout.open("./file//last_game.txt", ios::app);
		if (!fout.is_open())
			exit(1);
		fout << mode << endl << length << endl << lives << endl << score << endl;
		fout << name << endl;
		fout.close();
		//��ȡ��ʷ�߷���Ϣ�����±Ƚ�
		ifstream fin;
		if (mode == 1)
			fin.open("./file//max1.txt");
		if (mode == 2)
			fin.open("./file//max2.txt");
		if (mode == 3)
			fin.open("./file//max3.txt");
		if (!fin.is_open()) {
			exit(1);
		}
		int score_of_his = 0;
		char name0[11];
		fin >> score_of_his >> name0;
		fin.close();

		ofstream fout1;
		//���������ʷ�߷־͸���
		if (score_of_his <= score) {
			if (mode == 1)
				fout1.open("./file//max1.txt");
			if (mode == 2)
				fout1.open("./file//max2.txt");
			if (mode == 3)
				fout1.open("./file//max3.txt");
			if (!fout1.is_open())
				exit(1);
			fout1 << score << " " << name;
		}
		fout1.close();
	}
}
