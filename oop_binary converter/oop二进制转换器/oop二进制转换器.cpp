#include <iostream>
using namespace std;


void itobs(int num, char* buffer) {
    /* 将整数转换为二进制并存入 buffer 字符串 */
    /* 例：1964 的二进制是：00000000 00000000 00000111 10101100 */
    cout << num << " 的二进制是: ";
    unsigned int cmp = 1;
    int tmp = 0;
    cmp = cmp << 31;         //cmp用于比较每一位是否是1，先将其放在首位
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
    cout << "输入一些整数：" << endl;
    while (1) {
        cin >> num;
        if (cin.fail())
            break;
        else
            itobs(num, buffer);
    }

    return 0;
}