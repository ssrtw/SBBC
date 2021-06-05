#include "argparse/argparse.hpp"
#include "feistel.h"
using namespace std;

int main(int argc, char* argv[]) {
    // 處理資料
    // *----------------------------------------------------*

    // 以字串形式作為明文，預設加密作業要求之字串
    // TODO: 之後能夠選擇加密字串或讀取參數列的檔案

    // 明文字串
    string text;
    // 是否列印出明文與密文的bytes，false時僅顯示加解密使用時間
    argparse::ArgumentParser program("sbbc");
    program.add_argument("--showMore")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-t")
        .default_value(string("I WILL PASS NETWORK SECURITY"))
        .action([](const std::string& value) { return value; });

    try {
        program.parse_args(argc, argv);  // Example: ./main -abc 1.95 2.47
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    bool showMore = program.get<bool>("--showMore");  // true
    text = program.get<string>("-t");                 // text

    // 密鑰
    // string key = "48763";

    // 存放明文的vector<uint8_t>
    vector<uint8_t> plainBytes;
    // 存放明文的vector<uint64_t>
    vector<uint64_t> plain;

    str2Byte(text, plainBytes);
    addPadding(plainBytes);
    byte2Data(plainBytes, plain);

    // 加密
    // *----------------------------------------------------*

    // 加密花費時間
    int64_t encryptTime;
    // 存放密文的vector<uint64_t>
    vector<uint64_t> cipher;
    // 計時，參考https://stackoverflow.com/questions/2808398
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    encrypt(plain, cipher);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    encryptTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();

    // 解密
    // *----------------------------------------------------*

    // 解密花費時間
    int64_t decryptTime;
    // 存放解回的明文的vector<uint64_t>
    vector<uint64_t> decryPlain;
    begin = chrono::steady_clock::now();

    decrypt(cipher, decryPlain);

    end = chrono::steady_clock::now();
    decryptTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    // 把解回的明文以byte儲存
    plainBytes.clear();
    data2Byte(decryPlain, plainBytes);
    removePadding(plainBytes);
    if (showMore) {
        cout << "Cipher:" << endl;
        print(cipher);
        cout << "Plain:" << endl;
        print(decryPlain);
        cout << "Plain text:" << endl;
        print(plainBytes);
    }
    cout << endl
         << "Encryption time " << encryptTime << "us" << endl
         << "Decryption time " << decryptTime << "us" << endl;
}
