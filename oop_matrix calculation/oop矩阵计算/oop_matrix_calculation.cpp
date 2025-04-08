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
        << "���س�������";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

void menu()
{
    cout << "*********************************************************" << endl;
    cout << " *      1 ����ӷ�      2 ��������      3 ����ת��      *" << endl;
    cout << " *      4 ����˷�      5 Hadamard�˻�  6 ������      *" << endl;
    cout << " *      7 ���Ӧ��      8 Otsu�㷨      0 �˳�ϵͳ      *" << endl;
    cout << "*********************************************************" << endl;
    cout << "ѡ��˵���<0~8>��" << endl;
    return;
}

void initial_mat(int sign = 0)  //�����ʼ��
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

void input_mn(int& m,int k)  //�������У����ݲ���k����
{
    if (k == 0)
        cout << "�������������" << endl;
    else
        cout << "�������������" << endl;
    while (1) {
        cin >> m;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2048, '\n');
        }
        else if (m > 0 && m < 256)
            break;
        cout << "��������Խ�磬����������" << endl;
    }

    return;
}

void input_mat(int* mat, int m, int n)   //�������Ԫ��
{
    cout << "����������Ԫ��" << endl;
    for (int i = 0; i < m * n; i++) {
        while (1) {
            cin >> mat[i];
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2048, '\n');
                cout << "��������ʵ�����" << endl;
            }
            else
                break;
        }
    }

    return;
}

void print_mat(int* mat, int m, int n) //����8λ�Ŀ�ȴ�ӡ����
{
    for (int i = 0; i < m*n; i++) {
        cout << setw(8) << mat[i];
        if ((i+1) % n == 0)
            cout << endl;
    }
    return;
}

void matriplus()   //�ӷ�
{
    system("cls");
    int m, n;
    initial_mat();
    cout << "<����ӷ�>" << endl;
    cout << "����ĿҪ�������������зֱ����" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "����1��";
    input_mat(mat1, m, n);
    cout << "����2��";
    input_mat(mat2, m, n);
    for (int i = 0; i < m * n; i++)
        mat3[i] = mat1[i] + mat2[i];  //�ӷ������ڴ�
    cout << "������Ϊ��" << endl;
    print_mat(mat3, m, n);
    cout << endl;
    wait_for_enter();

    return;
}

void nummulti()
{
    system("cls");
    int m, n, k;  //k�ǳ���
    initial_mat();
    cout << "<��������>" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "�������˵ľ���";
    input_mat(mat1, m, n);
    cout << "�����������";
    while (1) {
        cin >> k;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(2048, '\n');
            cout << "��������ʵ�����" << endl;
        }
        else
            break;
    }
    for (int i = 0; i < m * n; i++)
        mat1[i] *= k;  //���������ڴ�
    cout << "������Ϊ��" << endl;
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
    cout << "<����ת��>" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "����ת�õľ���";
    input_mat(mat1, m, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat2[i * m + j] = mat1[j * n + i];
        }
    }                     //ת�������ڴ�
        
    cout << "������Ϊ��" << endl;
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
    cout << "<����˷�>" << endl;
    cout << "����ĿҪ�����1�������;���2���������" << endl << endl;
    cout << "����1�����У�" << endl;
    input_mn(m, 0);
    input_mn(p, 1);
    cout << "����1��";
    input_mat(mat1, m, p);
    cout << "����2�������Ѿ�ȷ��Ϊ "<<p<<" ,����2������:" << endl;
    input_mn(n, 1);
    cout << "����2��";
    input_mat(mat2, p, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < p; k++) {
                mat3[i * m + j] += mat1[p * i + k] * mat2[n * k + j];
            }
        }
    }


    cout << "������Ϊ��" << endl;
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
    cout << "<Hadamard�˻�>" << endl;
    cout << "����ĿҪ�������������зֱ����" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "����1��";
    input_mat(mat1, m, n);
    cout << "����2��";
    input_mat(mat2, m, n);
    for (int i = 0; i < m * n; i++)
        mat3[i] = mat1[i] * mat2[i];  //�ӷ������ڴ�
    cout << "������Ϊ��" << endl;
    print_mat(mat3, m, n);
    cout << endl;
    wait_for_enter();

    return;
}

void conv_calculate(int* a, int m1, int n1, int* b, int m2, int n2, int* c)//a,b,c�ֱ�Ϊ������󣬾���ˣ��������
{
    int tmp[100] = { 0 };   //���ڴ�ŵ�ǰ�þ���˸��ǵ�С�����Ԫ�أ��ô�С���㹻
    for (int i = 0; i < m1 - m2 + 1; i++) {
        for (int j = 0; j < n1 - n2 + 1; j++) {
            int sum = 0;
            for (int t = 0; t < m2; t++) {
                for (int w = 0; w < n2; w++)
                    tmp[t * n2 + w] = a[(t * n2 + w) + (i * n1) + (m1 - m2) * t + j];//��ŵ�ǰ�þ���˸��ǵ�С����
            }
            for (int k = 0; k < m2; k++) {
                for (int s = 0; s < n2; s++) {
                    sum = sum + b[k * n2 + s] * tmp[k * n2 + s];
                }    //����һ��hadamard����
                if (k == m2 - 1)
                    c[i * (n1 - n2 + 1) + j] = sum; //ÿ��λ�õ�������ɺ�ֵ�������
            }
        }
    }
}

void conv()
{
    system("cls");
    int m, n;
    initial_mat();
    cout << "<������>" << endl;
    cout << "�þ�������Ĳ���Ϊ��kernel size = 3��padding = 1��stride = 1��dilation = 1" << endl;
    input_mn(m, 0);
    input_mn(n, 1);
    cout << "����input��";
    input_mat(mat1, m, n);
    cout << "kernal������һ���̶���СΪ 3*3 �ľ���" << endl;
    cout << "����kernal��";
    input_mat(mat2, 3, 3);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat0[(i+1) * (n + 2) + j+1] = mat1[i * n + j];
        }
    }
    cout << "��չ��ı������Ϊ��" << endl;
    print_mat(mat0, m + 2, n + 2);

    wait_for_enter();

    conv_calculate(mat0, m+2, n+2, mat2, 3, 3, mat3);
    cout << "���Ϊ" << endl;
    print_mat(mat3, m, n);


    wait_for_enter();
}

void demo()
{
    // /* ��vs+opencv��ȷ���ú󷽿�ʹ�ã��˴�ֻ����һ�ζ�ȡ����ʾͼ��Ĳο����룬���๦������������ƺͲ������� */
    Mat image = imread("D:/images/images/demolena.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original", image);
    cvtColor(image, image, CV_BGR2GRAY);        //���ĻҶ�ֵ����ֹ���ͼ��������ֻ��ʾһ����
    //waitKey(0);
    initial_mat();
    for (int i = 0; i < 256; i++) {              //ת�����鵽mat����
        for (int j = 0; j < 256; j++) {
            mat1[i * 256 + j] = int(image.at<uchar>(i, j));
        }
    }
     
    for (int i = 0; i < 256; i++) {              //��չһȦ0
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
    
    // ��ʾ��Mat��ʽ���������໥ת��

    if (waitKey(0))
        destroyAllWindows();  //ѡ�д��ں����ⰴ�����Թر�����ͼƬ����

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
    }                                //count�����±�������ֵ����ֵ��ʾ������ֵ�ĸ���
    
    float maxpro = 0;
    int kk = 0;
    for (i = 0; i < 256; i++) {
        pro[i] = float(count[i]) / (m * n);    //pro�����¼�±��Ӧ����ֵ������ͼ���еı���
        if (pro[i] > maxpro) {
            maxpro = pro[i];
            kk = i;
        }
    }

    //�����Ҷ�
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltatmp, deltamax = 0;
    for (i = 0; i < 256; i++) {   //��i������ֵ
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltatmp = 0;
        for (j = 0; j < 256; j++) {
            if (j <= i) {   //��������  
                w0 += pro[j];
                u0tmp += j * pro[j];
            }
            else {   //ǰ������  
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
    Mat image = imread("D:/images/images/demolena.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original2", image);
    cvtColor(image, image, CV_BGR2GRAY);        //���ĻҶ�ֵ����ֹ���ͼ��������ֻ��ʾһ����
    for (int i = 0; i < 256; i++) {              //ת�����鵽mat����
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

    //ѩ��ͼƬ
    initial_mat();
    image = imread("D:/images/images/snowball.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original3", image);
    cvtColor(image, image, CV_BGR2GRAY);        //���ĻҶ�ֵ����ֹ���ͼ��������ֻ��ʾһ����
    for (int i = 0; i < 150; i++) {              //ת�����鵽mat����
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
    
    
    //�������
    image = imread("D:/images/images/polyhedrosis.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original4", image);
    cvtColor(image, image, CV_BGR2GRAY);        //���ĻҶ�ֵ����ֹ���ͼ��������ֻ��ʾһ����
    for (int i = 0; i < 90; i++) {              //ת�����鵽mat����
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


    //����
    image = imread("D:/images/images/ship.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original5", image);
    cvtColor(image, image, CV_BGR2GRAY);        //���ĻҶ�ֵ����ֹ���ͼ��������ֻ��ʾһ����
    for (int i = 0; i < 96; i++) {              //ת�����鵽mat����
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


    //�Բ�Ӱ���ȡ
    image = imread("D:/images/images/brain.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original6", image);
    cvtColor(image, image, CV_BGR2GRAY);        //���ĻҶ�ֵ����ֹ���ͼ��������ֻ��ʾһ����
    for (int i = 0; i < 78; i++) {              //ת�����鵽mat����
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
        destroyAllWindows();  //ѡ�д��ں����ⰴ�����Թر�����ͼƬ����

    return;
}

int main()
{
    char choice, ch;

    wait_for_enter();
    while (true) // ע���ѭ���˳�������
    {
        system("cls"); // ��������

        menu(); // ���ò˵���ʾ���������в������

        choice = _getche();

        if (choice == '0') {
            cout << "\n ȷ���˳���?(����Y��y�󰴻س����˳�)" << endl;
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
            cout << "\n ����������������" << endl;
            wait_for_enter();
        }
    }
    return 0;
}