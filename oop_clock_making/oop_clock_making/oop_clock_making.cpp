#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
using namespace std;

#define PI 3.1415926  
#define MAXSNOW 250	// 雪花总数

#define bcolor0 RGB(214,25,33)
#define bcolor1 RGB(55,125,34)
#define bcolor2 RGB(240,195,189)
#define bcolor3 RGB(255,255,255)

struct tm t;	

struct Point {
    int x;
    int y;
};

struct SNOW {
    int	x;
    int y;
    int step;
    int color;
};

SNOW snow[MAXSNOW];

void InitSnow(int i)//设定单一雪花的范围和初始值
{
    snow[i].y = 45 + rand() % 390;
    snow[i].x = 45 + rand() % 550;
    while (getpixel(snow[i].x, snow[i].y) != 0) {
        snow[i].y = 45 + rand() % 390;
        snow[i].x = 45 + rand() % 550;
    }
    snow[i].step = int((rand() % 5000) / 1000 + 1);
    snow[i].color = (int)(snow[i].step * 255 / 6.0 + 0.5);
    snow[i].color = RGB(snow[i].color, snow[i].color, snow[i].color);
}

void MoveSnow(int i)//实现下落效果
{
    putpixel((int)snow[i].x, snow[i].y, 0);
    if (getpixel(snow[i].x, snow[i].y + snow[i].step) == 0) {
        snow[i].y += snow[i].step;
    }
    if (snow[i].y > 435|| getpixel(snow[i].x, snow[i].y + snow[i].step) != 0)
        InitSnow(i);
    if (getpixel(snow[i].x, snow[i].y) == 0)
        putpixel((int)snow[i].x, snow[i].y, snow[i].color);
}

void draw_smooth_line(int x1, int y1, int x2, int y2) //参考的xiaolin wu 直线抗锯齿算法
{
    int x0, y0;
    double x, y;//物理坐标
    double alpha1, alpha2;//上下像素点权重
    COLORREF r0, g0, b0, r1, g1, b1, r2, g2, b2;

    COLORREF r, g, b;
    r = GetRValue(getlinecolor());
    g = GetGValue(getlinecolor());
    b = GetBValue(getlinecolor());
    if (abs(y2 - y1) > abs(x2 - x1)) {
        for (y = y1; y != y2;) {
            x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);//用斜率沿其画点构成线
            x0 = int(x);
            y0 = int(y);

            r0 = GetRValue(getpixel(x0, y0));
            g0 = GetGValue(getpixel(x0, y0));
            b0 = GetBValue(getpixel(x0, y0));

            alpha1 = x - x0;
            alpha2 = 1 - alpha1;

            r1 = r0 * (1 - alpha1) + r * alpha1;
            g1 = g0 * (1 - alpha1) + g * alpha1;
            b1 = b0 * (1 - alpha1) + b * alpha1;
            putpixel(x0 + 1, y0, RGB(r1,g1,b1));

            r2 = r0 * (1 - alpha2) + r * alpha2;
            g2 = g0 * (1 - alpha2) + g * alpha2;
            b2 = b0 * (1 - alpha2) + b * alpha2;
            putpixel(x0, y0, RGB(r2, g2, b2));
            if (y1 > y2)
                y--;
            else
                y++;
        }
    }
    else {
        for (x = x1; x != x2;) {
            y = y1 + (x - x1) * (y2 - y1) / (x2 - x1);
            y0 = int(y);
            x0 = int(x);
            r0 = GetRValue(getpixel(x0, y0));
            g0 = GetGValue(getpixel(x0, y0));
            b0 = GetBValue(getpixel(x0, y0));

            alpha1 = y - y0;
            alpha2 = 1 - alpha1;

            r1 = r0 * (1 - alpha1) + r * alpha1;
            g1 = g0 * (1 - alpha1) + g * alpha1;
            b1 = b0 * (1 - alpha1) + b * alpha1;
            putpixel(x0, y0+1, RGB(r1, g1, b1));

            r2 = r0 * (1 - alpha2) + r * alpha2;
            g2 = g0 * (1 - alpha2) + g * alpha2;
            b2 = b0 * (1 - alpha2) + b * alpha2;
            putpixel(x0, y0, RGB(r2, g2, b2));
            if (x1 > x2)
                x--;
            else
                x++;
        }
    }
    return;
}

void draw_hands()
{
    Point center, sec_end, min_end, hour_end;//一个中心点，一个末端点
    center.x = 320;
    center.y = 240;
    int sec_length = 135;//指针长度
    int min_length = 105;
    int hour_length = 70;
    double sec_angle, min_angle, hour_angle;//指针角度
   
    time_t now;
    time(&now);
    localtime_s(&t, &now);	// 获取当地时间
    
    sec_angle = t.tm_sec * 2 * PI / 60;
    min_angle = t.tm_min * 2 * PI / 60 + sec_angle / 60;
    hour_angle = t.tm_hour * 2 * PI / 12 + min_angle / 12;//确认各指针角度
    
    // 由角度决定终点坐标
    sec_end.x = center.x + sec_length * sin(sec_angle);
    sec_end.y = center.y - sec_length * cos(sec_angle);

    min_end.x = center.x + min_length * sin(min_angle);
    min_end.y = center.y - min_length * cos(min_angle);
    
    hour_end.x = center.x + hour_length * sin(hour_angle);
    hour_end.y = center.y - hour_length * cos(hour_angle);
    
    // 画针
    setlinecolor(RGB(77, 38, 12));
    draw_smooth_line(center.x, center.y, sec_end.x, sec_end.y);
    draw_smooth_line(center.x, center.y, min_end.x, min_end.y);
    draw_smooth_line(center.x, center.y, hour_end.x, hour_end.y);


    Sleep(1000);
    //一秒之后需要清除上一次画的秒针，用表盘填充色再画一遍即可
    setcolor(RGB(224,224,224));
    line(center.x, center.y, sec_end.x, sec_end.y);
    line(center.x, center.y, min_end.x, min_end.y);
    line(center.x, center.y, hour_end.x, hour_end.y);//因为颜色和背景色相同，不需要用抗锯齿算法

}


//SDF+alpha blending
COLORREF mix_color(COLORREF bg, COLORREF color, double alpha)//SDF抗锯齿算法需要的颜色计算
{
    COLORREF mixed;
    COLORREF r, g, b;
    r = GetRValue(bg) * (1 - alpha) + GetRValue(color) * alpha;
    g = GetGValue(bg) * (1 - alpha) + GetGValue(color) * alpha;
    b = GetBValue(bg) * (1 - alpha) + GetBValue(color) * alpha;
    mixed = RGB(r, g, b);
    return mixed;
}

void SDF_draw_circle(Point p, COLORREF color, int r,int fillornot) //p是圆心，color是想要绘制的颜色，r是半径，利用sdf算法实现圆的抗锯齿
{
    for (int i = p.x - r - 100; i < p.x + r + 100; i++) {
        for (int j = p.y - r - 100; j < p.y + r + 100; j++) {     //规定一个10单位的邻域范围
            Point p1 = { i,j }; //p1是目标像素点
            double d;
            d = sqrt((pow(p1.x - p.x, 2) + pow(p1.y - p.y, 2))) - r;
            if (d < 0)
                d = 0-d;
            double alpha = 1-d/4;
            if (d < 0)
                continue;
            if (alpha >= 0 && alpha <= 1) {
                COLORREF bg = getpixel(i, j);       //获取目标像素点原来的颜色
                COLORREF mixed = mix_color(bg, color, alpha);        
                putpixel(i, j, mixed);//最终绘制像素点
            }
        }
    }
    setfillcolor(color);
    setlinecolor(color);
    if (fillornot==1)
        fillcircle(p.x, p.y, r);
}

void draw_scale(Point center)     //绘制刻度盘
{
    int x, y, i;
    for (i = 0; i < 60; i++)
    {
        x = center.x + int(175 * sin(PI * 2 * i / 60));   //获取刻度的坐标
        y = center.y - int(175 * cos(PI * 2 * i / 60));
        setlinecolor(RGB(176, 48, 96));
        setlinestyle(PS_SOLID, 5);

        if (i == 15)                    //特殊位置用线
            line(x+5, y, x - 13, y);
        else if (i == 30)
            line(x, y+5, x, y - 13);
        else if (i == 45)
            line(x-5, y, x + 13, y);
        else if (i == 0)
            line(x, y-5, x, y + 13);
        else {
            circle(x, y, 2);     //其他位置用点
        }
        setbkmode(TRANSPARENT);
        settextcolor(RGB(176, 48, 96));
        settextstyle(15, 0, L"BIZ UDPGothic");
        switch (i) {
        case 5:
            outtextxy(x-10, y + 10, '1');
            break;
        case 10:
            outtextxy(x-18, y + 3, '2');
            break;
        case 20:
            outtextxy(x - 18, y - 13, '4');
            break;
        case 25:
            outtextxy(x - 10, y -20, '5');
            break;
        case 35:
            outtextxy(x + 5, y - 20, '7');
            break;
        case 40:
            outtextxy(x + 18, y - 13, '8');
            break;
        case 50:
            outtextxy(x + 11, y + 3, '1');
            outtextxy(x + 18, y + 3, '0');
            break;
        case 55:
            outtextxy(x + 3, y + 10, '1');
            outtextxy(x + 10, y + 10, '1');
            break;
        }

    }
}


void set_blocks_color(int n)
{
    if (n % 4 == 0) {
        setfillcolor(bcolor0);
        setlinecolor(bcolor0);
    }
    else if (n % 4 == 1) {
        setfillcolor(bcolor1);
        setlinecolor(bcolor1);
    }
    else if (n % 4 == 2) {
        setfillcolor(bcolor2);
        setlinecolor(bcolor2);
    }
    else if (n % 4 == 3) {
        setfillcolor(bcolor3);
        setlinecolor(bcolor3);
    }
}

void Init_blocks(int n)
{
    set_blocks_color(n);
    fillrectangle(0, 0, 128, 45);//no1
    fillrectangle(512, 0, 640, 45);//no5
    fillrectangle(512, 435, 640, 480);//no9
    fillrectangle(0, 435, 128, 480);//no13
    n++;
    set_blocks_color(n);
    fillrectangle(128, 0, 256, 45);//no2
    fillrectangle(595,50,640,175);//no6
    fillrectangle(384,435,512,480);//no10
    fillrectangle(0, 305, 45, 430);//no14
    n++;
    set_blocks_color(n);
    fillrectangle(256, 0, 384, 45);//no3
    fillrectangle(595, 175, 640, 305);//no7
    fillrectangle(256, 435, 384, 480);//no11
    fillrectangle(0, 175, 45, 305);//no15
    n++;
    set_blocks_color(n);
    fillrectangle(384, 0, 512, 45);//no4
    fillrectangle(595, 305, 640, 430);//no8
    fillrectangle(128, 435, 256, 480);//no12
    fillrectangle(0, 50, 45, 175);//no16
    n++;
}

void init()
{
    Point center = { 320,240 };
    SDF_draw_circle(center, RGB(224, 224, 224), 180, 1);
    SDF_draw_circle(center, RGB(112, 146, 190), 170, 0);
    SDF_draw_circle(center, RGB(112, 146, 190), 183, 0);
    Init_blocks(0);
    draw_scale(center);
}

int main()
{
    struct tm t;
    time_t now;
    time(&now);
    localtime_s(&t, &now);	// 获取当地时间
    srand((unsigned)time(NULL));	// 随机种子
    initgraph(640, 480);	// 图形方式初始化
    Point center = { 320,240 };
    init();			// 自定义图形初始化函数，用于绘制时钟界面
    for (int i = 0; i < MAXSNOW; i++)//初始化雪花
        InitSnow(i);
    int n = 0;//n用于砖块的变化
    while (!_kbhit())	// 无键盘操作时进入循环
    {
        for (int i = 0; i < MAXSNOW; i++)
            MoveSnow(i);

        Init_blocks(n);
        n++;

        draw_hands();
    }
    _getch();		// 按任意键准备退出时钟程序
    closegraph();		// 退出图形界面
    return 0;
}
