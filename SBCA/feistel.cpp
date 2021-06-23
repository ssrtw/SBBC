#include "stdafx.h"
#include "Feistel.h"
#include "util.h"

// 以PKCS#7對明文padding
// @param byte 要做padding的明文vector
void Feistel::addPKCS7(vector<uint8_t>* bytes) {
    // 檢查要padding多少
    // https://asecuritysite.com/encryption/padding_des
    // 使用RFC 5652(PKCS#7 Padding)方式，Padding到%16=0
    int needPadding = 16 - (bytes->size() % 16);
    for (int i = 0; i < needPadding; i++) {
        bytes->push_back(needPadding);
    }
}

// 移除PKCS#7的padding
// @param bytes 要移除padding的vector
void Feistel::rmPKCS7(vector<uint8_t>* bytes) {
    uint8_t check = (*bytes)[bytes->size() - 1];
    if (check > 16) {
        throw 1;
    }
    for (int i = 0; i < check; i++)
        bytes->pop_back();
}

// 取sbox的值做替換
// @param val 原始資料
// @param hand 選用一個sbox
// @return 原始資料經過sbox替換後的值
uint32_t Feistel::s(uint32_t val, int hand) {
    uint32_t res = 0;
    uint8_t tmp;
    for (int i = 0; i < 4; i++) {
        // 拿一個byte出來
        tmp = val >> 8 * i & 0xff;
        // 找box要替代的值
        res |= (sbox[hand][tmp >> 4][tmp & 0xf]) << 8 * i;
    }
    return res;
}

// 自訂的Feistel的Function
// @param val block左半值
// @param round 現在是第幾round
// @return Function算出的值
uint64_t Feistel::F(uint64_t val, int round) {
    int lHand = hands[round][0], rHand = hands[round][1];
    uint32_t h = s((uint32_t)(val >> 32), lHand);
    uint32_t l = s((uint32_t)(val & 0xffffffffffffffff), rHand);
    val = (uint64_t)(h) << 32 | l;
    val ^= ssrH;
    reverse(val);
    val ^= ssrL;
    highLowChange(val);

    val ^= gojoH;
    reverse(val);
    val ^= gojoL;
    highLowChange(val);

    val ^= kirotoH;
    reverse(val);
    val ^= kirotoL;
    highLowChange(val);

    // Permutation
    uint64_t tmp = 0;
    for (int ii = 0; ii < 64; ii++)
        addbit(tmp, val, Pbox[ii], ii);
    val = tmp;
    return val;
}

// 運行Feistel結構做加密
// @param plain 明文vector
// @return 密文vector
vector<uint64_t>* Feistel::encrypt(vector<uint64_t>& plain) {
    vector<uint64_t>* cipher = new vector<uint64_t>();
    uint64_t L, R;
    for (int i = 0; i < plain.size(); i += 2) {
        L = plain[i];
        R = plain[i + 1];
        // Permutation
        uint64_t tmp = 0;
        for (int ii = 0; ii < 64; ii++)
            addbit(tmp, L, IP[ii], ii);
        L = tmp;
        tmp = 0;
        for (int ii = 0; ii < 64; ii++)
            addbit(tmp, R, IP[ii], ii);
        R = tmp;
        if (modeCBC)
            if (i) {
                L ^= (*cipher)[i - 2];
                R ^= (*cipher)[i - 1];
            } else {
                L ^= initVecL ^ keys->getIdx(0);
                R ^= initVecR ^ keys->getIdx(1);
            }
        // 跑round
        for (int j = 0; j < 16; j++) {
            // 先讓右半與Key做XOR，將值丟入F函數
            uint64_t f = F(R ^ keys->getIdx(j), j);
            // 把左半XOR F函數的結果
            L ^= f;
            // 不是最後一round都要左右交換
            if (j != 15) {
                // swap兩邊
                R ^= L;
                L ^= R;
                R ^= L;
            }
        }
        cipher->push_back(L);
        cipher->push_back(R);
    }
    return cipher;
}

// 運行Feistel結構做解密
// @param cipher 密文vector
// @return 明文vector
vector<uint64_t>* Feistel::decrypt(vector<uint64_t>& cipher) {
    vector<uint64_t>* plain = new vector<uint64_t>();
    uint64_t L, R;
    for (int i = 0; i < cipher.size(); i += 2) {
        L = cipher[i];
        R = cipher[i + 1];
        // 跑round
        for (int j = 15; j >= 0; j--) {
            // 先讓右半與Key做XOR，將值丟入F函數
            uint64_t f = F(R ^ keys->getIdx(j), j);
            // 把左半XOR F函數的結果
            L ^= f;
            // 不是最後一round都要左右交換
            if (j != 0) {
                // swap兩邊
                R ^= L;
                L ^= R;
                R ^= L;
            }
        }
        if (modeCBC)
            if (i) {
                L ^= cipher[i - 2];
                R ^= cipher[i - 1];
            } else {
                L ^= initVecL ^ keys->getIdx(0);
                R ^= initVecR ^ keys->getIdx(1);
            }
        // Permutation
        uint64_t tmp = 0;
        for (int ii = 0; ii < 64; ii++)
            addbit(tmp, L, IP1[ii], ii);
        L = tmp;
        tmp = 0;
        for (int ii = 0; ii < 64; ii++)
            addbit(tmp, R, IP1[ii], ii);
        R = tmp;
        plain->push_back(L);
        plain->push_back(R);
    }
    return plain;
}

// 建構子
// 有預設的、直接讀取一堆參數與讀取Config物件傳進來的多載
Feistel::Feistel() : keys(nullptr), modeCBC(false), verbose(false), isEncrypt(false) {}
Feistel::Feistel(Key* k, bool modeCBC, bool verbose, bool isEncrypt) : keys(k), modeCBC(modeCBC), verbose(verbose), isEncrypt(isEncrypt) {
    keys = new Key(k);
}
Feistel::Feistel(Config* config) {
    // 從config拿到keys，複製一份過來
    keys = new Key(config->keys);
    modeCBC = config->modeCBC;
    verbose = config->verbose;
    isEncrypt = config->isEncrypt;
}

// 解構子
Feistel::~Feistel() {
    if (keys != nullptr) delete keys;
}

vector<uint8_t>* Feistel::Run(vector<uint8_t>* input) {
    vector<uint64_t>* result = nullptr;
    vector<uint64_t>* tmp = nullptr;
    vector<uint8_t>* plainBytes = nullptr;
    auto begin = chrono::steady_clock::now();
    if (isEncrypt) {
        // 加密
        addPKCS7(input);
        tmp = byteToU64(input);
        result = encrypt(*tmp);
        plainBytes = u64ToByte(result);
    } else {
        // 解密
        try {
            tmp = byteToU64(input);
            result = decrypt(*tmp);
            plainBytes = u64ToByte(result);
            rmPKCS7(plainBytes);
        } catch (int errCode) {
            SetColor(124);  // 灰底紅字
            cerr << "Decryption wrong, can't remove padding!" << endl;
            SetColor(7);  // Reset
            exit(0);
        }
    }
    auto end = chrono::steady_clock::now();
    usingTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    delete result, tmp;
    return plainBytes;
}

// 生成花費時間的get函數
// @return round key生成花費時間
uint64_t Feistel::getTime() {
    return usingTime;
}

void Feistel::showInfo() {
    cout << "key generation spend time: " << keys->getTime() << "us" << endl;
    cout << "cryption spend time: " << usingTime << "us" << endl;
}