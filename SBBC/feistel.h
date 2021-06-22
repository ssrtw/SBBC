#pragma once
#include "Key.h"
#include "Config.h"
// 是否顯示加解密資訊
extern bool verbose, modeCBC;

class Feistel {
   private:
    Key* keys;
    bool modeCBC, verbose, isEncrypt;
    uint64_t usingTime = 0;

   public:
    void addPKCS7(vector<uint8_t>* bytes);
    void rmPKCS7(vector<uint8_t>* bytes);
    uint32_t s(uint32_t val, int hand);
    uint64_t F(uint64_t val, int round);
    vector<uint64_t>* encrypt(vector<uint64_t>& plain);
    vector<uint64_t>* decrypt(vector<uint64_t>& cipher);
    Feistel();
    Feistel(Key* k, bool modeCBC, bool verbose, bool isEncrypt);
    Feistel(Config* config);
    ~Feistel();
    vector<uint8_t>* Run(vector<uint8_t>* input);
    uint64_t getTime();
    void showInfo();
};
