#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <graphics.h>
#include <fstream>
#include "control.h"
#include "menu.h"
using namespace std;

int main_menu()
{
	initgraph(1200, 800);
	
	//����ͼƬ
	IMAGE pic0;
	loadimage(&pic0, _T("./images//main_menu.png"), 1200, 800);
	putimage(0, 0, &pic0);
	
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	setfillcolor(WHITE);
	
	//����˵�����
	LOGFONT f; 
	gettextstyle(&f); 
	f.lfHeight = 40, f.lfWeight = 130; 
	_tcscpy(f.lfFaceName, _T("����")); 
	f.lfQuality = ANTIALIASED_QUALITY; 
	settextstyle(&f); //����������ʽ
	settextcolor(RGB(0,139,139));
	setbkcolor(WHITE);
	//���ֿ�
	RECT R1 = { 0,450,400,600 };
	RECT R2 = { 400,450,800,600 };
	RECT R3 = { 800,450,1200,600 };
	//�����Դ������ֿ�
	fillrectangle(50, 470, 350, 580);
	fillrectangle(450, 470, 750, 580);
	fillrectangle(850, 470, 1150, 580);
	drawtext(_T("START GAME"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("CONTINUE"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("HISTORY"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	
	MOUSEMSG m; //���ָ��
	int jud = 0;
	int last_do = -1;  //��¼�����һ������
	while (1) {
		m = GetMouseMsg(); //��ȡһ�������Ϣ
		switch (m.uMsg) {
			case WM_MOUSEMOVE:
				setlinecolor(RGB(0, 139, 139));
				settextcolor(WHITE);
				setbkcolor(RGB(0, 139, 139));
				setfillcolor(RGB(0, 139, 139));
				f.lfHeight = 50, f.lfWeight = 140;
				settextstyle(&f); //����������ʽ
				if (m.x > 50 && m.x < 350 && m.y>470 && m.y < 580)
					jud = 1;
				else if (m.x > 450 && m.x < 750 && m.y>470 && m.y < 580)
					jud = 2;
				else if (m.x > 850 && m.x < 1150 && m.y>470 && m.y < 580)
					jud = 3;
				else
					jud = 0;
				
				if (last_do != 0&&jud == 1) {
					fillrectangle(50, 470, 350, 580);
					drawtext(_T("START GAME"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					last_do = 0;
				}
				else if (last_do != 1&&jud == 2) {
					fillrectangle(450, 470, 750, 580);
					drawtext(_T("CONTINUE"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					last_do = 1;
				}
				else if (last_do != 2&&jud == 3) {
					fillrectangle(850, 470, 1150, 580);
					drawtext(_T("HISTORY"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					last_do = 2;
				}
				
				if (last_do != -1 && jud == 0) {
					setlinecolor(WHITE);
					settextcolor(RGB(0, 139, 139));
					setbkcolor(WHITE);
					setfillcolor(WHITE);
					f.lfHeight = 40, f.lfWeight = 130;
					settextstyle(&f); //����������ʽ
					
					if (last_do==0)
						fillrectangle(50, 470, 350, 580);
						drawtext(_T("START GAME"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					if (last_do==1)
						fillrectangle(450, 470, 750, 580);
						drawtext(_T("CONTINUE"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					if(last_do==2)
						fillrectangle(850, 470, 1150, 580);
						drawtext(_T("HISTORY"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					last_do = -1;
				}
				break;

			case WM_LBUTTONDOWN:
				if (m.x > 50 && m.x < 350 && m.y>470 && m.y < 580)
					jud = 1;
				else if (m.x > 450 && m.x < 750 && m.y>470 && m.y < 580)
					jud = 2;
				else if (m.x > 850 && m.x < 1150 && m.y>470 && m.y < 580)
					jud = 3;
				else
					jud = 0;

				if (jud == 1) {
					return start_menu();
				}
				else if (jud == 2) {
					setbkcolor(WHITE);
					cleardevice();
					return 4;
				}
				else if (jud == 3) {
					history_menu();
					return 0;
				}
				break;
				FlushMouseMsgBuffer();//��������Ϣ������
		}
	}
}


int start_menu()
{
	setbkcolor(RGB(255, 240, 245));
	cleardevice();
	//����ͼƬ
	IMAGE pic0;
	loadimage(&pic0, _T("./images//start_menu_0.png"), 1200, 630);
	putimage(0, 0, &pic0);

	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	setfillcolor(WHITE);
	
	//����˵�����
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40, f.lfWeight = 130;
	_tcscpy(f.lfFaceName, _T("����"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f); //����������ʽ
	settextcolor(RGB(0, 139, 139));
	setbkcolor(WHITE);
	//���ֿ�
	RECT R1 = { 0,630,400,780 };
	RECT R2 = { 400,630,800,780 };
	RECT R3 = { 800,630,1200,780 };
	fillrectangle(50, 650, 350, 760);
	fillrectangle(450, 650, 750, 760);
	fillrectangle(850, 650, 1150, 760);
	drawtext(_T("���Ű�"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("���װ�"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(_T("�߼���"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ

	IMAGE pic1;
	loadimage(&pic1, _T("./images//start_menu_1.png"), 1200, 630);
	IMAGE pic2;
	loadimage(&pic2, _T("./images//start_menu_2.png"), 1200, 630);
	IMAGE pic3;
	loadimage(&pic3, _T("./images//start_menu_3.png"), 1200, 630);

	MOUSEMSG m; //���ָ��
	int jud = 0;
	int last_do = -1;
	while (1) {
		m = GetMouseMsg(); //��ȡһ�������Ϣ
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			setlinecolor(RGB(0, 139, 139));
			settextcolor(WHITE);
			setbkcolor(RGB(0, 139, 139));
			setfillcolor(RGB(0, 139, 139));
			f.lfHeight = 50, f.lfWeight = 140;
			settextstyle(&f); //����������ʽ
			if (m.x > 50 && m.x < 350 && m.y>650 && m.y < 760)
				jud = 1;
			else if (m.x > 450 && m.x < 750 && m.y>650 && m.y < 760)
				jud = 2;
			else if (m.x > 850 && m.x < 1150 && m.y>650 && m.y < 760)
				jud = 3;
			else
				jud = 0;

			if (last_do != 0 && jud == 1) {
				fillrectangle(50, 650, 350, 760);
				drawtext(_T("���Ű�"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				last_do = 0;
				putimage(0, 0, &pic1);
			}
			else if (last_do != 1&&jud == 2) {
				fillrectangle(450, 650, 750, 760);
				drawtext(_T("���װ�"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				last_do = 1;
				putimage(0, 0, &pic2);
			}
			else if (last_do != 2&&jud == 3) {
				fillrectangle(850, 650, 1150, 760);
				drawtext(_T("�߼���"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				last_do = 2;
				putimage(0, 0, &pic3);
			}

			if (last_do != -1 && jud == 0) {
				setlinecolor(WHITE);
				settextcolor(RGB(0, 139, 139));
				setbkcolor(WHITE);
				setfillcolor(WHITE);
				f.lfHeight = 40, f.lfWeight = 130;
				settextstyle(&f); //����������ʽ
				if (last_do == 0)
					fillrectangle(50, 650, 350, 760);
					drawtext(_T("���Ű�"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (last_do == 1)
					fillrectangle(450, 650, 750, 760);
					drawtext(_T("���װ�"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (last_do == 2)
					fillrectangle(850, 650, 1150, 760);
					drawtext(_T("�߼���"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				loadimage(&pic0, _T("./images//start_menu_0.png"), 1200, 630);
				putimage(0, 0, &pic0);
				last_do = -1;
			}
			break;

		case WM_LBUTTONDOWN:
			if (m.x > 50 && m.x < 350 && m.y>650 && m.y < 760)
				jud = 1;
			else if (m.x > 450 && m.x < 750 && m.y>650 && m.y < 760)
				jud = 2;
			else if (m.x > 850 && m.x < 1150 && m.y>650 && m.y < 760)
				jud = 3;
			else
				jud = 0;

			if (jud != 0) {
				setbkcolor(WHITE);
				return jud;
			}
			break;
			FlushMouseMsgBuffer();//��������Ϣ������
		}
	}
}


void history_menu()
{
	setbkcolor(WHITE);
	cleardevice();

	ifstream fin("./file//history.txt", ios::app);
	
	//�������
	int x1 = 0, x2 = 200, x3 = 400, x4 = 600;
	int y1 = 0, y2 = 30;


	while (!fin.eof()) {
		//��ȡ��ʷ��Ϣ
		int type, score;
		string name;
		if (!(fin >> type >> name >>score))
			break;

		//�����ʷ��Ϣ
		LOGFONT f; 
		gettextstyle(&f); 
		_tcscpy(f.lfFaceName, _T("����"));
		f.lfHeight = 20, f.lfWeight = 20; //���������С
		f.lfQuality = ANTIALIASED_QUALITY; //�������Ч��Ϊ�����
		settextstyle(&f); //����������ʽ
		settextcolor(BLACK);
		
		//�����������ֱ�Ϊ���������
		TCHAR s_score[20];         // EasyX����������Ҫ���ַ�����������
		_stprintf_s(s_score, _T("%d"), score); 

		TCHAR s_name[20];         // EasyX����������Ҫ���ַ�����������
		int i = 0;
		for (i = 0; i < name.size(); i++) {
			s_name[i] = name[i];
		}
		s_name[i] = '\0';

		RECT R = { 800,550,1200,600 };

		RECT R1 = { x1,y1,x1 + 100,y2 };
		RECT R2 = { x1 + 100,y1,x2,y2 };
		RECT R3 = { x2,y1,x2 + 100,y2 };
		RECT R4 = { x2 + 100,y1,x3,y2 };
		RECT R5 = { x3,y1,x3 + 100,y2 };
		RECT R6 = { x3 + 100,y1,x4,y2 };

		drawtext(_T("�汾��"), &R1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		switch (type) {
			case 1:
				drawtext(_T("���Ű�"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				break;
			case 2:
				drawtext(_T("���װ�"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				break;
			case 3:
				drawtext(_T("�߼���"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				break;
		}
		drawtext(_T("������"), &R3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(s_score, &R4, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("�û�����"), &R5, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(s_name, &R6, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

		y1 += 30;
		y2 += 30;
	}

	while (key_monitor() != 27);
}