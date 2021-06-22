#include "stdafx.h"
#include "util.h"
#include "Feistel.h"
#include "Key.h"
#include "Config.h"

int main(int argc, char* argv[]) {
    // 解析參數列
    Config* config = new Config(argc, argv);

    // 加解密運算
    Feistel* feistel = new Feistel(config);
    vector<uint8_t>* result = feistel->Run(&config->text);

    // 回存檔案
    config->saveFile(result);

    if (config->verbose) {
        feistel->showInfo();
    }

    // 刪除new出來的物件
    delete feistel, config;
}
