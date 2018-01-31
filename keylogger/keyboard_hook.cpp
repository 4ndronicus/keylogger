#include "keyboard_hook.h"
#include "../libraries/window_functions.h"
#include "keycode_map.h"

static HHOOK hhk = NULL;
static bool keyStates[257] = { false };

/**
The function that we call to process the keystroke that we have detected
*/
void processKeyStroke(DWORD keyCode, bool keyDown, char* asciiChar)
{

//    char asciiText[64] = { 0 };
    compareWindows();

    if( keyDown ) /**< if a key is being pressed, do this */
    {
        keyStates[keyCode] = true;
        getStatusOfKeys(keyCode, asciiChar);
//        writeLine(asciiChar);
    }
    else   /**< if a key is being released, do this */
    {
        keyStates[keyCode] = false;
    }
}

/**
The callback function for the keyboard hook
*/
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{

    char asciiText[64] = { 0 };

    /**< if there is an incoming action and a key was pressed */
    if(nCode == HC_ACTION && ((DWORD)lParam & 0x80000000) == 0)
//    if(((DWORD)lParam & 0x80000000) == 0)	// if there is an incoming action and a key was pressed
    {
        KBDLLHOOKSTRUCT* kStruct = (KBDLLHOOKSTRUCT*)lParam;
        bool keyDown = false;
        /**< If the flag for the key is 'pressed' */
        if(((int)kStruct->flags & 0x80) == 0)
        {
            keyDown = true;
        }
        processKeyStroke(kStruct->vkCode,keyDown,asciiText);
//        writeLine(asciiText);
    }
    return CallNextHookEx(hhk, nCode, wParam, lParam);
}

/**
How we put in the keyboard hook
*/
void addKeyboardHook()
{
    hhk = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
}

/**
How we remove the keyboard hook
*/
void rmvKeyboardHook()
{
    UnhookWindowsHookEx(hhk);
}

/*
    Check whether a key is down.
*/
bool keyDown(DWORD keyCode)
{
    return keyStates[keyCode];
}
