#ifndef FEISTEL_H
#define FEISTEL_H

// 是否顯示加解密資訊
extern bool verbose, modeCBC;

// feistel結構相關

uint32_t s(uint32_t val, int hand);
uint64_t F(uint64_t val, int round);
void encrypt(vector<uint64_t>& plain, vector<uint64_t>& cipher, vector<uint64_t>& keys);
void decrypt(vector<uint64_t>& cipher, vector<uint64_t>& plain, vector<uint64_t>& keys);

#endif