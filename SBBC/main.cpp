#include "stdafx.h"
#include "util.h"
#include "feistel.h"
#include "argHandle.h"

// 明文字串與密鑰
vector<uint8_t> input, key;
string outputName;
bool isEncrypt;

int main(int argc, char* argv[]) {
    // 處理資料
    // *----------------------------------------------------*

    // 以字串形式作為明文，預設加密作業要求之字串
    // TODO: 之後能夠選擇加密字串或讀取參數列的檔案
    // 是否列印出明文與密文的bytes，false時僅顯示加解密使用時間
    ArgumentParser program("sbbc");
    buildArgs(program);
    parserInit(program, argc, argv);
    setArg(program, verbose, input, key, modeCBC, outputName, isEncrypt);
    // 密鑰
    vector<uint64_t> keys;
    genKeys(key, keys);

    // 存放加解密後的結果的vector<uint64_t>
    vector<uint64_t> result;

    // 加密
    // *----------------------------------------------------*
    if (isEncrypt) {
        addPKCS7(input);
        vector<uint64_t> tmp;
        byteToU64(input, tmp);
        // 加密花費時間
        int64_t encryptTime;
        // 計時，參考https://stackoverflow.com/questions/2808398
        auto begin = chrono::steady_clock::now();

        encrypt(tmp, result, keys);

        auto end = chrono::steady_clock::now();
        encryptTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
        if (verbose) {
            cout << "Cipher:" << endl;
            print(result);
            cout << endl
                 << "Encryption time " << encryptTime << "us" << endl;
        }
    }
    // 解密
    // *----------------------------------------------------*

    else {
        try {
            // 解密花費時間
            int64_t decryptTime;
            vector<uint64_t> tmp;
            byteToU64(input, tmp);
            auto begin = chrono::steady_clock::now();
            decrypt(tmp, result, keys);
            auto end = chrono::steady_clock::now();
            decryptTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();
            if (verbose) {
                cout << endl
                     << "Decryption time " << decryptTime << "us" << endl;
            }
        } catch (int errCode) {
            switch (errCode) {
                case 1:
                    cerr << "Decryption wrong, can't remove padding!" << endl;  // red
            }
        }
    }

    ofstream output_file(outputName, ios::out | ios::binary);
    ostream_iterator<uint8_t> output_iterator(output_file);
    if (isEncrypt) {
        vector<uint8_t> cipherBytes;
        u64ToByte(result, cipherBytes);
        copy(cipherBytes.begin(), cipherBytes.end(), output_iterator);
    } else {
        vector<uint8_t> plainBytes;
        u64ToByte(result, plainBytes);
        rmPKCS7(plainBytes);
        print(plainBytes);
        copy(plainBytes.begin(), plainBytes.end(), output_iterator);
    }
    output_file.close();
}
