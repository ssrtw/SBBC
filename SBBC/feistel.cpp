#include "stdafx.h"
#include "feistel.h"
#include "util.h"

// 是否顯示加解密資訊
bool verbose, modeCBC;

// 自訂的Feistel的Function
// @param val block左半值
// @param round 現在是第幾round
// @return Function算出的值
uint64_t F(uint64_t val, int round) {
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
// @param cipher 密文vector
void encrypt(vector<uint64_t>& plain, vector<uint64_t>& cipher, vector<uint64_t>& keys) {
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
                L ^= cipher[i - 2];
                R ^= cipher[i - 1];
            } else {
                L ^= initVecL ^ keys[0];
                R ^= initVecR ^ keys[1];
            }
        // 跑round
        for (int j = 0; j < 16; j++) {
            // 先讓右半與Key做XOR，將值丟入F函數
            uint64_t f = F(R ^ keys[j], j);
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
        cipher.push_back(L);
        cipher.push_back(R);
    }
}

// 運行Feistel結構做解密
// @param cipher 密文vector
// @param plain 明文vector
void decrypt(vector<uint64_t>& cipher, vector<uint64_t>& plain, vector<uint64_t>& keys) {
    uint64_t L, R;
    for (int i = 0; i < cipher.size(); i += 2) {
        L = cipher[i];
        R = cipher[i + 1];
        // 跑round
        for (int j = 15; j >= 0; j--) {
            // 先讓右半與Key做XOR，將值丟入F函數
            uint64_t f = F(R ^ keys[j], j);
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
                L ^= initVecL ^ keys[0];
                R ^= initVecR ^ keys[1];
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
        plain.push_back(L);
        plain.push_back(R);
    }
}
