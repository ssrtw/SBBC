#ifndef FEISTEL_H
#define FEISTEL_H

// 用於檢視加解密花費時間
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>

#include "const.h"
using namespace std;

void print(vector<uint64_t>& v);
void print(vector<uint8_t>& v);

void addbit(uint64_t& block, uint64_t from, int position_from, int position_to);
void reverse(uint64_t& x);
void highLowChange(uint64_t& val);

uint32_t s(uint32_t val, int hand);
uint64_t F(uint64_t val, int round);
void encrypt(vector<uint64_t>& before, vector<uint64_t>& after);
void decrypt(vector<uint64_t>& before, vector<uint64_t>& after);

void str2Byte(string str, vector<uint8_t>& byte);
void byte2Data(vector<uint8_t>& byte, vector<uint64_t>& data);
void data2Byte(vector<uint64_t>& data, vector<uint8_t>& byte);

void addPadding(vector<uint8_t>& byte);
void removePadding(vector<uint8_t>& byte);

#endif