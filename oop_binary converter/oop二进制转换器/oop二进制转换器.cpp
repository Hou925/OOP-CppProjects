#include <iostream>
using namespace std;


void itobs(int num, char* buffer) {
    /* ������ת��Ϊ�����Ʋ����� buffer �ַ��� */
    /* ����1964 �Ķ������ǣ�00000000 00000000 00000111 10101100 */
    cout << num << " �Ķ�������: ";
    unsigned int cmp = 1;
    int tmp = 0;
    cmp = cmp << 31;         //cmp���ڱȽ�ÿһλ�Ƿ���1���Ƚ��������λ
    for (int i = 0; i < 32; i++) {
        tmp = ((cmp & num) == cmp);
        buffer[i] = char(tmp + 48);
        cmp = cmp >> 1;
        cout << buffer[i];
    }
    cout << endl;
    return;
}

int main()
{
    int num;
    char buffer[32];
    cout << "����һЩ������" << endl;
    while (1) {
        cin >> num;
        if (cin.fail())
            break;
        else
            itobs(num, buffer);
    }

    return 0;
}