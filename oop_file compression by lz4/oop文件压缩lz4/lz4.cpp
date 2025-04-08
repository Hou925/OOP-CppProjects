#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, int> table;

void block(string& tmp, string content, int i) //设定检索区域字符串，即lz4中的4
{
    char* ch = &content[i];
    for (int j = 0; j < 4; j++)
        *(ch + j) = content[i + j];
    *(ch + 4) = '\0';
    tmp = ch;
    return;
}

int cal_match_length(string content,int i, int start, int length)  //逐字符比较得到匹配的长度
{
    int length0 = length;
    while (i + length0 < content.size()) {   
        if (content[start + length0] != content[i + length0]) {
            break;
        }
        length0++;
    }
    return length0;
}

void code(ofstream& fout1, string content)  //进行lz4编码操作并输出到压缩文件中
{
    table.clear();
    int i0 = 0;      //第一个指针位置
    int offset = 0;  //偏移量
    string literal;  //中间跳过的字符串

    string tmp;
    //int sign = 0;
    int i = 0;  //第二个指针位置
    while (i < content.size() - 3) {   //该算法导致最后三位无法被检查
        block(tmp, content, i);
       /* if (sign == 0) {
            cout << tmp << endl;
            sign++;
        }
       */
        if (table.find(tmp) != table.end()) {
            int match_length = 4;   //匹配字符长度，至少是4位
            int first_char = table[tmp];  //第一个匹配字符的位置
            offset = i - first_char;
            match_length = cal_match_length(content, i, first_char, match_length);
            literal = "0";  //零表示NULL，没有跳过任何字符
            if (i - i0 > 0) {
                literal = content.substr(i0, i - i0);
            }

            fout1 << i - i0 << '-' << literal << '-' << match_length << '-' << offset << '=';  //便于解压缩的输出方式
            
            i0 += (match_length + i - i0);
            i = i + match_length;
        }
        else {  //添加新键值对
            table[tmp] = i;
            i++;
        }

    }
    return;
}


int main(int argc, char* argv[]) {
    cout << "Zipper 0.001! Author: root" << endl;
    if (argc != 4) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }

    if (strcmp(argv[3], "zip")/* && strcmp(argv[3], "unzip")*/) {
        cerr << "Unknown parameter!\nCommand list:\nzip" << endl;
        return -1;
    }

    ifstream fin(argv[1], ios::binary); // 以二进制方式打开文件
    if (!fin) {
        cerr << "Can not open the input file!" << endl; // 输出错误信息并退出
        return -1;
    }

    ofstream fout1(argv[2], ios::binary); // 打开输出文件
    if (!fout1) {
        cerr << "Can not open the output file!" << endl;
        return -1;
    }
    //每4kb读取一次

    vector<char> buffer(4096);
    //char buffer[maxsize];
    while (fin.read(buffer.data(), 4096)) {
        code(fout1, buffer.data());
        buffer.clear();
        buffer.resize(4096);
    }

    //处理最后剩下的文本
    int last = fin.gcount();
    if (last > 0) {
        code(fout1, buffer.data());
    }

    /*    istreambuf_iterator<char> beg(fin),
            end; // 设置两个文件指针，指向开始和结束，以 char(一字节) 为步长
        string content(beg, end); // 将文件全部读入 string 字符串
    */

    fin.close(); // 操作完文件后关闭文件句柄是一个好习惯

    


   
    
    fout1.close();

    
    cout << "Complete!" << endl;
    return 0;
}