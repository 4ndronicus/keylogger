#ifndef KEYCODE_MAP_H
#define KEYCODE_MAP_H

#include <string>
#include <windows.h>

using namespace std;

const int SHIFT_DELTA = 300;

std::string GetClipboardText();
void logClipboardCts();
bool keyDown(DWORD keyCode);
bool shiftDown(DWORD keyCode);
bool ctrlDown( DWORD keyCode);
bool wndDown( DWORD keyCode);
bool altDown( DWORD keyCode);
void getStatusOfKeys(DWORD keyCode, char* asciiChar);

#endif
