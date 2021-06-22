#include "stdafx.h"
#include "Config.h"
#include "util.h"

bool Config::exists_test(const string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void Config::buildArgs() {
    program->add_argument("-v", "--verbose")
        .help("show more infomation")
        .default_value(false)
        .implicit_value(true);

    program->add_argument("-e")
        .help("Encrypt")
        .default_value(true)
        .implicit_value(true);

    program->add_argument("-d")
        .help("Decrypt")
        .default_value(false)
        .implicit_value(true);

    program->add_argument("-c", "--cbc")
        .help("Use CBC mode Encryption/Decryption")
        .default_value(false)
        .implicit_value(true);

    program->add_argument("-t", "--text")
        .help("Plain text")
        .default_value(string("I WILL PASS NETWORK SECURITY"))
        .action([](const string& value) { return value; });

    program->add_argument("-k", "--key")
        .help("Key")
        .default_value(string("I4B53-410612011"))
        .action([](const string& value) { return value; });

    program->add_argument("-i", "--input")
        .default_value(string(""))
        .action([](const string& value) {
            return value;
        });
    program->add_argument("-o", "--output")
        .default_value(string(""))
        .action([](const string& value) { return value; });
}

void Config::parserInit(vector<string>& args) {
    try {
        program->parse_args(args);
    } catch (const runtime_error& err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }
}

void Config::parserInit(int& argc, char* argv[]) {
    try {
        program->parse_args(argc, argv);
    } catch (const runtime_error& err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }
}

void Config::setArg() {
    verbose = program->get<bool>("-v");  // verbose
    // use CBC Mode
    modeCBC = program->get<bool>("-c");
    // encrypt or decrypt
    isEncrypt = program->get<bool>("-e");
    if (program->get<bool>("-d")) isEncrypt = false;
    string filename = program->get<string>("-i");
    vector<unsigned char>* buffer = new vector<unsigned char>;
    if (filename != "") {
        if (exists_test(filename)) {
            ifstream stream(filename, ios::binary | ios::in);
            // read file
            buffer = new vector<unsigned char>(istreambuf_iterator<char>(stream), {});
            for (char c : *buffer)
                text.push_back(c);
        } else {
            throw 3;
        }
    } else {
        string str = program->get<string>("-t");
        for (char c : str)
            text.push_back(c);  // text
    }

    // key
    string k = program->get<string>("-k");
    vector<uint8_t> key;
    for (char c : k)
        key.push_back(c);
    keys = new Key(key);

    // fileName
    outputName = program->get<string>("-o");
    if (outputName == "")
        if (isEncrypt)
            outputName = "cipher.bin";
        else
            outputName = "plain.txt";
}

void Config::saveFile(vector<uint8_t>* result) {
    // ¿é¥XÀÉ®×
    // *----------------------------------------------------*
    ofstream output_file(outputName, ios::out | ios::binary);
    ostream_iterator<uint8_t> output_iterator(output_file);
    copy(result->begin(), result->end(), output_iterator);
    output_file.close();
}

Config::Config() {
    program = new ArgumentParser("SBBC");
    buildArgs();
}

Config::Config(int argc, char* argv[]) : Config() {
    parserInit(argc, argv);
    try {
        setArg();
    } catch (int errCode) {
        SetColor(124);  // ¦Ç©³¬õ¦r
        cerr << "Input file not exist!!!" << endl;
        SetColor(7);  // Reset
        exit(0);
    }
}

Config::Config(vector<string>& args) : Config() {
    parserInit(args);
    try {
        setArg();
    } catch (int errCode) {
        SetColor(124);  // ¦Ç©³¬õ¦r
        cerr << "Input file not exist!!!" << endl;
        SetColor(7);  // Reset
        exit(0);
    }
}

Config::~Config() {
    if (program != nullptr)
        delete program;
    if (keys != nullptr)
        delete keys;
}