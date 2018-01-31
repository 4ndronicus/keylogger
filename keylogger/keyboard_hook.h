#ifndef KEYBOARD_HOOK_H
#define KEYBOARD_HOOK_H

#include <windows.h>


using namespace std;

void processKeyStroke(DWORD,bool,char*);
LRESULT CALLBACK LowLevelKeyboardProc(int,WPARAM,LPARAM);
void addKeyboardHook();
void rmvKeyboardHook();
bool keyDown(DWORD);

#endif

