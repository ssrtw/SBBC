#include "feistel.h"

// 列印字串
// @param byte 要進行列印的vector
void print(vector<DATA>& v) {
    for (DATA ul : v) {
        printf("%08x\n", ul);
    }
    printf("\n");
}

// 列印字串
// @param byte 要進行列印的vector
void print(vector<uint8_t>& byte) {
    for (int i = 0; i < byte.size(); i++) {
        cout << byte[i];
    }
}

// 做permutation
// @param block 要從放置換後的值
// @param from 原始資料
// @param position_from 從這個bit搬移
// @param position_to 搬到這個bit
void addbit(DATA* block, DATA from, int position_from, int position_to) {
    if (((from << (position_from)) & FIRSTBIT) != 0)
        *block += (FIRSTBIT >> position_to);
}

// 對資料做反轉
// @param x 要反轉的資料
void reverse(DATA* x) {
    DATA n = *x;
    n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    *x = n;
}

// 將DATA的前後半bit做對調
// @param val block左半值
// return Function算出的值
void highLowChange(DATA* val) {
    DATA high, low;
    // DATA 是 4byte
    // >>16是移動2個byte，0xffff共16個1
    high = (*val >> 16);
    low = (*val & 0xffff);
    // 把高低兩邊對調
    *val = high | (low << 16);
}

// 自訂的Feistel的Function
// @param val block左半值
// @return Function算出的值
DATA F(DATA val) {
    val ^= 0xC8763423;  // C8763星爆氣流斬，4/23我生日
    reverse(&val);
    val ^= 0x10612011;    // 學號去掉前面的4
    highLowChange(&val);  // 高byte與低byte交換
    val ^= 0x5b006b00;    // 孫:5b6b
    reverse(&val);
    val ^= 0x005b0078;    // 學:5b78
    highLowChange(&val);  // 高byte與低byte交換
    val ^= 0x4e00fb00;    // 任:4efb

    // Permutation
    DATA tmp = 0, tmp2 = 0;
    for (int ii = 0; ii < 32; ii++)
        addbit(&tmp, val, Pbox[ii] - 1, ii);
    for (int ii = 0; ii < 32; ii++)
        addbit(&tmp2, tmp, Pbox[ii] - 1, ii);
    val = tmp2;
    return val;
}

// 運行Feistel結構做加解密
// @param before 加密或解密前的vector
// @param after 加密或解密後要存放計算的vector
void doFeistel(vector<DATA>& before, vector<DATA>& after) {
    DATA L, R;
    for (int i = 0; i < before.size(); i += 2) {
        L = before[i];
        R = before[i + 1];
        // 跑round
        for (int j = 0; j < 16; j++) {
            // 算F函數值
            DATA f = F(R);
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
        after.push_back(L);
        after.push_back(R);
    }
}

// 將std::string轉為vector<uint8_t>
// @param str 字串
// @param byte 字串轉換後的vector
void str2Byte(string str, vector<uint8_t>& byte) {
    for (uint8_t c : str) {
        byte.push_back(c);
    }
}

// 將byte轉回DATA
// @param byte 要做資料轉換的vector
// @param data 存放轉換後的vector
void byte2Data(vector<uint8_t>& byte, vector<DATA>& data) {
    uint8_t* tmp = new uint8_t[DATA_SIZE];
    // 重新組裝為4byte作為半個block，這樣加密時就能一個一個讀取了
    for (int i = 0; i < byte.size(); i += DATA_SIZE) {
        for (int j = 0; j < DATA_SIZE; j++) {
            tmp[j] = byte[i + j];
        }
        // 將陣列DATA指標後取值
        data.push_back(*((DATA*)tmp));
    }
}

// 將DATA轉回byte
// @param byte 要做資料轉換的vector
// @param data 存放轉換後的vector
void data2Byte(vector<DATA>& data, vector<uint8_t>& byte) {
    for (DATA i : data) {
        byte.push_back(i & 0xff);
        byte.push_back((i >> 8) & 0xff);
        byte.push_back((i >> 16) & 0xff);
        byte.push_back((i >> 24) & 0xff);
    }
}

// 於明文後面加上padding
// @param byte 要做資料轉換的vector
void addPadding(vector<uint8_t>& byte) {
    // 檢查要padding多少
    // https://asecuritysite.com/encryption/padding_des
    // 使用RFC 2898(PKCS#5 Padding)方式，也就是Padding 0x1~0x8
    int needPadding = 8 - (byte.size() % 8);
    for (int i = 0; i < needPadding; i++) {
        byte.push_back(needPadding);
    }
}

// 移除解回明文的padding
// 以PKCS#5 padding
// @param byte 要移除padding的vector
void removePadding(vector<uint8_t>& byte) {
    uint8_t check = byte[byte.size() - 1];
    if (check < 8)
        for (int i = 0; i < check; i++)
            byte.pop_back();
}