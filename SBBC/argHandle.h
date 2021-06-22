#pragma once
#include "stdafx.h"
inline bool exists_test(const string& name);
void buildArgs(argparse::ArgumentParser& program);
void parserInit(ArgumentParser& program, vector<string>& args);
void parserInit(ArgumentParser& program, int& argc, char* argv[]);
void setArg(ArgumentParser& program, bool& verbose, vector<uint8_t>& text, vector<uint8_t>& key, bool& modeCBC, string& outputName, bool& isEncrypt);