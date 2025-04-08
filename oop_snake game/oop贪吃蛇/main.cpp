#define _CRT_SECURE_NO_WARNINGS
#include "objects.h"
#include"menu.h"
#include"control.h"
#include<iostream>
#include<graphics.h>
#include "game.h"

using namespace std;


int main() {
    while (1) {
        //ȡ�����
        srand(time(0));
        //����˵�����
        int mode = main_menu();
        while (mode == 0)
            mode = main_menu();
        cleardevice();

        //����Ϸ
        if (mode != 4) {
            Game G(mode);
            Food F(G);
            Wall W(G);
            Snake S(G);
            G.Score_value();
            G.length_value();
            int type = start(G, W, F, S, mode);

            ofstream fout("./file//last_game.txt");
            if (!fout.is_open()) {
                exit(1);
            }
            fout << type << endl;
            G.print_record();
            //��Ϊ������Ϸ��Ҫ�Ƚ���game�࣬�������ʾ����
            G.~Game();
            fout.close();
            while (key_monitor() != 27);
        }


        //������Ϸ
        else if (mode == 4) {
            ifstream fin("./file//last_game.txt");
            int resume;
            fin >> resume;

            //û�м�¼����Ϸ
            if (resume == 0) {
                RECT R1 = { 300,250,900,350 };
                RECT R2 = { 200,350,1000,450 };

                LOGFONT f;
                gettextstyle(&f);
                f.lfHeight = 48;
                _tcscpy(f.lfFaceName, _T("����"));
                f.lfQuality = ANTIALIASED_QUALITY;
                settextstyle(&f); //����������ʽ
                settextcolor(RGB(0, 139, 139));
                setbkcolor(WHITE);
                drawtext(_T("Ŀǰû�пɼ�������Ϸ"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                drawtext(_T("�밴esc�������˵���������Ϸ��"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                while (key_monitor() != 27);
            }

            //�м�¼�����������Ϸ
            else {
                Game G(fin);
                //����˳��Ҫ������Ϸ�෴
                Snake S(fin, G);
                Wall W(fin, G);
                Food F(fin, G);
                fin.close();
                int type = start(G, W, F, S, G.get_mode());
                ofstream fout("./file//last_game.txt");
                if (!fout.is_open()) {
                    exit(1);
                }
                fout << type << endl;
                fout.close();
                G.print_record();
                G.~Game();
                //���ܰ��չ���˳���Զ������������¼˳�����
                S.~Snake();
                W.~Wall();
                F.~Food();
                while (key_monitor() != 27);
            }
        }
    }
    return 0;
}

