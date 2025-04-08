#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<graphics.h>
#include<fstream>
#include "game.h"
#include "objects.h"
#include"control.h"
using namespace std;

int time_count = 0;

//��ȡ������Ϣ
int key_monitor() {
	// ��ȡ��ǰ���̵ľ��
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);

	// ��������ģʽΪ��ؼ�������
	DWORD prev_mode;
	GetConsoleMode(hConsole, &prev_mode);
	SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS | ENABLE_INSERT_MODE | ENABLE_QUICK_EDIT_MODE | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	bool running = true;
	INPUT_RECORD inputBuffer[128];
	DWORD numEvents = 0;

	GetNumberOfConsoleInputEvents(hConsole, &numEvents);
	if (numEvents != 0) {
		ReadConsoleInput(hConsole, inputBuffer, 128, &numEvents);
		for (DWORD i = 0; i < numEvents; ++i) {
			if (inputBuffer[i].EventType == KEY_EVENT && inputBuffer[i].Event.KeyEvent.bKeyDown) {
				// �����¼�
				KEY_EVENT_RECORD keyEvent = inputBuffer[i].Event.KeyEvent;
				char keyPressed = keyEvent.uChar.AsciiChar;
				if (keyPressed == 27 || keyPressed == 97 || keyPressed == 119 || keyPressed == 115 || keyPressed == 100 || keyPressed == 32)
				{
					return int(keyPressed);
				}
				else
					return -1;
			}
		}
	}
	// �����ӳ�
	Sleep(80);
	time_count += 80;
	// �ָ�����̨����ģʽ
	SetConsoleMode(hConsole, prev_mode);

	return -1;
}

//���Ű�
int play_one(Game& G, Wall& W, Food& F, Snake& S)
{
	//װ��
	IMAGE pic_rina;
	loadimage(&pic_rina, _T("./images//rina_board.jpg"), 485 * 0.6, 424 * 0.6);
	putimage(850, 30, &pic_rina);

	//ʱ������
	setbkcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	settextcolor(BLACK);
	f.lfHeight = 35, f.lfWeight = 35;
	settextstyle(&f);

	TCHAR s[10];
	TCHAR m[20];
	RECT r1{ 800, 300, 1000, 350 };
	RECT r2{ 1000, 300, 1100, 350 };
	RECT r3{ 800,350,1200,400 };

	int minutes = 0, seconds = 0;
	
	int last_do = 0;  //��һ������
	while (1) {
		//ʱ�Ӵ�ӡ
		if (time_count >= 1000) {
			seconds++;
			if (seconds == 60) {
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(800, 300, 1200, 350);
				seconds = 0;
				minutes++;
			}
			_stprintf_s(s, _T(":%d"), seconds); // ��ʽ���ַ���
			_stprintf_s(m, _T("Time��%d"), minutes); // ��ʽ���ַ���
			drawtext(m, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			drawtext(s, &r2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			time_count = 0;
		}

		//��ȡ����
		int key2 = key_monitor();
		int dir = S.get_dir();
		if (dir == 1 && key2 == 97 || dir == 0 && key2 == 100 || dir == 3 && key2 == 119 || dir == 2 && key2 == 115)
			continue;
		switch (key2) {
		case -1:
		case 32:
			S.move(-1, G);
			break;
		case 97:
			S.move(0, G);
			break;
		case 100:
			S.move(1, G);
			break;
		case 115:
			S.move(3, G);
			break;
		case 119:
			S.move(2, G);
			break;
		case 27:
			return 1;
			break;
		}
		node* sh = S.snake_head();
		int type = G.get_map(sh->x, sh->y);
		
		//�����ߵ��ĸ������ͽ��в���
		if (type == 0) { //�հ״�
			G.Create_sth(sh->x, sh->y, 3);
			if (last_do >= 2)
				last_do--;
			if (last_do == 1) {
				loadimage(&pic_rina, _T("./images//rina_board.jpg"), 485 * 0.6, 424 * 0.6);
				putimage(850, 30, &pic_rina);
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(800, 350, 1200, 400);
				last_do--;
			}
		}
		else if (type == 1) { //ײ��ǽ��ʾ����
			IMAGE pic_rina_mad;
			loadimage(&pic_rina_mad, _T("./images//rina_board_mad.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_mad);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�� X�nX ��"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			return 0;
		}
		else if (type == 2) { //�Ե�ʳ����ʾЦ��
			F.refresh(sh->x, sh->y, G);
			S.recover(G);
			G.Create_sth(sh->x, sh->y, 3);
			G.cal_length();
			G.Score_value();
			G.length_value();
			IMAGE pic_rina_happy;
			loadimage(&pic_rina_happy, _T("./images//rina_board_happy.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_happy);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�d(�R���Q*)o"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			last_do = 6;
		}
		else if (type == 3) { //ײ��������ʾ����
			IMAGE pic_rina_mad;
			loadimage(&pic_rina_mad, _T("./images//rina_board_mad.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_mad);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�� X�nX ��"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			return 0;
		}
		Sleep(50);
		time_count += 50;
	}
}

//���װ�
int play_two(Game& G, Wall& W, Food& F, Snake& S)
{
	//װ��
	IMAGE pic_rina;
	loadimage(&pic_rina, _T("./images//rina_board.jpg"), 485 * 0.6, 424 * 0.6);
	putimage(850, 30, &pic_rina);

	setbkcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	settextcolor(BLACK);
	f.lfHeight = 35, f.lfWeight = 35;
	settextstyle(&f);

	TCHAR s[10];
	TCHAR m[20];
	RECT r1{ 800, 300, 1000, 350 };
	RECT r2{ 1000, 300, 1100, 350 };
	RECT r3{ 800,350,1200,400 };

	int minutes = 0, seconds = 0;

	int last_do = 0;
	while (G.get_blank() >= 5) {
		if (time_count >= 1000) {
			seconds++;
			if (seconds == 60) {
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(800, 300, 1200, 350);
				seconds = 0;
				minutes++;
			}
			_stprintf_s(s, _T(":%d"), seconds); // ��ʽ���ַ���
			_stprintf_s(m, _T("Time��%d"), minutes); // ��ʽ���ַ���
			drawtext(m, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			drawtext(s, &r2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			time_count = 0;
		}
		int key2 = key_monitor();
		int dir = S.get_dir();
		if (dir == 1 && key2 == 97 || dir == 0 && key2 == 100 || dir == 3 && key2 == 119 || dir == 2 && key2 == 115)
			continue;
		switch (key2) {
		case -1:
		case 32:
			S.move(-1, G);
			break;
		case 97:
			S.move(0, G);
			break;
		case 100:
			S.move(1, G);
			break;
		case 115:
			S.move(3, G);
			break;
		case 119:
			S.move(2, G);
			break;
		case 27:
			return 2;
			break;
		}
		node* sh = S.snake_head();
		int type = G.get_map(sh->x, sh->y);

		if (type == 0) { //�հ�
			G.Create_sth(sh->x, sh->y, 3);
			if (last_do >= 2)
				last_do--;
			if (last_do == 1) {
				loadimage(&pic_rina, _T("./images//rina_board.jpg"), 485 * 0.6, 424 * 0.6);
				putimage(850, 30, &pic_rina);
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(800, 350, 1200, 400);
				last_do--;
			}
		}
		else if (type == 1) { 
			S.reset(G, F, W, 1);//ʬ����ǽ��
			G.cal_length(1);
			G.length_value();
			IMAGE pic_rina_mad;
			loadimage(&pic_rina_mad, _T("./images//rina_board_mad.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_mad);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�� X�nX ��"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			last_do = 6;
		}
		else if (type == 2) {  //�Ե�ʳ��
			F.refresh(sh->x, sh->y, G);
			S.recover(G);
			G.Create_sth(sh->x, sh->y, 3);
			G.cal_length();
			G.Score_value();
			G.length_value();
			IMAGE pic_rina_happy;
			loadimage(&pic_rina_happy, _T("./images//rina_board_happy.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_happy);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�d(�R���Q*)o"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			last_do = 5;
		}
		else if (type == 3) { //ʬ����ǽ��
			S.reset(G, F, W, 1);
			G.cal_length(1);
			G.length_value();
			IMAGE pic_rina_mad;
			loadimage(&pic_rina_mad, _T("./images//rina_board_mad.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_mad);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�� X�nX ��"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			last_do = 5;
		}
		Sleep(50);
		time_count += 50;
	}
}

//�߼���
int play_three(Game& G, Wall& W, Food& F, Snake& S)
{
	//װ��
	IMAGE pic_rina;
	loadimage(&pic_rina, _T("./images//rina_board.jpg"), 485 * 0.6, 424 * 0.6);
	putimage(850, 30, &pic_rina);

	setbkcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy(f.lfFaceName, _T("����"));
	settextcolor(BLACK);
	f.lfHeight = 35, f.lfWeight = 35;
	settextstyle(&f);

	TCHAR s[10];
	TCHAR m[20];
	RECT r1{ 800, 300, 1000, 350 };
	RECT r2{ 1000, 300, 1100, 350 };
	RECT r3{ 800,350,1200,400 };

	int minutes = 0, seconds = 0;

	int last_do = 0;

	while (G.get_hp() > 0 && G.get_blank() >= 5) {
		if (time_count >= 1000) {
			seconds++;
			if (seconds == 60) {
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(800, 300, 1200, 350);
				seconds = 0;
				minutes++;
			}
			_stprintf_s(s, _T(":%d"), seconds); // ��ʽ���ַ���
			_stprintf_s(m, _T("Time��%d"), minutes); // ��ʽ���ַ���
			drawtext(m, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			drawtext(s, &r2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			time_count = 0;
		}

		int key2 = key_monitor();
		int dir = S.get_dir();
		if (dir == 1 && key2 == 97 || dir == 0 && key2 == 100 || dir == 3 && key2 == 119 || dir == 2 && key2 == 115)
			continue;
		switch (key2) {
		case -1:
		case 32:
			S.move(-1, G);
			break;
		case 97:
			S.move(0, G);
			break;
		case 100:
			S.move(1, G);
			break;
		case 115:
			S.move(3, G);
			break;
		case 119:
			S.move(2, G);
			break;
		case 27:
			return 3;
			break;
		}
		node* sh = S.snake_head();
		int type = G.get_map(sh->x, sh->y);

		if (type == 0) { 
			G.Create_sth(sh->x, sh->y, 3);
			if (last_do >= 2)
				last_do--;
			if (last_do == 1) {
				loadimage(&pic_rina, _T("./images//rina_board.jpg"), 485 * 0.6, 424 * 0.6);
				putimage(850, 30, &pic_rina);
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillrectangle(800, 350, 1200, 400);
				last_do--;
			}
		}
		else if (type == 1) {
			S.reset(G, F, W, 2);//ʬ����ʳ��
			G.HP_value();
			G.cal_length(1);
			G.length_value();
			int live = G.get_hp();
			IMAGE pic_rina_mad;
			loadimage(&pic_rina_mad, _T("./images//rina_board_mad.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_mad);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�� X�nX ��"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			last_do = 6;
			if (live == 0)
				return 0;
		}
		else if (type == 2) { 
			F.refresh(sh->x, sh->y, G);
			S.recover(G);
			G.Create_sth(sh->x, sh->y, 3);
			G.cal_length();
			G.Score_value();
			G.length_value();
			IMAGE pic_rina_happy;
			loadimage(&pic_rina_happy, _T("./images//rina_board_happy.jpg"), 485 * 0.6, 424 * 0.6);
			fillrectangle(800, 350, 1200, 400);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�d(�R���Q*)o"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			putimage(850, 30, &pic_rina_happy);
			last_do = 6;
		}
		else if (type == 3) { //ʬ����ʳ��
			S.reset(G, F, W, 2);
			G.HP_value();
			G.cal_length(1);
			G.length_value();
			int live = G.get_hp();
			IMAGE pic_rina_mad;
			loadimage(&pic_rina_mad, _T("./images//rina_board_mad.jpg"), 485 * 0.6, 424 * 0.6);
			putimage(850, 30, &pic_rina_mad);
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillrectangle(800, 350, 1200, 400);
			settextcolor(RGB(255, 182, 193));
			drawtext(_T("�� X�nX ��"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextcolor(BLACK);
			last_do = 5;
			if (live == 0)
				return 0;
		}
		Sleep(50);
		time_count += 50;
	}
}

//��ʼ��Ϸ���ո���ƿ�ʼ
int start(Game& G, Wall& W, Food& F, Snake& S, int mode) 
{
	int key1 = 0;
	while (key1 != 32) 
		key1 = key_monitor(); 

	int a = 0;//����ֵ
	if (mode == 1)
		a = play_one(G, W, F, S);
	else if (mode == 2)
		a = play_two(G, W, F, S);
	else if (mode == 3)
		a = play_three(G, W, F, S);

	return a;
}

