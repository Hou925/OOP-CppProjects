#include <conio.h>
#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int mat1[256 * 256] = { 0 }, mat2[256 * 256] = { 0 }, mat3[256 * 256] = { 0 }, mat0[258 * 258] = { 0 };
int B1[] = { 1,1,1,1,1,1,1,1,1 },
B2[] = { -1,-2,-1,0,0,0,1,2,1 },
B3[] = { -1,0,1,-2,0,2,-1,0,1 },
B4[] = { -1,-1,-1,-1,9,-1,-1,-1,-1 },
B5[] = { -1,-1,0,-1,0,1,0,1,1 },
B6[] = { 1,2,1,2,4,2,1,2,1 };


void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

void menu()
{
    cout << "*********************************************************" << endl;
    cout << " *      1 矩阵加法      2 矩阵数乘      3 矩阵转置      *" << endl;
    cout << " *      4 矩阵乘法      5 Hadamard乘积  6 矩阵卷积      *" << endl;
    cout << " *      7 卷积应用      8 Otsu算法      0 退出系统      *" << endl;
    cout << "*********************************************************" << endl;
    cout << "选择菜单项<0~8>：" << endl;
    return;
}

void initial_mat(int sign = 0)  //矩阵初始化
{
    if (sign == 1) {
        for (int i = 0; i < 256 * 256; i++) {
            mat3[i] = 0;
            //mat0[i] = 0;
        }
    }
    else {
        for (int i = 0; i < 256 * 256; i++) {
            mat1[i] = 0;
            mat2[i] = 0;
            mat3[i] = 0;
            mat0[i] = 0;
        }
    }
    return;
}

void input_mn(int& m,int k)  //输入行列，根据参数k调整
{
    if (k == 0)
        cout << "请输入矩阵行数" << endl;
    else
        cout << "请输入矩阵列数" << endl;
    while (1) {
        cin >> m;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2048, '\n');
        }
        else if (m > 0 && m < 256)
            break;
        cout << "输入错误或越界，请重新输入" << endl;
    }

    return;
}

void input_mat(int* mat, int m, int n)   //输入矩阵元素
{
    cout << "请输入矩阵的元素" << endl;
    for (int i = 0; i < m * n; i++) {
        while (1) {
            cin >> mat[i];
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
                cout << "请输入合适的整数" << endl;
            }
            else
                break;
        }
    }

    return;
}

void print_mat(int* mat, int m, int n) //按照8位的宽度打印矩阵
{
    for (int i = 0; i < m*n; i++) {
        cout << setw(8) << mat[i];
        if ((i+1) % n == 0)
            cout << endl;
    }
    return;
}

void matriplus()   //加法
{
    system("cls");
    int m, n;
    initial_mat();
    cout << "<矩阵加法>" << endl;
    cout << "该项目要求两个数组行列分别相等" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "矩阵1：";
    input_mat(mat1, m, n);
    cout << "矩阵2：";
    input_mat(mat2, m, n);
    for (int i = 0; i < m * n; i++)
        mat3[i] = mat1[i] + mat2[i];  //加法运算在此
    cout << "运算结果为：" << endl;
    print_mat(mat3, m, n);
    cout << endl;
    wait_for_enter();

    return;
}

void nummulti()
{
    system("cls");
    int m, n, k;  //k是乘数
    initial_mat();
    cout << "<矩阵数乘>" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "参与数乘的矩阵：";
    input_mat(mat1, m, n);
    cout << "请输入乘数：";
    while (1) {
        cin >> k;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2048, '\n');
            cout << "请输入合适的整数" << endl;
        }
        else
            break;
    }
    for (int i = 0; i < m * n; i++)
        mat1[i] *= k;  //数乘运算在此
    cout << "运算结果为：" << endl;
    print_mat(mat1, m, n);
    cout << endl;
    wait_for_enter();

    return;
}

void matritrans()
{
    system("cls");
    int m, n;
    initial_mat();
    cout << "<矩阵转置>" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "参与转置的矩阵：";
    input_mat(mat1, m, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat2[i * m + j] = mat1[j * n + i];
        }
    }                     //转置运算在此
        
    cout << "运算结果为：" << endl;
    print_mat(mat2, n, m);
    cout << endl;
    wait_for_enter();

    return;
}

void matrimulti()
{
    system("cls");
    int m, p, n;
    initial_mat();
    cout << "<矩阵乘法>" << endl;
    cout << "该项目要求矩阵1的列数和矩阵2的行数相等" << endl << endl;
    cout << "矩阵1的行列：" << endl;
    input_mn(m, 0);
    input_mn(p, 1);
    cout << "矩阵1：";
    input_mat(mat1, m, p);
    cout << "矩阵2的行数已经确定为 "<<p<<" ,矩阵2的列数:" << endl;
    input_mn(n, 1);
    cout << "矩阵2：";
    input_mat(mat2, p, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < p; k++) {
                mat3[i * m + j] += mat1[p * i + k] * mat2[n * k + j];
            }
        }
    }


    cout << "运算结果为：" << endl;
    print_mat(mat3, m, n);
    cout << endl;
    wait_for_enter();

    return;
}

void hadamulti()
{
    system("cls");
    int m, n;
    initial_mat();
    cout << "<Hadamard乘积>" << endl;
    cout << "该项目要求两个数组行列分别相等" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "矩阵1：";
    input_mat(mat1, m, n);
    cout << "矩阵2：";
    input_mat(mat2, m, n);
    for (int i = 0; i < m * n; i++)
        mat3[i] = mat1[i] * mat2[i];  //加法运算在此
    cout << "运算结果为：" << endl;
    print_mat(mat3, m, n);
    cout << endl;
    wait_for_enter();

    return;
}

void conv_calculate(int* a, int m1, int n1, int* b, int m2, int n2, int* c)//a,b,c分别为输入矩阵，卷积核，结果矩阵
{
    int tmp[100] = { 0 };   //用于存放当前用卷积核覆盖的小矩阵的元素，该大小已足够
    for (int i = 0; i < m1 - m2 + 1; i++) {
        for (int j = 0; j < n1 - n2 + 1; j++) {
            int sum = 0;
            for (int t = 0; t < m2; t++) {
                for (int w = 0; w < n2; w++)
                    tmp[t * n2 + w] = a[(t * n2 + w) + (i * n1) + (m1 - m2) * t + j];//存放当前用卷积核覆盖的小矩阵
            }
            for (int k = 0; k < m2; k++) {
                for (int s = 0; s < n2; s++) {
                    sum = sum + b[k * n2 + s] * tmp[k * n2 + s];
                }    //进行一次hadamard运算
                if (k == m2 - 1)
                    c[i * (n1 - n2 + 1) + j] = sum; //每个位置的运算完成后赋值到结果中
            }
        }
    }
}

void conv()
{
    system("cls");
    int m, n;
    initial_mat();
    cout << "<矩阵卷积>" << endl;
    cout << "该卷积操作的参数为：kernel size = 3，padding = 1，stride = 1，dilation = 1" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "矩阵input：";
    input_mat(mat1, m, n);
    cout << "kernal矩阵是一个固定大小为 3*3 的矩阵" << endl;
    cout << "矩阵kernal：";
    input_mat(mat2, 3, 3);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat0[(i+1) * (n + 2) + j+1] = mat1[i * n + j];
        }
    }
    cout << "扩展后的被卷矩阵为：" << endl;
    print_mat(mat0, m + 2, n + 2);

    wait_for_enter();

    conv_calculate(mat0, m+2, n+2, mat2, 3, 3, mat3);
    cout << "结果为" << endl;
    print_mat(mat3, m, n);


    wait_for_enter();
}

void demo()
{
    // /* 对vs+opencv正确配置后方可使用，此处只给出一段读取并显示图像的参考代码，其余功能流程自行设计和查阅文献 */
    Mat image = imread("D:/images/images/demolena.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original", image);
    cvtColor(image, image, CV_BGR2GRAY);        //更改灰度值，防止最后图像被拉长后只显示一部分
    //waitKey(0);
    initial_mat();
    for (int i = 0; i < 256; i++) {              //转换数组到mat变量
        for (int j = 0; j < 256; j++) {
            mat1[i * 256 + j] = int(image.at<uchar>(i, j));
        }
    }
     
    for (int i = 0; i < 256; i++) {              //扩展一圈0
        for (int j = 0; j < 256; j++) {
            mat0[(i + 1) * (256 + 2) + j + 1] = mat1[i * 256 + j];
        }
    }
    

    initial_mat(1);
    conv_calculate(mat0, 258, 258, B1, 3, 3, mat3);
    //conv2(mat3, mat1, B1, 256, 256);
    for (int i = 0; i < 256 * 256; i++)
        mat3[i] /= 9;
    Mat result1(256, 256, CV_32S, mat3);
    result1.convertTo(result1, 8, 1, 0);
    imshow("Image-result1", result1);

    initial_mat(1);
    conv_calculate(mat0, 258, 258, B2, 3, 3, mat3);
    //conv2(mat3, mat1, B2, 256, 256);
    Mat result2(256, 256, CV_32S, mat3);
    result2.convertTo(result2, 8, 1, 0);
    imshow("Image-result2", result2);
    
    initial_mat(1);
    conv_calculate(mat0, 258, 258, B3, 3, 3, mat3);
    Mat result3(256, 256, CV_32S, mat3);
    result3.convertTo(result3, 8, 1, 0);
    imshow("Image-result3", result3);

    initial_mat(1);
    conv_calculate(mat0, 258, 258, B4, 3, 3, mat3);
    Mat result4(256, 256, CV_32S, mat3);
    result4.convertTo(result4, 8, 1, 0);
    imshow("Image-result4", result4);
    
    initial_mat(1);
    conv_calculate(mat0, 258, 258, B5, 3, 3, mat3);
    Mat result5(256, 256, CV_32S, mat3);
    result5.convertTo(result5, 8, 1, 0);
    imshow("Image-result5", result5);

    initial_mat(1);
    conv_calculate(mat0, 258, 258, B6, 3, 3, mat3);
    for (int i = 0; i < 256 * 256; i++)
        mat3[i] /= 16;
    Mat result6(256, 256, CV_32S, mat3);
    result6.convertTo(result6, 8, 1, 0);
    imshow("Image-result6", result6);
    
    // 提示：Mat格式可与数组相互转换

    if (waitKey(0))
        destroyAllWindows();  //选中窗口后任意按键可以关闭所有图片窗口

    return;
}

int calculate_threshold(int m,int n)
{
    int count[256] = { 0 };
    float pro[256] = { 0 };
    int threshold = 0;
    int i, j = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            count[mat1[i * n + j]]++;
        }
    }                                //count数组下标是像素值，器值表示该像素值的个数
    
    float maxpro = 0;
    int kk = 0;
    for (i = 0; i < 256; i++) {
        pro[i] = float(count[i]) / (m * n);    //pro数组记录下标对应像素值在整个图像中的比例
        if (pro[i] > maxpro) {
            maxpro = pro[i];
            kk = i;
        }
    }

    //遍历灰度
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltatmp, deltamax = 0;
    for (i = 0; i < 256; i++) {   //把i当作阈值
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltatmp = 0;
        for (j = 0; j < 256; j++) {
            if (j <= i) {   //背景部分  
                w0 += pro[j];
                u0tmp += j * pro[j];
            }
            else {   //前景部分  
                w1 += pro[j];
                u1tmp += j * pro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltatmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltatmp > deltamax)
        {
            deltamax = deltatmp;
            threshold = i;
        }
    }

    return threshold;
}


void otsu()
{
    initial_mat();
    Mat image = imread("D:/images/images/demolena.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original2", image);
    cvtColor(image, image, CV_BGR2GRAY);        //更改灰度值，防止最后图像被拉长后只显示一部分
    for (int i = 0; i < 256; i++) {              //转换数组到mat变量
        for (int j = 0; j < 256; j++) {
            mat1[i * 256 + j] = int(image.at<uchar>(i, j));
        }
    }
    int threshold = 0;

    threshold = calculate_threshold(256,256);

    for (int i = 0; i < 256 * 256; i++) {
        if (mat1[i] > threshold)
            mat2[i] = 255;
        else if (mat1[i] <= threshold)
            mat2[i] = 0;
    }
    Mat result_otsu(256, 256, CV_32S, mat2);
    result_otsu.convertTo(result_otsu, 8, 1, 0);
    imshow("Image-result_otsu", result_otsu);

    //雪球图片
    initial_mat();
    image = imread("D:/images/images/snowball.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original3", image);
    cvtColor(image, image, CV_BGR2GRAY);        //更改灰度值，防止最后图像被拉长后只显示一部分
    for (int i = 0; i < 150; i++) {              //转换数组到mat变量
        for (int j = 0; j < 200; j++) {
            mat1[i * 200 + j] = int(image.at<uchar>(i, j));
        }
    }
    
    threshold = calculate_threshold(150, 200);

    for (int i = 0; i < 200 * 150; i++) {
        if (mat1[i] < threshold)
            mat2[i] = 0;
        else
            mat2[i] = mat1[i];
    }
    Mat result_otsu2(150, 200, CV_32S, mat2);
    result_otsu2.convertTo(result_otsu2, 8, 1, 0);
    imshow("Image-result_otsu2", result_otsu2);
    
    
    //多角星形
    image = imread("D:/images/images/polyhedrosis.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original4", image);
    cvtColor(image, image, CV_BGR2GRAY);        //更改灰度值，防止最后图像被拉长后只显示一部分
    for (int i = 0; i < 90; i++) {              //转换数组到mat变量
        for (int j = 0; j < 98; j++) {
            mat1[i * 98 + j] = int(image.at<uchar>(i, j));
        }
    }

    threshold = calculate_threshold(90,98);

    for (int i = 0; i < 90 * 98; i++) {
        if (mat1[i] < threshold)
            mat2[i] = 0;
        else
            mat2[i] = 255;
    }
    Mat result_otsu3(90, 98, CV_32S, mat2);
    result_otsu3.convertTo(result_otsu3, 8, 1, 0);
    imshow("Image-result_otsu3", result_otsu3);


    //船舰
    image = imread("D:/images/images/ship.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original5", image);
    cvtColor(image, image, CV_BGR2GRAY);        //更改灰度值，防止最后图像被拉长后只显示一部分
    for (int i = 0; i < 96; i++) {              //转换数组到mat变量
        for (int j = 0; j < 128; j++) {
            mat1[i * 128 + j] = int(image.at<uchar>(i, j));
        }
    }

    threshold = calculate_threshold(96,128);

    for (int i = 0; i < 96 * 128; i++) {
        if (mat1[i] < threshold)
            mat2[i] = 0;
        else
            mat2[i] = mat1[i];
    }
    Mat result_otsu4(96, 128, CV_32S, mat2);
    result_otsu4.convertTo(result_otsu4, 8, 1, 0);
    imshow("Image-result_otsu4", result_otsu4);


    //脑部影像截取
    image = imread("D:/images/images/brain.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    imshow("Image-original6", image);
    cvtColor(image, image, CV_BGR2GRAY);        //更改灰度值，防止最后图像被拉长后只显示一部分
    for (int i = 0; i < 78; i++) {              //转换数组到mat变量
        for (int j = 0; j < 119; j++) {
            mat1[i * 119 + j] = int(image.at<uchar>(i, j));
        }
    }

    threshold = calculate_threshold(78,119);

    for (int i = 0; i < 78 * 119; i++) {
        if (mat1[i] > threshold)
            mat2[i] = 255;
        else if (mat1[i] <= threshold)
            mat2[i] = 0;
    }
    Mat result_otsu5(78, 119, CV_32S, mat2);
    result_otsu5.convertTo(result_otsu5, 8, 1, 0);
    imshow("Image-result_otsu5", result_otsu5);

    
    if (waitKey(0))
        destroyAllWindows();  //选中窗口后任意按键可以关闭所有图片窗口

    return;
}

int main()
{
    char choice, ch;

    wait_for_enter();
    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数

        menu(); // 调用菜单显示函数，自行补充完成

        choice = _getche();

        if (choice == '0') {
            cout << "\n 确定退出吗?(输入Y或y后按回车即退出)" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice) {
        case '1':
            matriplus();
            break;
        case '2':
            nummulti();
            break;
        case '3':
            matritrans();
            break;
        case '4':
            matrimulti();
            break;
        case '5':
            hadamulti();
            break;
        case '6':
            conv();
            break;
        case '7':
            demo();
            break;
        case '8':
            otsu();
            break;
        default:
            cout << "\n 输入错误，请从新输入" << endl;
            wait_for_enter();
        }
    }
    return 0;
}