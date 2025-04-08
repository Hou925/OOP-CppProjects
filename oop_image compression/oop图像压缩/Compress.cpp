#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include "PicReader.h"
#include <sstream>
#include <unordered_map>
#include <bitset>
using namespace std;

//先定义一些资料中需要用到的全局变量

const int zigzag_mat[64] = {                  //zigzag处理需要的表格
	0, 1, 5, 6, 14, 15, 27, 28,
	2, 4, 7, 13, 16, 26, 29, 42,
	3, 8, 12, 17, 25, 30, 41, 43,
	9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 51, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63
};

const int Qy[8][8] = {                     //标准亮度量化表
	16, 11, 10, 16, 24, 40, 51, 61,
	12, 12, 14, 19, 26, 58, 60, 55,
	14, 13, 16, 24, 40, 57, 69, 56,
	14, 17, 22, 29, 51, 87, 80, 62,
	18, 22, 37, 56, 68, 109, 103, 77,
	24, 35, 55, 64, 81, 104, 113, 92,
	49, 64, 78, 87, 103, 121, 120, 101,
	72, 92, 95, 98, 112, 100, 103, 99, };

const int Qc[8][8] = {                     //标准色差量化表
	17, 18, 24, 47, 99, 99, 99, 99,
	18, 21, 26, 66, 99, 99, 99, 99,
	24, 26, 56, 99, 99, 99, 99, 99,
	47, 66, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
};

//-------------------------------------------------------------------------------
const char Standard_DC_Luminance_NRCodes[] = { 0, 0, 7, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
const unsigned char Standard_DC_Luminance_Values[] = { 4, 5, 3, 2, 6, 1, 0, 7, 8, 9, 10, 11 };

//-------------------------------------------------------------------------------
const char Standard_DC_Chrominance_NRCodes[] = { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
const unsigned char Standard_DC_Chrominance_Values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

//-------------------------------------------------------------------------------
const char Standard_AC_Luminance_NRCodes[] = { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d };
const unsigned char Standard_AC_Luminance_Values[] =
{
	0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
	0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
	0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
	0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
	0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
	0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
	0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
	0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
	0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
	0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
	0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
	0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
	0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
	0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
	0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
	0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};

//-------------------------------------------------------------------------------
const char Standard_AC_Chrominance_NRCodes[] = { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 };
const unsigned char Standard_AC_Chrominance_Values[] =
{
	0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
	0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
	0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
	0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
	0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
	0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
	0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
	0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
	0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
	0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
	0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
	0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
	0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
	0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
	0xf9, 0xfa
};



//压缩操作类

class Compress
{
private:
	struct block {
		double Y[8][8], Cb[8][8], Cr[8][8];
		struct block* next;
	}*head = nullptr;
	UINT x = 0, y = 0; //图片尺寸
	
	//哈夫曼表优先队列
	
	unordered_map<unsigned char, string>m_Y_DC_Huffman_Table;
	unordered_map<unsigned char, string>m_Y_AC_Huffman_Table;

	unordered_map<unsigned char, string>m_CbCr_DC_Huffman_Table;
	unordered_map<unsigned char, string>m_CbCr_AC_Huffman_Table;
	
	//编码过程用变量，leftstr为哈夫曼二进制每8位转化后的剩余二进制码
	string leftstr;
	int lastone[3] = { 0 };

public:
	void blocking(const char*);
    void read(const char*);
	void compress(const char*);
	void dct(double mat[8][8]);
	void quantify(double mat[8][8], int*, int);
	double alpha(int);
	void zigzag(int*);
	int binaryLength(int);
	void Huffman_Code(const char*, const unsigned char*);
	void Init_Huffman_Code();
	void Code(int*, int, int,ofstream&);
	void coding_print(ofstream& fout);
	//void write_byte(unsigned char, FILE*);
	//void write_word(unsigned short, FILE*);
	//void write(const void*, int, FILE*);
	//void write_header(FILE*,int,int);

	void print_header(ofstream &, int, int);
};


//写表头
void Compress::print_header(ofstream &fout, int height, int width)
{
	//SOI
	fout << char(0xff) << char(0xd8);
	fout << char(0xff) << char(0xe0) << char(0x00) << char(0x10);
	fout << char(0x4a) << char(0x46) << char(0x49) << char(0x46) << char(0x00);
	fout << char(0x01) << char(0x02);
	fout << char(0x00) << char(0x00) << char(0x01) << char(0x00)<<char(0x01);
	fout << char(0x00) << char(0x00);

	//DQT
	fout << char(0xff) << char(0xdb);
	fout << char(0x00) << char(0x84);
	//量化表Qy
	fout << char(0x00);
	int tmp[64], tmp1[64];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			tmp[i * 8 + j] = Qy[i][j];
	for (int i = 0; i < 64; i++)
		tmp1[zigzag_mat[i]] = tmp[i];
	for(int i=0;i<64;i++)
		fout << char(tmp1[i]);
	//量化表Qc
	fout << char(0x01);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			tmp[i * 8 + j] = Qc[i][j];
	for (int i = 0; i < 64; i++)
		tmp1[zigzag_mat[i]] = tmp[i];
	for (int i = 0; i < 64; i++)
		fout << char(tmp1[i]);
	//SOFO
	fout << char(0xff) << char(0xc0);
	fout << char(0x00) << char(0x11);
	fout << char(0x08);
	fout << char(height >> 8) << char(height & 15) << char(width >> 8) << char(width & 15);
	fout << char(0x03);
	fout << char(0x01) << char(0x11) << char(0x00);
	fout << char(0x02) << char(0x11) << char(0x01);
	fout << char(0x03) << char(0x11) << char(0x01);

	//DHT
	fout << char(0xff) << char(0xc4) << char(0x01) << char(0xa2);
	fout << char(0x00);
	for (int i = 0; i < 16; i++)
		fout<<char(Standard_DC_Luminance_NRCodes[i]);
	for (int i = 0; i < 12; i++)
		fout << char(Standard_DC_Luminance_Values[i]);
	fout << char(0x10);
	for (int i = 0; i < 16; i++)
		fout << char(Standard_AC_Luminance_NRCodes[i]);
	for (int i = 0; i < 162; i++)
		fout << char(Standard_AC_Luminance_Values[i]);
	fout << char(0x01);
	for (int i = 0; i < 16; i++)
		fout << char(Standard_DC_Chrominance_NRCodes[i]);
	for (int i = 0; i < 12; i++)
		fout << char(Standard_DC_Chrominance_Values[i]);
	fout << char(0x11);
	for (int i = 0; i < 16; i++)
		fout << char(Standard_AC_Chrominance_NRCodes[i]);
	for (int i = 0; i < 162; i++)
		fout << char(Standard_AC_Chrominance_Values[i]);

	//SOS
	fout << char(0xff) << char(0xda);
	fout << char(0x00) << char(0x0c);
	fout << char(0x03) << char(0x01) << char(0x00) << char(0x02) << char(0x11) << char(0x03) << char(0x11);
	fout << char(0x00) << char(0x3f) << char(0x00);

	return;
}


void Compress::read(const char* filename)
{
	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;
	imread.readPic(filename);
	imread.getData(data, x, y);

	printf("show lena, press enter to continue...");
	(void)getchar();

	imread.showPic(data, x, y);

	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();
}

void Compress::blocking(const char* filename)   //将矩阵分为8*8的小块
{
	//提取图片信息
	PicReader imread;
	BYTE* data = nullptr;
	UINT x0, y0;
	imread.readPic(filename);
	imread.getData(data, x0, y0);
	x = x0;
	y = y0;
	head = new(nothrow) block;
	if (head == NULL)
		exit(0);

	head->next = nullptr;
	block* q = head; //辅助指针

	for (int i = 0; i < x0; i += 8)
		for (int j = 0; j < y0; j += 8) {
			block* p = new(nothrow) block;
			if (p == NULL)
				exit(0);
			q->next = p;

			//RGB->YCbCr
			for (int i0 = i; i0 < i + 8; i0++)
				for (int j0 = j; j0 < j + 8; j0++) {
					int cur = (i0 * y0 + j0) * 4;
					p->Y[i0 - i][j0 - j] = 0.29871 * data[cur] + 0.58661 * data[cur + 1] + 0.11448 * data[cur + 2] - 128;
					p->Cb[i0 - i][j0 - j] = -0.16874 * data[cur] - 0.33126 * data[cur + 1] + 0.50000 * data[cur + 2];
					p->Cr[i0 - i][j0 - j] = 0.50000 * data[cur] - 0.41869 * data[cur + 1] - 0.08131 * data[cur + 2];
				}
			p->next = NULL;
			q = p;
		}
	
	delete[] data;

}

double Compress::alpha(int u) {
	if (u == 0)
		return 1.000 / sqrt(8);
	return 0.500;
}

//离散余弦变换操作，取系数 F(u, v)
void Compress::dct(double mat[8][8])
{
	double F[8][8];
    //初始化
	for (int u = 0; u < 8; u++) {
		for (int v = 0; v < 8; v++)
			F[u][v] = 0;
	}
	//dct公式
	for (int u = 0; u < 8; u++) {
		for (int v = 0; v < 8; v++) {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					F[u][v] += mat[x][y] * cos(double(2 * x + 1) / 16 * u * M_PI) * cos(double(2 * y + 1) / 16 * v * M_PI);
				}
			}
			F[u][v] *= alpha(u) * alpha(v);
		}
	}
	//结果存储回mat中
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			mat[i][j] = F[i][j];
		}
	}

	return;
}

//量化操作
void Compress::quantify(double mat[8][8], int* Arry, int select)
{
	if (select == 1) {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				Arry[i * 8 + j] = round(mat[i][j] / Qy[i][j]);      // 亮度量化
	}
	if (select == 2) {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				Arry[i * 8 + j] = round(mat[i][j] / Qc[i][j]);      // 色差量化
	}

	return;
}

//zigzag处理，将矩阵信息变成一维，且0全部靠后
void Compress::zigzag(int* Arry)
{
	int New_Arry[64];
	for (int i = 0; i < 64; i++)
		New_Arry[zigzag_mat[i]] = Arry[i];

	//需要将数据放回原矩阵中
	for (int i = 0; i < 64; i++)
		Arry[i] = New_Arry[i];
	return;
}

//计算整数的二进制位数，用于辅助bit编码
int Compress::binaryLength(int n) {
	int length = 0;
	int n0 = n;
	if (n < 0)
		n0 = -n;
	while (n0 != 0) {
		length++;
		n0 >>= 1;  // 右移一位  
	}
	return length;
}


//编写四个哈夫曼表（两个dc，两个ac）
void Compress::Huffman_Code(const char* NRCodes, const unsigned char* Values) {
	int code = 0;
	const unsigned char* p = Values;
	for (int i = 0; i < 16; i++) {
		char num = NRCodes[i];
		for (int j = 0; j < num; j++) {
			//unsigned char value = *p;
			string str;
			bitset<50>bit(code);
			for (int k = i; k >= 0; k--) {
				if (bit[k] == 0)
					str += '0';
				if (bit[k] == 1)
					str += '1';
			}
			if (NRCodes == Standard_DC_Luminance_NRCodes) {
				m_Y_DC_Huffman_Table[*p] = str;
			}
			else if (NRCodes == Standard_AC_Luminance_NRCodes) {
				m_Y_AC_Huffman_Table[*p] = str;
			}
			else if (NRCodes == Standard_DC_Chrominance_NRCodes) {
				m_CbCr_DC_Huffman_Table[*p] = str;
			}
			else if (NRCodes == Standard_AC_Chrominance_NRCodes) {
				m_CbCr_AC_Huffman_Table[*p] = str;
			}
				
			code++;
			p++;
		}
		code <<= 1;
	}
}

//整合四个哈夫曼表
void Compress::Init_Huffman_Code() {
	Huffman_Code(Standard_DC_Luminance_NRCodes, Standard_DC_Luminance_Values);
	Huffman_Code(Standard_AC_Luminance_NRCodes, Standard_AC_Luminance_Values);
	Huffman_Code(Standard_DC_Chrominance_NRCodes, Standard_DC_Chrominance_Values);
	Huffman_Code(Standard_AC_Chrominance_NRCodes, Standard_AC_Chrominance_Values);
}



//编码
void Compress::Code(int* tmp, int type, int num,ofstream& fout)
{
	//DC处理
	int tmp0 = tmp[0];
	tmp[0] -= lastone[num];
	lastone[num] = tmp0;
	

	//先找到最后有几个0，存储个数
	int zero_final = 0; 
	for (int i = 63; i > 0; i--) {
		if (tmp[i] == 0)
			zero_final++;
		else
			break;
	}

	int zero_num = 0;
	bool ac_sign = 0;  //判断当前操作dc还是ac
	string str = leftstr;
	for (int i = 0; i < 64 - zero_final; i++) {
		//rle编码
		if (tmp[i] != 0 || zero_num == 15 || i == 0) {
			int flag = 0;
			if (tmp[i] < 0) {
				flag = 1;
				tmp[i] *= -1;
			}
				
			//对非0数字进行bit编码
			int len = binaryLength(tmp[i]);
			bitset<40>bit(tmp[i]);

			//哈夫曼编码0的部分
			if (type == 1) {
				if (ac_sign == 0)
					str += m_Y_DC_Huffman_Table[zero_num * 16 + len];
				else if (ac_sign==1)
					str += m_Y_AC_Huffman_Table[zero_num * 16 + len];
			}
			else if (type == 2) {
				if (ac_sign == 0)
					str += m_CbCr_DC_Huffman_Table[zero_num * 16 + len];
				else if (ac_sign == 1)
					str += m_CbCr_AC_Huffman_Table[zero_num * 16 + len];
			}
			//哈夫曼编码非0的部分
			for (int i = len - 1; i >= 0; i--)
				if (bit[i]==flag)   //负数的时候输出反码
					str += '0';
				else 
					str += '1';
			zero_num = 0;
		}
		else
			zero_num++;
		ac_sign = 1;
	}

	//eob部分，即最后的0，y和cbcr是不同的
	if (zero_final != 0) {
		if (type==1)
			str += m_Y_AC_Huffman_Table[0];
		else if (type==2)
			str += m_CbCr_AC_Huffman_Table[0];
	}
	
	//哈夫曼二进制编码转化成字符输出
	int cur = 0;
	while (str.length() > cur + 7) {
		bitset<8>bit(str.substr(cur, 8));
		cur += 8;
		unsigned char c = bit.to_ullong();
		fout << c;
		if (c == 0xff)
			fout << char(0x00);
	}

	leftstr = str.substr(cur, str.length() - cur);
}


void Compress::coding_print(ofstream& fout) {
	//图像编码信息
	block* p = head;
	while (p->next != NULL) {
		p = p->next;
		dct(p->Y);
		int tmp[64];
		quantify(p->Y, tmp, 1);
		zigzag(tmp);
		Code(tmp, 1, 0,fout);

		dct(p->Cb);
		quantify(p->Cb, tmp, 2);
		zigzag(tmp);
		Code(tmp, 2, 1,fout);

		dct(p->Cr);
		quantify(p->Cr, tmp, 2);
		zigzag(tmp);
		Code(tmp, 2, 2,fout);
	}
	if (leftstr.length()) {
		int addzero = (8 - leftstr.length() % 8) % 8;
		for (int i = 0; i < addzero; i++)
			leftstr = leftstr + '0';
		bitset<8>bit(leftstr);
		unsigned char c = bit.to_ulong();
		fout << c;
		if (c == 0xff)
			fout << char(0x00);
	}

	//EOI
	fout << char(0xff) << char(0xd9);
}


//综合所有方法实现压缩
void Compress::compress(const char* filename)
{
	blocking(filename);
	Init_Huffman_Code();

	ofstream fout("lena.jpg", ios::binary);
	if (!fout) {
		cout << "File opening ERROR!" << endl;
		exit(0);
	}
	print_header(fout, x, y);
	coding_print(fout);
		
	fout.close();

}




int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }
	
    if (strcmp(argv[1], "-compress") && strcmp(argv[1], "-read")) {
        cerr << "Unknown parameter!\nCommand list:\ncompress\nread" << endl;
        return -1;
    }

	Compress compress_pic;

    if (strcmp(argv[1], "-read")==0) {
		compress_pic.read(argv[2]);
		cout << "Reading mission Complete!" << endl;
    }
	else if (strcmp(argv[1], "-compress")==0) {
		compress_pic.compress(argv[2]);
		cout << "Compressing misssion complete!" << endl;
	}
	else {
		cout << "Illegal Command!" << endl;
	}

	
	return 0;

}

