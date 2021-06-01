#include "feistel.h"

using namespace std;

int main() {
    // 處理資料
    // *----------------------------------------------------*
    // 讀取明文
    //string text = "哈囉!你們好這裡是台灣～!"; // text
    string text = "I WILL PASS NETWORK SECURITY";  // text
    string key = "48763";                          //key
    // 拆成小單位(1 byte)
    vector<unsigned char> prePlain;
    vector<DATA> plain;
    for (int i = 0; i < text.size(); i++) {
        prePlain.push_back(text[i]);
    }
    for (int i = 0; i < prePlain.size(); i++) {
        char tmp = prePlain[i];
        cout << (char)tmp;
    }
    cout << endl;
    // 檢查要padding多少
    // https://asecuritysite.com/encryption/padding_des
    // 使用RFC 2898(PKCS#5 Padding)方式，也就是Padding 0x1~0x8
    int needPadding = 8 - (prePlain.size() % 8);
    for (int i = 0; i < needPadding; i++) {
        prePlain.push_back(needPadding);
    }
    char tmp[4] = {0};
    // 重新組裝為4byte作為半個block，這樣加密時就能一個一個讀取了
    for (int i = 0; i < prePlain.size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = prePlain[i + j];
        }
        // 將陣列DATA指標後取值
        plain.push_back(*((DATA*)tmp));
    }
    print(&plain);
    // 加密
    // *----------------------------------------------------*
    // 拿vertor plain這個陣列來做block跑round
    vector<DATA> cipher;
    DATA L, R;
    for (int i = 0; i < plain.size(); i += 2) {
        L = plain[i];
        R = plain[i + 1];
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
        cipher.push_back(L);
        cipher.push_back(R);
    }
    print(&cipher);

    // 解密
    // *----------------------------------------------------*
    vector<DATA> decryPlain;
    vector<unsigned char> bytes;
    for (int i = 0; i < cipher.size(); i += 2) {
        L = cipher[i];
        R = cipher[i + 1];
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
        decryPlain.push_back(L);
        decryPlain.push_back(R);
    }
    print(&decryPlain);

    vector<char> result;
    for (DATA i : decryPlain) {
        result.push_back(i & 0xff);
        result.push_back((i >> 8) & 0xff);
        result.push_back((i >> 16) & 0xff);
        result.push_back((i >> 24) & 0xff);
    }
    char check = result[result.size() - 1];
    if (check < 8)
        for (int i = 0; i < check; i++)
            result.pop_back();
    for (int i = 0; i < result.size(); i++) {
        char tmp = result[i];
        cout << (char)tmp;
    }
    return 0;
}
