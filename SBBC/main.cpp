#include "argparse/argparse.hpp"
#include "feistel.h"
using namespace std;

int main(int argc, char* argv[]) {
    // 處理資料
    // *----------------------------------------------------*

    // 以字串形式作為明文，預設加密作業要求之字串
    // TODO: 之後能夠選擇加密字串或讀取參數列的檔案

    // 明文字串與密鑰
    string text, key;
    // 是否列印出明文與密文的bytes，false時僅顯示加解密使用時間
    argparse::ArgumentParser program("sbbc");
    program.add_argument("-v", "--verbose")
        .help("show more infomation")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-t", "--text")
        .help("plain text")
        .default_value(string("I WILL PASS NETWORK SECURITY"))
        .action([](const std::string& value) { return value; });

    program.add_argument("-k", "--key")
        .help("encryption key")
        .default_value(string("I4B53-410612011"))
        .action([](const std::string& value) { return value; });

    try {
        program.parse_args(argc, argv);
    } catch (const runtime_error& err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }
    verbose = program.get<bool>("-v");  // verbose
    text = program.get<string>("-t");   // text
    key = program.get<string>("-k");    // key
    // 密鑰
    vector<uint64_t> keys;
    genKeys(key, keys);

    // 存放明文的vector<uint8_t>
    vector<uint8_t> plainBytes;
    // 存放明文的vector<uint64_t>
    vector<uint64_t> plain;

    str2Byte(text, plainBytes);
    addPKCS7(plainBytes);
    byteToU64(plainBytes, plain);

    // 加密
    // *----------------------------------------------------*

    // 加密花費時間
    int64_t encryptTime;
    // 存放密文的vector<uint64_t>
    vector<uint64_t> cipher;
    // 計時，參考https://stackoverflow.com/questions/2808398
    auto begin = chrono::steady_clock::now();

    encrypt(plain, cipher, keys);

    auto end = chrono::steady_clock::now();
    encryptTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();

    // 解密
    // *----------------------------------------------------*

    // 解密花費時間
    int64_t decryptTime;
    // 存放解回的明文的vector<uint64_t>
    vector<uint64_t> decryPlain;
    begin = chrono::steady_clock::now();

    decrypt(cipher, decryPlain, keys);

    end = chrono::steady_clock::now();
    decryptTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    // 把解回的明文以byte儲存
    plainBytes.clear();
    u64ToByte(decryPlain, plainBytes);
    rmPKCS7(plainBytes);
    if (verbose) {
        cout << endl
             << "Encryption time " << encryptTime << "us" << endl
             << "Decryption time " << decryptTime << "us" << endl;
    }
    cout << "Cipher:" << endl;
    print(cipher);
    cout << "Plain text:" << endl;
    print(plainBytes);
}
