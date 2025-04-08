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
        //取随机数
        srand(time(0));
        //进入菜单界面
        int mode = main_menu();
        while (mode == 0)
            mode = main_menu();
        cleardevice();

        //新游戏
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
            //因为继续游戏需要先建立game类，因此先显示调用
            G.~Game();
            fout.close();
            while (key_monitor() != 27);
        }


        //继续游戏
        else if (mode == 4) {
            ifstream fin("./file//last_game.txt");
            int resume;
            fin >> resume;

            //没有记录可游戏
            if (resume == 0) {
                RECT R1 = { 300,250,900,350 };
                RECT R2 = { 200,350,1000,450 };

                LOGFONT f;
                gettextstyle(&f);
                f.lfHeight = 48;
                _tcscpy(f.lfFaceName, _T("黑体"));
                f.lfQuality = ANTIALIASED_QUALITY;
                settextstyle(&f); //设置字体样式
                settextcolor(RGB(0, 139, 139));
                setbkcolor(WHITE);
                drawtext(_T("目前没有可继续的游戏"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                drawtext(_T("请按esc返回主菜单进行新游戏吧"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                while (key_monitor() != 27);
            }

            //有记录，允许继续游戏
            else {
                Game G(fin);
                //定义顺序要和新游戏相反
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
                //不能按照构造顺序自动析构，否则记录顺序错误
                S.~Snake();
                W.~Wall();
                F.~Food();
                while (key_monitor() != 27);
            }
        }
    }
    return 0;
}

