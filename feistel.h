#ifndef FEISTEL_H
#define FEISTEL_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define FIRSTBIT 0x8000000000000000  // 1000000000...
#define DATA_SIZE sizeof(uint64_t)

// Feistel F function 使用的 置換表
// row 1前5個值是48763(星爆氣流斬)
// col 1(idx=0,8,16...)的前五個值是學號410612011
static int Pbox[64] = {4, 8, 7, 6, 3, 14, 16, 12,
                       10, 40, 51, 57, 59, 60, 29, 42,
                       61, 2, 15, 1, 25, 31, 0, 22,
                       20, 54, 50, 48, 58, 55, 18, 36,
                       11, 9, 13, 26, 24, 30, 35, 43,
                       63, 33, 46, 32, 56, 62, 41, 53,
                       49, 23, 19, 17, 27, 21, 28, 5,
                       44, 39, 38, 45, 34, 47, 52, 37};

void print(vector<uint64_t>& v);
void print(vector<uint8_t>& v);

void addbit(uint64_t* block, uint64_t from, int position_from, int position_to);
void reverse(uint64_t* x);
void highLowChange(uint64_t* val);

uint64_t F(uint64_t val);
void doFeistel(vector<uint64_t>& before, vector<uint64_t>& after);

void str2Byte(string str, vector<uint8_t>& byte);
void byte2Data(vector<uint8_t>& byte, vector<uint64_t>& data);
void data2Byte(vector<uint64_t>& data, vector<uint8_t>& byte);

void addPadding(vector<uint8_t>& byte);
void removePadding(vector<uint8_t>& byte);

#endif