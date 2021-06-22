#include "stdafx.h"
using namespace argparse;

inline bool exists_test(const string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void buildArgs(ArgumentParser& program) {
    program.add_argument("-v", "--verbose")
        .help("show more infomation")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-e")
        .help("Encrypt")
        .default_value(true)
        .implicit_value(true);

    program.add_argument("-d")
        .help("Decrypt")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-c", "--cbc")
        .help("Use CBC mode Encryption/Decryption")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-t", "--text")
        .help("Plain text")
        .default_value(string("I WILL PASS NETWORK SECURITY"))
        .action([](const string& value) { return value; });

    program.add_argument("-k", "--key")
        .help("Key")
        .default_value(string("I4B53-410612011"))
        .action([](const string& value) { return value; });

    program.add_argument("-i", "--input")
        .default_value(string(""))
        .action([](const string& value) {
            return value;
        });
    program.add_argument("-o", "--output")
        .default_value(string(""))
        .action([](const string& value) { return value; });
}

void parserInit(ArgumentParser& program, vector<string>& args) {
    try {
        program.parse_args(args);
    } catch (const runtime_error& err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }
}
void parserInit(ArgumentParser& program, int& argc, char* argv[]) {
    try {
        program.parse_args(argc, argv);
    } catch (const runtime_error& err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }
}

void setArg(ArgumentParser& program, bool& verbose, vector<uint8_t>& text, vector<uint8_t>& key, bool& modeCBC, string& outputName, bool& isEncrypt) {
    verbose = program.get<bool>("-v");  // verbose
    string filename = program.get<string>("-i");
    vector<unsigned char>* buffer = new vector<unsigned char>;
    if (filename != "") {
        if (exists_test(filename)) {
            ifstream stream(filename, ios::binary | ios::in);
            // read a JSON file
            buffer = new vector<unsigned char>(istreambuf_iterator<char>(stream), {});
            for (char c : *buffer)
                text.push_back(c);
        } else {
            throw 3;
        }
    } else {
        string str = program.get<string>("-t");
        for (char c : str)
            text.push_back(c);  // text
    }
    string k = program.get<string>("-k");  // key
    for (char c : k)
        key.push_back(c);

    modeCBC = program.get<bool>("-c");  // use CBC Mode
    isEncrypt = program.get<bool>("-e");
    if (program.get<bool>("-d")) isEncrypt = false;
    outputName = program.get<string>("-o");
    if (outputName == "")
        if (isEncrypt)
            outputName = "cipher.bin";
        else
            outputName = "plain.txt";
}