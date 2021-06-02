#ifndef FEISTEL_H
#define FEISTEL_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define FIRSTBIT 0x80000000  // 1000000000...
typedef uint32_t DATA;
#define DATA_SIZE sizeof(DATA)

static int Pbox[32] = {
    4, 8, 7, 6, 3, 12, 16, 14,
    0, 2, 15, 22, 25, 1, 10, 31,
    18, 9, 20, 11, 24, 26, 29, 30,
    13, 23, 19, 5, 27, 17, 28, 21};

void print(vector<DATA>& v);
void print(vector<uint8_t>& v);

void addbit(DATA* block, DATA from, int position_from, int position_to);
void reverse(DATA* x);
void highLowChange(DATA* val);

DATA F(DATA val);
void doFeistel(vector<DATA>& before, vector<DATA>& after);

void str2Byte(string str, vector<uint8_t>& byte);
void byte2Data(vector<uint8_t>& byte, vector<DATA>& data);
void data2Byte(vector<DATA>& data, vector<uint8_t>& byte);

void addPadding(vector<uint8_t>& byte);
void removePadding(vector<uint8_t>& byte);

#endif