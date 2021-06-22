#include "stdafx.h"

// Reference from https://blog.wildsky.cc/posts/c-code-note
void SetColor(int color = 7) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}