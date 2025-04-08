#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, int> table;

void block(string& tmp, string content, int i) //�趨���������ַ�������lz4�е�4
{
    char* ch = &content[i];
    for (int j = 0; j < 4; j++)
        *(ch + j) = content[i + j];
    *(ch + 4) = '\0';
    tmp = ch;
    return;
}

int cal_match_length(string content,int i, int start, int length)  //���ַ��Ƚϵõ�ƥ��ĳ���
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

void code(ofstream& fout1, string content)  //����lz4��������������ѹ���ļ���
{
    table.clear();
    int i0 = 0;      //��һ��ָ��λ��
    int offset = 0;  //ƫ����
    string literal;  //�м��������ַ���

    string tmp;
    //int sign = 0;
    int i = 0;  //�ڶ���ָ��λ��
    while (i < content.size() - 3) {   //���㷨���������λ�޷������
        block(tmp, content, i);
       /* if (sign == 0) {
            cout << tmp << endl;
            sign++;
        }
       */
        if (table.find(tmp) != table.end()) {
            int match_length = 4;   //ƥ���ַ����ȣ�������4λ
            int first_char = table[tmp];  //��һ��ƥ���ַ���λ��
            offset = i - first_char;
            match_length = cal_match_length(content, i, first_char, match_length);
            literal = "0";  //���ʾNULL��û�������κ��ַ�
            if (i - i0 > 0) {
                literal = content.substr(i0, i - i0);
            }

            fout1 << i - i0 << '-' << literal << '-' << match_length << '-' << offset << '=';  //���ڽ�ѹ���������ʽ
            
            i0 += (match_length + i - i0);
            i = i + match_length;
        }
        else {  //����¼�ֵ��
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

    ifstream fin(argv[1], ios::binary); // �Զ����Ʒ�ʽ���ļ�
    if (!fin) {
        cerr << "Can not open the input file!" << endl; // ���������Ϣ���˳�
        return -1;
    }

    ofstream fout1(argv[2], ios::binary); // ������ļ�
    if (!fout1) {
        cerr << "Can not open the output file!" << endl;
        return -1;
    }
    //ÿ4kb��ȡһ��

    vector<char> buffer(4096);
    //char buffer[maxsize];
    while (fin.read(buffer.data(), 4096)) {
        code(fout1, buffer.data());
        buffer.clear();
        buffer.resize(4096);
    }

    //�������ʣ�µ��ı�
    int last = fin.gcount();
    if (last > 0) {
        code(fout1, buffer.data());
    }

    /*    istreambuf_iterator<char> beg(fin),
            end; // ���������ļ�ָ�룬ָ��ʼ�ͽ������� char(һ�ֽ�) Ϊ����
        string content(beg, end); // ���ļ�ȫ������ string �ַ���
    */

    fin.close(); // �������ļ���ر��ļ������һ����ϰ��

    


   
    
    fout1.close();

    
    cout << "Complete!" << endl;
    return 0;
}