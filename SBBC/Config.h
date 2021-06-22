#pragma once
#include "Key.h"

class Config {
   private:
    ArgumentParser* program;

    bool exists_test(const string& name);
    void buildArgs();
    void parserInit(vector<string>& args);
    void parserInit(int& argc, char* argv[]);
    void setArg();

   public:
    Key* keys;
    string outputName;
    vector<uint8_t> text;
    bool verbose, modeCBC, isEncrypt;

    void saveFile(vector<uint8_t>* result);

    Config();
    Config(int argc, char* argv[]);
    Config(vector<string>& args);
    ~Config();
};