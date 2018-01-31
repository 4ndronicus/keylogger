#ifndef FTPOBJ_H
#define FTPOBJ_H

//#include <iostream>
#include <string>

#define BUFFER_LENGTH   512

using namespace std;

class FTPObj
{
    public:
        FTPObj();
        FTPObj(std::string,std::string, std::string, std::string,std::string);
        FTPObj(std::string,std::string, std::string, std::string);
        virtual ~FTPObj();

        int setFilename(std::string);
        std::string getFilename();
        int setUsername(std::string);
        std::string getUsername();
        int setServer(std::string);
        std::string getServer();
        int setPath(std::string);
        std::string getPath();

        int FileSubmit();

    protected:

    private:

    std::string fileName;
    std::string user;
    std::string pass;
    std::string ftpserver;
    std::string szNewDirName;
//    std::string remoteName;
};

#endif // FTPOBJ_H
