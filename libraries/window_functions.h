#ifndef WINDOW_FUNCTIONS_H
#define WINDOW_FUNCTIONS_H

#include <windows.h>

using namespace std;

const int TITLE_LENGTH = 1024;

void getProcIDFromHwnd(HWND);
void recWindowTitle(HWND);
void recChildWindowTitle(HWND);
void compareWindows();

#endif
