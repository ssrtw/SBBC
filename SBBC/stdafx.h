#pragma once
#define _HAS_STD_BYTE 0
#include <stdlib.h>
#include <sys/stat.h>

#include <chrono>  // 用於檢視加解密花費時間
#include <iostream>
#include <string>
#include <vector>

#include "argparse/argparse.hpp"
#include "const.h"

#include <fstream>
#include <algorithm>

#include <windows.h>

using namespace std;
using namespace argparse;