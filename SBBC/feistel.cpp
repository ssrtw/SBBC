#include "feistel.h"

// 是否顯示加解密資訊
bool verbose;

// 列印字串
// @param byte 要進行列印的vector
void print(vector<uint64_t>& v) {
    for (uint64_t ul : v) {
        printf("%016llx\n", ul);
    }
    printf("\n");
}

// 列印字串
// @param bytes 要進行列印的vector
void print(vector<uint8_t>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
}

// 做permutation
// @param block 要從放置換後的值
// @param from 原始資料
// @param position_from 從這個bit搬移
// @param position_to 搬到這個bit
void addbit(uint64_t& block, uint64_t from, int position_from, int position_to) {
    // 檢查如果為0就不用做shift與加法
    if (((from << (position_from)) & FIRSTBIT) != 0)
        block += (FIRSTBIT >> position_to);
}

// 對資料做反轉
// @param x 要反轉的資料
void reverse(uint64_t& x) {
    uint64_t n = x;
    n = ((n & 0xffffffff00000000) >> 32) | ((n & 0x00000000ffffffff) << 32);
    n = ((n & 0xffff0000ffff0000) >> 16) | ((n & 0x0000ffff0000ffff) << 16);
    n = ((n & 0xff00ff00ff00ff00) >> 8) | ((n & 0x00ff00ff00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0f0f0f0f0) >> 4) | ((n & 0x0f0f0f0f0f0f0f0f) << 4);
    n = ((n & 0xcccccccccccccccc) >> 2) | ((n & 0x3333333333333333) << 2);
    n = ((n & 0xaaaaaaaaaaaaaaaa) >> 1) | ((n & 0x5555555555555555) << 1);
    x = n;
}

// 將uint64_t的前後半bit做對調
// @param val block左半值
// return Function算出的值
void highLowChange(uint64_t& val) {
    // uint64_t 是 8byte
    // >>16是移動4個byte，0xffffffff共32個1
    // 把高低兩邊對調
    val = (val >> 32) | ((val & 0xffffffff) << 32);
}

// 輸入32bit的值回傳其右旋shift個bit的值
// @param value 要旋轉的value
// @param shift 右旋幾個bit
// @return 旋轉後的結果
uint32_t rotateR(uint32_t value, uint8_t shift) {
    return value >> shift | value << (32 - shift);
}

// 輸入64bit的值回傳其右旋shift個bit的值
// @param value 要旋轉的value
// @param shift 右旋幾個bit
// @return 旋轉後的結果
uint64_t rotateR(uint64_t value, uint8_t shift) {
    return value >> shift | value << (64 - shift);
}

// 取sbox的值做替換
// @param val 原始資料
// @param hand 選用一個sbox
// @return 原始資料經過sbox替換後的值
uint32_t s(uint32_t val, int hand) {
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
        plain.push_back(L);
        plain.push_back(R);
    }
}

// 將std::string轉為vector<uint8_t>
// @param str 字串
// @param byte 字串轉換後的vector
void str2Byte(string str, vector<uint8_t>& bytes) {
    for (uint8_t c : str) {
        bytes.push_back(c);
    }
}

// 將byte轉回uint32_t
// @param bytes 要做資料轉換的vector
// @param data 存放轉換後的vector
void byteToU32(vector<uint8_t>& bytes, vector<uint32_t>& data) {
    uint8_t* tmp = new uint8_t[4];
    // 重新組裝為8byte作為半個block，這樣加密時就能一個一個讀取了
    for (int i = 0; i < bytes.size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = bytes[i + j];
        }
        // 將陣列uint64_t指標後取值
        data.push_back(*((uint32_t*)tmp));
    }
    delete[] tmp;
}

// 將byte轉回uint64_t
// @param bytes 要做資料轉換的vector
// @param data 存放轉換後的vector
void byteToU64(vector<uint8_t>& bytes, vector<uint64_t>& data) {
    uint8_t* tmp = new uint8_t[DATA_SIZE];
    // 重新組裝為8byte作為半個block，這樣加密時就能一個一個讀取了
    for (int i = 0; i < bytes.size(); i += DATA_SIZE) {
        for (int j = 0; j < DATA_SIZE; j++) {
            tmp[j] = bytes[i + j];
        }
        // 將陣列uint64_t指標後取值
        data.push_back(*((uint64_t*)tmp));
    }
    delete[] tmp;
}

// 將uint64_t轉回byte
// @param byte 要做資料轉換的vector
// @param data 存放轉換後的vector
void u64ToByte(vector<uint64_t>& data, vector<uint8_t>& byte) {
    for (uint64_t i : data) {
        byte.push_back(i & 0xff);
        byte.push_back((i >> 8) & 0xff);
        byte.push_back((i >> 16) & 0xff);
        byte.push_back((i >> 24) & 0xff);
        byte.push_back((i >> 32) & 0xff);
        byte.push_back((i >> 40) & 0xff);
        byte.push_back((i >> 48) & 0xff);
        byte.push_back((i >> 56) & 0xff);
    }
}

// 以PKCS#7對明文padding
// @param byte 要做padding的明文vector
void addPKCS7(vector<uint8_t>& bytes) {
    // 檢查要padding多少
    // https://asecuritysite.com/encryption/padding_des
    // 使用RFC 5652(PKCS#7 Padding)方式，Padding到%16=0
    int needPadding = 16 - (bytes.size() % 16);
    for (int i = 0; i < needPadding; i++) {
        bytes.push_back(needPadding);
    }
}

// 移除PKCS#7的padding
// @param bytes 要移除padding的vector
void rmPKCS7(vector<uint8_t>& bytes) {
    uint8_t check = bytes[bytes.size() - 1];
    for (int i = 0; i < check; i++)
        bytes.pop_back();
}

// 於密鑰後方加上padding
// padding的方式與MD5、SHA2一樣，100...00||length
// @param key 要做資料轉換的vector
void keyPadding(vector<uint8_t>& key) {
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
void keyHashing(vector<uint32_t>& in, vector<uint64_t>& out) {
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
// @param key 這次使用的密鑰，傳入string，key多長都行，會被壓縮為64bit
// @param keys 所有的round key
void genKeys(string& key, vector<uint64_t>& keys) {
    vector<uint8_t> keyBytes;
    vector<uint32_t> calc;

    // 先把原本的密鑰字串轉成bytes vector
    str2Byte(key, keyBytes);
    // 用MD5、SHA2一樣的padding方式
    keyPadding(keyBytes);
    // 轉32bit的資料
    byteToU32(keyBytes, calc);
    auto begin = chrono::steady_clock::now();
    // 對padding過的key進行雜湊算出前兩把round key
    keyHashing(calc, keys);
    auto end = chrono::steady_clock::now();
    if (verbose)
        cout << "hash time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;
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
    if (verbose) {
        cout << "other key gen time: " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "us" << endl;
        print(keys);
    }
}