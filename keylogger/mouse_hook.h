#ifndef MOUSE_HOOK_H
#define MOUSE_HOOK_H

#include <windef.h>

using namespace std;

LRESULT CALLBACK MouseHookProc(int,WPARAM,LPARAM);
void begMouseHook(HINSTANCE hInstance);
void endMouseHook();

#endif

