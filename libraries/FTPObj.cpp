#include "fileio.h"
#include "FTPObj.h"
#include <string.h>
#include <iostream>
#include <wininet.h>
#include <windows.h>
#include <time.h>
#include <sstream>

using namespace std;

#define TIME_LEN            20

FTPObj::FTPObj()
{
    //ctor
}

FTPObj::FTPObj(std::string fileName, std::string userName, std::string passWord, std::string server ){
    FTPObj::fileName = fileName;
    FTPObj::user = userName;
    FTPObj::pass = passWord;
    FTPObj::ftpserver = server;
}

FTPObj::FTPObj(std::string fileName, std::string userName, std::string passWord, std::string server, std::string path){
    FTPObj::fileName = fileName;
    FTPObj::user = userName;
    FTPObj::pass = passWord;
    FTPObj::ftpserver = server;
    FTPObj::szNewDirName = path;
}

FTPObj::~FTPObj()
{
    //dtor
}


int FTPObj::FileSubmit(){

    char remoteName[MAX_PATH] = {0};
    HINTERNET hInternet;
    HINTERNET hFtpSession;

    /** Set up the timestamp for the log file */
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[TIME_LEN]; /** Used for timestamp */
    tstruct = *localtime(&now);
    strftime(buf,sizeof(buf),"%Y%m%d-%H%M%S.",&tstruct);

    // Check for non-zero filename, user, password, ftpserver lengths
    if( FTPObj::fileName.length() < 1 ){
        return -1;
    }

    if( FTPObj::user.length() < 1 ){
        return -2;
    }

    if( FTPObj::pass.length() < 1 ){
        return -3;
    }

    if( FTPObj::ftpserver.length() < 1 ){
        return -4;
    }

    /** Create the connection */
    hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
    if (hInternet == NULL)
    {
        return -5;
    }

    /** Connect to the FTP server */
    hFtpSession = InternetConnect(hInternet,ftpserver.c_str() , INTERNET_DEFAULT_FTP_PORT, user.c_str(), pass.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
    if( hFtpSession == NULL ){
        return -6;
    }

    /** Make sure we have a valid path to start in on the FTP server */
    if( szNewDirName.length() == 0 ){
        szNewDirName = "/";
    }

    /** Change to the specified path on the FTP server*/
    if( FtpSetCurrentDirectory( hFtpSession, szNewDirName.c_str() ) == FALSE){
        return -7;
    }

    /** Create the filename that the log will be called on the FTP server. */
    strcpy( remoteName, buf );
    strncat( remoteName, fileName.c_str(), (size_t)sizeof( remoteName ) );

    /** Upload the file */
    if( FtpPutFile(hFtpSession, fileName.c_str(), remoteName, FTP_TRANSFER_TYPE_ASCII, 0) == FALSE ){
        return -8;
    }

    /** Have to do this or the handles will not close */
    Sleep(3000);

    /** Close the handles */
    InternetCloseHandle( hFtpSession );
    InternetCloseHandle( hInternet );

    return 0;
}
