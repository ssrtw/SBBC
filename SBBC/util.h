#pragma once
void print(vector<uint64_t>& v);
void print(vector<uint8_t>& v);

// bitswise運算相關

void addbit(uint64_t& block, uint64_t from, int position_from, int position_to);
void reverse(uint64_t& x);
void highLowChange(uint64_t& val);
uint32_t rotateR(uint32_t value, uint8_t shift);
uint64_t rotateR(uint64_t value, uint8_t shift);

// 資料處理相關

void str2Byte(string str, vector<uint8_t>& bytes);
void byteToU32(vector<uint8_t>& bytes, vector<uint32_t>& data);
void byteToU64(vector<uint8_t>& bytes, vector<uint64_t>& data);
void u64ToByte(vector<uint64_t>& data, vector<uint8_t>& bytes);

void addPKCS7(vector<uint8_t>& bytes);
void rmPKCS7(vector<uint8_t>& bytes);

void keyPadding(vector<uint8_t>& key);

// key生成相關
void keyHashing(vector<uint32_t>& in, vector<uint64_t>& out);
void genKeys(vector<uint8_t>& key, vector<uint64_t>& keys);
void genKeys(string& key, vector<uint64_t>& keys);