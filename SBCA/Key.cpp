#include "stdafx.h"
#include "util.h"
#include "Key.h"

// 於密鑰後方加上padding
// padding的方式與MD5、SHA2一樣，100...00||length
// @param key 要做資料轉換的vector
void Key::keyPadding(vector<uint8_t>& key) {
    uint64_t size = key.size();
    int needPadding = 64 - (key.size() % 64) - 9;
    key.push_back(0x80);
    for (int i = 0; i < needPadding; i++) {
        key.push_back(0);
    }
    for (int i = 0; i < 8; i++) {
        key.push_back((size >> (8 - i * 2)) && 0xff);
    }
}

// 用與md5相似結構產生出128bit作為Feistel的前兩組key值
// 中間使用一些SHA2的公式
// @param in 要雜湊的資料的vector
// @param out 要存放算出的雜湊值的vector
void Key::keyHashing(vector<uint32_t>& in, vector<uint64_t>& out) {
    // 密鑰雜湊的初始值
    // 我生日、桐人生日、C87取63的值5ce34160a1f04b47f8
    // c8763、48763、五條悟生日、班級座號、我的手機末四碼
    uint32_t h0 = 0x19990423, h1 = 0x20081007, h2 = 0x5ce34160, h3 = 0xa1f04b47;
    uint32_t f, g, h, tmp;
    for (int i = 0; i < in.size(); i += 16) {
        for (int j = 0; j < 16; j++) {
            uint32_t a = h0, b = h1, c = h2, d = h3;
            for (int r = 0; r < 64; r++) {
                if (r < 16) {
                    // 用SHA2的s0
                    tmp = rotateR(a, 2) ^ rotateR(a, 13) ^ rotateR(a, 22);
                    // 用SHA2的maj
                    f = tmp + (a & b) ^ (a & c) ^ (b & c);
                    g = j;
                } else if (r >= 16 && r < 32) {
                    // 用SHA2的s1，e->d
                    f = rotateR(d, 6) ^ rotateR(d, 11) ^ rotateR(d, 25);
                    g = (5 * j + 1) % 16;
                } else if (r >= 32 && r < 48) {
                    f = b ^ c ^ d;
                    g = (3 * j + 5) % 16;
                } else {
                    f = c ^ (b | (~d)) + (a & b) ^ ((~a) & c);
                    g = (3 * j + 5) % 16;
                }
                tmp = d;
                d = c;
                c = b;
                h = rotateR((a + f + keyK[r] + in[i * 16 + g]), (uint8_t)rot[r]);
                b = h + b;
                a = tmp;
            }
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
        }
    }
    out.push_back((uint64_t)h0 << 32 | h1);
    out.push_back((uint64_t)h2 << 32 | h3);
}

// 取原始key產生每個Round要用的key vector
// @param key 這次使用的密鑰，傳入一個vector，key多長都行，會被壓縮為64bit
// @param keys 所有的round key
void Key::genKeys(vector<uint8_t>& key, vector<uint64_t>& keys) {
    vector<uint8_t> keyBytes;
    vector<uint32_t>* calc = nullptr;

    // 用MD5、SHA2一樣的padding方式
    keyPadding(keyBytes);
    // 轉32bit的資料
    calc = byteToU32(&keyBytes);
    auto begin = chrono::steady_clock::now();
    // 對padding過的key進行雜湊算出前兩把round key
    keyHashing(*calc, keys);
    auto end = chrono::steady_clock::now();
    /*if (verbose)
        cout << "hash time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;*/
    begin = chrono::steady_clock::now();
    // 因為前面有用自訂的如md5的函式產生128bit的值，用這2組64bit的值產生剩下的14把key
    for (int i = 2; i < 16; i++) {
        // i 是 第幾把key
        // 拿前面第二個的key與(C87取63)最高的4byte串我的生日，再右旋rot的(i or not(i-2))%64
        uint64_t tmp = rotateR((keys[i - 2] ^ 0x5ce3416019990423), rot[((i | ~keys[i - 2]) & 0xf) % 64]);
        // 反轉tmp
        reverse(tmp);
        // 再將剛剛計算前面第二個key的值去XOR( ((keys[i-1]<<<7)&(keys[i-1]<<<6)) ^ (keys[i-1]<<<3) )
        tmp ^= (rotateR(keys[i - 1], 7) & rotateR(keys[i - 1], 6)) ^ rotateR(keys[i - 1], 3);
        keys.push_back(tmp);
    }

    end = chrono::steady_clock::now();
    /*if (verbose) {
        cout << "other key gen time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;
        print(keys);
    }*/
}

// 取原始key產生每個Round要用的key vector
// @param key 這次使用的密鑰，傳入string，key多長都行，會被壓縮為64bit
// @param keys 所有的round key
void Key::genKeys(string& key, vector<uint64_t>& keys) {
    vector<uint8_t>* keyBytes = nullptr;
    // 先把原本的密鑰字串轉成bytes vector
    keyBytes = str2Byte(key);
    genKeys(*keyBytes, keys);
    delete keyBytes;
}

// 建構子
Key::Key() {}
Key::Key(vector<uint8_t> k) {
    auto begin = chrono::steady_clock::now();
    genKeys(k, keys);
    auto end = chrono::steady_clock::now();
    usingTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
}
Key::Key(Key* other) {
    keys = vector<uint64_t>(*other->getKeys());
    usingTime = other->getTime();
}
// 用來讀取round key的function
// @return 第i把round key
uint64_t Key::getIdx(int i) {
    return keys[i];
}
// round key的get函數
// @return round key的vector
vector<uint64_t>* Key::getKeys() {
    return &keys;
}
// 生成花費時間的get函數
// @return round key生成花費時間
uint64_t Key::getTime() {
    return usingTime;
}