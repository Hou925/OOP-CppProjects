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
	
	//背景图片
	IMAGE pic0;
	loadimage(&pic0, _T("./images//main_menu.png"), 1200, 800);
	putimage(0, 0, &pic0);
	
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	setfillcolor(WHITE);
	
	//输出菜单文字
	LOGFONT f; 
	gettextstyle(&f); 
	f.lfHeight = 40, f.lfWeight = 130; 
	_tcscpy(f.lfFaceName, _T("黑体")); 
	f.lfQuality = ANTIALIASED_QUALITY; 
	settextstyle(&f); //设置字体样式
	settextcolor(RGB(0,139,139));
	setbkcolor(WHITE);
	//文字框
	RECT R1 = { 0,450,400,600 };
	RECT R2 = { 400,450,800,600 };
	RECT R3 = { 800,450,1200,600 };
	//矩形略大于文字框
	fillrectangle(50, 470, 350, 580);
	fillrectangle(450, 470, 750, 580);
	fillrectangle(850, 470, 1150, 580);
	drawtext(_T("START GAME"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("CONTINUE"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("HISTORY"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	
	MOUSEMSG m; //鼠标指针
	int jud = 0;
	int last_do = -1;  //记录鼠标上一步操作
	while (1) {
		m = GetMouseMsg(); //获取一条鼠标消息
		switch (m.uMsg) {
			case WM_MOUSEMOVE:
				setlinecolor(RGB(0, 139, 139));
				settextcolor(WHITE);
				setbkcolor(RGB(0, 139, 139));
				setfillcolor(RGB(0, 139, 139));
				f.lfHeight = 50, f.lfWeight = 140;
				settextstyle(&f); //设置字体样式
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
					settextstyle(&f); //设置字体样式
					
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
				FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
}


int start_menu()
{
	setbkcolor(RGB(255, 240, 245));
	cleardevice();
	//背景图片
	IMAGE pic0;
	loadimage(&pic0, _T("./images//start_menu_0.png"), 1200, 630);
	putimage(0, 0, &pic0);

	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	setfillcolor(WHITE);
	
	//输出菜单文字
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40, f.lfWeight = 130;
	_tcscpy(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f); //设置字体样式
	settextcolor(RGB(0, 139, 139));
	setbkcolor(WHITE);
	//文字框
	RECT R1 = { 0,630,400,780 };
	RECT R2 = { 400,630,800,780 };
	RECT R3 = { 800,630,1200,780 };
	fillrectangle(50, 650, 350, 760);
	fillrectangle(450, 650, 750, 760);
	fillrectangle(850, 650, 1150, 760);
	drawtext(_T("入门版"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("进阶版"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext(_T("高级版"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示

	IMAGE pic1;
	loadimage(&pic1, _T("./images//start_menu_1.png"), 1200, 630);
	IMAGE pic2;
	loadimage(&pic2, _T("./images//start_menu_2.png"), 1200, 630);
	IMAGE pic3;
	loadimage(&pic3, _T("./images//start_menu_3.png"), 1200, 630);

	MOUSEMSG m; //鼠标指针
	int jud = 0;
	int last_do = -1;
	while (1) {
		m = GetMouseMsg(); //获取一条鼠标消息
		switch (m.uMsg) {
		case WM_MOUSEMOVE:
			setlinecolor(RGB(0, 139, 139));
			settextcolor(WHITE);
			setbkcolor(RGB(0, 139, 139));
			setfillcolor(RGB(0, 139, 139));
			f.lfHeight = 50, f.lfWeight = 140;
			settextstyle(&f); //设置字体样式
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
				drawtext(_T("入门版"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				last_do = 0;
				putimage(0, 0, &pic1);
			}
			else if (last_do != 1&&jud == 2) {
				fillrectangle(450, 650, 750, 760);
				drawtext(_T("进阶版"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				last_do = 1;
				putimage(0, 0, &pic2);
			}
			else if (last_do != 2&&jud == 3) {
				fillrectangle(850, 650, 1150, 760);
				drawtext(_T("高级版"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				last_do = 2;
				putimage(0, 0, &pic3);
			}

			if (last_do != -1 && jud == 0) {
				setlinecolor(WHITE);
				settextcolor(RGB(0, 139, 139));
				setbkcolor(WHITE);
				setfillcolor(WHITE);
				f.lfHeight = 40, f.lfWeight = 130;
				settextstyle(&f); //设置字体样式
				if (last_do == 0)
					fillrectangle(50, 650, 350, 760);
					drawtext(_T("入门版"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (last_do == 1)
					fillrectangle(450, 650, 750, 760);
					drawtext(_T("进阶版"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (last_do == 2)
					fillrectangle(850, 650, 1150, 760);
					drawtext(_T("高级版"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
			FlushMouseMsgBuffer();//清空鼠标消息缓存区
		}
	}
}


void history_menu()
{
	setbkcolor(WHITE);
	cleardevice();

	ifstream fin("./file//history.txt", ios::app);
	
	//输出坐标
	int x1 = 0, x2 = 200, x3 = 400, x4 = 600;
	int y1 = 0, y2 = 30;


	while (!fin.eof()) {
		//读取历史信息
		int type, score;
		string name;
		if (!(fin >> type >> name >>score))
			break;

		//输出历史信息
		LOGFONT f; 
		gettextstyle(&f); 
		_tcscpy(f.lfFaceName, _T("黑体"));
		f.lfHeight = 20, f.lfWeight = 20; //设置字体大小
		f.lfQuality = ANTIALIASED_QUALITY; //设置输出效果为抗锯齿
		settextstyle(&f); //设置字体样式
		settextcolor(BLACK);
		
		//将分数和名字变为可输出类型
		TCHAR s_score[20];         // EasyX设置文字需要的字符串变量类型
		_stprintf_s(s_score, _T("%d"), score); 

		TCHAR s_name[20];         // EasyX设置文字需要的字符串变量类型
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

		drawtext(_T("版本："), &R1, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		switch (type) {
			case 1:
				drawtext(_T("入门版"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				break;
			case 2:
				drawtext(_T("进阶版"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				break;
			case 3:
				drawtext(_T("高级版"), &R2, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				break;
		}
		drawtext(_T("分数："), &R3, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(s_score, &R4, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("用户名："), &R5, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		drawtext(s_name, &R6, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

		y1 += 30;
		y2 += 30;
	}

	while (key_monitor() != 27);
}