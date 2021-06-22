#include "stdafx.h"
#include "Feistel.h"

// 列印字串
// @param v 要進行列印的vector
void print(vector<uint64_t>& v) {
    for (uint64_t ul : v) {
        printf("%016llx\n", ul);
    }
    printf("\n");
}

// 列印字串
// @param v 要進行列印的vector
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

// 將std::string轉為vector<uint8_t>
// @param str 字串
// @return 字串轉換後的vector
vector<uint8_t>* str2Byte(string str) {
    vector<uint8_t>* bytes = new vector<uint8_t>();
    for (uint8_t c : str) {
        bytes->push_back(c);
    }
    return bytes;
}

// 將byte轉回uint32_t
// @param bytes 要做資料轉換的vector
// @return 存放轉換後的vector
vector<uint32_t>* byteToU32(vector<uint8_t>* bytes) {
    vector<uint32_t>* data = new vector<uint32_t>();
    uint8_t* tmp = new uint8_t[4];
    // 重新組裝為8byte作為半個block，這樣加密時就能一個一個讀取了
    for (int i = 0; i < bytes->size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = (*bytes)[i + j];
        }
        // 將陣列uint64_t指標後取值
        data->push_back(*((uint32_t*)tmp));
    }
    delete[] tmp;
    return data;
}

// 將byte轉回uint64_t
// @param bytes 要做資料轉換的vector
// @return 存放轉換後的vector
vector<uint64_t>* byteToU64(vector<uint8_t>* bytes) {
    vector<uint64_t>* data = new vector<uint64_t>();
    uint8_t* tmp = new uint8_t[DATA_SIZE];
    // 重新組裝為8byte作為半個block，這樣加密時就能一個一個讀取了
    for (int i = 0; i < bytes->size(); i += DATA_SIZE) {
        for (int j = 0; j < DATA_SIZE; j++) {
            tmp[j] = (*bytes)[i + j];
        }
        // 將陣列uint64_t指標後取值
        data->push_back(*((uint64_t*)tmp));
    }
    delete[] tmp;
    return data;
}

// 將uint64_t轉回byte
// @param byte 要做資料轉換的vector
// @return 存放轉換後的vector
vector<uint8_t>* u64ToByte(vector<uint64_t>* data) {
    vector<uint8_t>* bytes = new vector<uint8_t>();
    for (uint64_t i : (*data)) {
        bytes->push_back(i & 0xff);
        bytes->push_back((i >> 8) & 0xff);
        bytes->push_back((i >> 16) & 0xff);
        bytes->push_back((i >> 24) & 0xff);
        bytes->push_back((i >> 32) & 0xff);
        bytes->push_back((i >> 40) & 0xff);
        bytes->push_back((i >> 48) & 0xff);
        bytes->push_back((i >> 56) & 0xff);
    }
    return bytes;
}