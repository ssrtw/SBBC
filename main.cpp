#include "feistel.h"

using namespace std;

int main() {
    // 處理資料
    // *----------------------------------------------------*

    // TODO: 目前以字串形式作為明文，之後要改為加密檔案
    // 明文字串
    string text = "I WILL PASS NETWORK SECURITY";
    // 密鑰
    // string key = "48763";

    // 存放明文的vector<uint8_t>
    vector<uint8_t> prePlain;
    // 存放明文的vector<DATA>
    vector<DATA> plain;

    str2Byte(text, prePlain);
    addPadding(prePlain);
    byte2Data(prePlain, plain);
    print(plain);

    // 加密
    // *----------------------------------------------------*

    // 存放密文的vector<DATA>
    vector<DATA> cipher;
    doFeistel(plain, cipher);
    print(cipher);

    // 解密
    // *----------------------------------------------------*

    // 存放解回的明文的vector<DATA>
    vector<DATA> decryPlain;
    doFeistel(cipher, decryPlain);
    print(decryPlain);
    
    // 把解回的明文以byte儲存
    vector<uint8_t> byte;
    data2Byte(decryPlain, byte);
    removePadding(byte);
    print(byte);
    return 0;
}
