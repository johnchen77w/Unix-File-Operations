//
// Created by John Chen on 2019-09-23.
//

#define ASN1_MANAGE_H
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <ftw.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <string.h>
#include "Manage.h"

using namespace std;

/**
 * Constructor.  This creates an instance of the class and initiatives it.
 * @param fName
 */
Manage::Manage(const char* fName)
{
    struct stat st;
    struct passwd *pwd = getpwuid(st.st_uid);
    struct group *grp = getgrgid(st.st_gid);
    if (stat(fName, &st) != 0)
    {
        errorNumber = errno;
        perror("stat error");
    }
    fileName = fName;                               // file name
    fileType = (unsigned long)st.st_mode;           // file type
    fileSize = (long long)st.st_size;               // file size
    userID = st.st_uid;                             // user id
    userName = pwd -> pw_name;                      // user name
    groupID = st.st_gid;                            // group name
    groupName = grp -> gr_name;                     // group id
    permissions = st.st_mode;                       // file permissions
    accessTime = ctime(&st.st_atime);               // last time access
    modificationTime = ctime(&st.st_mtime);         // last time modify
    statusChangeTime = ctime(&st.st_ctime);         // last time change its status
    blockSize = st.st_blksize;                      // block size
    errorNumber = 0;                                // error number
    std::vector <Manage> children;                  // children vector
}

/**
 * Destructor.  This destroys and frees up any resources attached to the object the destructor was called on.
 */
Manage::~Manage() { }


/**
 * This function will take a file stream as a parameter and dump the contents of the named file to that file stream.
 * @param fileStream
 * @return 0
 */
int Manage::Dump(ostream &fileStream)
{
    // check for regular file
    if (!S_ISREG(fileType))
    {
        errorNumber = errno;
        perror("Not a regular file\n");
    }
    // check file status (open/close)
    if (fileStream.eof())
    {
        errorNumber = errno;
        perror("File isn't open\n");
    } else
    {
        long blkSize = this->getBlockSize();
        char charArr[blkSize];
        ifstream fileStreamIn (fileName); // dump to filestream
        if (fileStreamIn.is_open())
        {
            while (!fileStreamIn.eof())
            {
                fileStreamIn.getline(charArr, blkSize);
                fileStream << charArr << endl;
            }
        } else
        {
            errorNumber = errno;
            perror("File isn't open\n");
        }
    }
    return 0;
}

/**
 * This changes the name of the file from its existing name to the new name provided as a parameter to this function.
 * @param newFileName
 * @return 0
 */
int Manage::Rename(const char* newFileName)
{
    // using rename() function to change the file name in the file system
    if (rename(fileName, newFileName) != 0)
    {
        errorNumber = errno;
        perror("Rename unsuccessful\n");
    }
    cout <<  (string)fileName + " renamed to " + newFileName << endl;
    // change the filename within the program
    fileName = newFileName;
    return 0;
}

/**
 * This removes the file from the file system
 * @return
 */
int Manage::Remove()
{
    // using unlink() function to remove the file from the file system
    if (unlink(fileName) != 0)
    {
        errorNumber = errno;
        perror("Remove unsuccessful\n");
    }
    // indicates that the file has been removed
    cout << "File " + (string)fileName + " deleted" << endl;
    return 0;
}

/**
 * This function takes another one of the file objects as a parameter and will compare the contents
 * of the file object this function was invoked upon to this other file object.
 * @param fName
 * @return true or false depends on whether if files are the same
 */
int Manage::Compare(const char* fName)
{
    fstream f1, f2;
    // flag indicates if files are the same. 1 if they're the same and 0 otherwise.
    int flag = 1;
    long blkSize = this->getBlockSize();
    // open file 1 and check
    f1.open(fileName, ios::in);
    if(f1.fail())
    {
        errorNumber = errno;
        perror("File 1 can't be opened\n");
    }
    // open file 2 and check
    f2.open(fName, ios::in);
    if(f2.fail())
    {
        errorNumber = errno;
        perror("File 2 can't be opened\n");
    }
    // make two new char arrays
    char charArr1[blkSize];
    char charArr2[blkSize];
    // load two files into the char arrays
    f1.getline(charArr1, blkSize);
    f2.getline(charArr2, blkSize);
    // check the size of two char arrays, set flag to 0 and return false if the size is different
    if (sizeof(charArr1) == sizeof(charArr2))
    {
        // if the char arrays have the same length, check character by character
        for (int i = 0; charArr1[i]!='\0'; i++) {
            cout << charArr1[i] << endl;
            cout << charArr2[i] << endl;
            // if any characters don't match between the two char arrays, set flag to 0 and return false
            if(charArr1[i] != charArr2[i])
            {
                flag = 0;
                break;
            }
        }
    } else { flag = 0; }
    if (flag == 0)
    {
        cout << fileName << " has different content with " << fName << endl;
        return false;
    }
    cout << fileName << " as the same content with " << fName << endl;
    return true;
}

/**
 * This function operates on directories only and is used to fill in the children of the file object this
 * function was invoked upon.
 * @return
 */
int Manage::Expand()
{
    // check if it's a directory
    if (!S_ISDIR(fileType))
    {
        errorNumber = errno;
        perror("Not a directory\n");
    }// else
    // make new DIR object
    DIR *dir = opendir(fileName);
    if (dir == nullptr)
    {
        errorNumber = errno;
        perror("Directory is empty\n");
    }
    struct dirent *content = readdir(dir);
    // making a complete file path
    while (content != nullptr)
    {
        string filePath = content->d_name;
        string slash = "/";
        string dirPath = fileName;
        dirPath += slash += fileName;
        Manage exManage (filePath.c_str());
        children.push_back(exManage);
        content = readdir(dir);
    }
    closedir(dir);
    return 0;
}

/**
 * Getter
 * @return fileName
 */
const char* Manage::getFileName() { return fileName; }

/**
 * Setter
 * @param name
 */
void Manage::setFileName(const char* name) { fileName = name; }

/**
 * Getter. This will print out the file type, for example, a.txt will get "txt" as an output
 * @return 0
 */
string Manage::getFileType()
{
    string fn = fileName;
    size_t i = fn.rfind('.', fn.length());
    if (i != string::npos) {
        return(fn.substr(i+1, fn.length() - i));
    }
    return 0;
}

/**
 * Getter
 * @return fileSize
 */
long long Manage::getFileSize() { return fileSize; }

/**
 * Getter
 * @return userID
 */
uid_t Manage::getUserID() { return userID; }

/**
 * Getter
 * @return userName
 */
std::string Manage::getUserName() { return userName; }

/**
 * Getter
 * @return groupID
 */
gid_t Manage::getGroupID() { return groupID; }

/**
 * Getter
 * @return groupName
 */
std::string Manage::getGroupName() { return groupName; }

/**
 * Getter for permission
 * @return modeArr
 */
char* Manage::getPermission()
{
    struct stat st;
    char* modeArr = new char[11];
    // converting from int to characters
    if(stat(fileName, &st) == 0){
        mode_t mode = st.st_mode;
        modeArr[0] = (S_ISDIR(mode)) ? 'r' : '-';
        modeArr[1] = (mode & S_IRUSR) ? 'r' : '-';
        modeArr[2] = (mode & S_IWUSR) ? 'w' : '-';
        modeArr[3] = (mode & S_IXUSR) ? 'x' : '-';
        modeArr[4] = (mode & S_IRGRP) ? 'r' : '-';
        modeArr[5] = (mode & S_IWGRP) ? 'w' : '-';
        modeArr[6] = (mode & S_IXGRP) ? 'x' : '-';
        modeArr[7] = (mode & S_IROTH) ? 'r' : '-';
        modeArr[8] = (mode & S_IWOTH) ? 'w' : '-';
        modeArr[9] = (mode & S_IXOTH) ? 'x' : '-';
        modeArr[10] = '\0';
    }
    return modeArr;
}

/**
 * Getter
 * @return accessTime
 */
char* Manage::getAccessTime() { return accessTime; }

/**
 * Getter
 * @return modificationTime
 */
char* Manage::getModificationTime() { return modificationTime; }

/**
 * Getter
 * @return statusChangeTime
 */
char* Manage::getStatusChangeTime() { return statusChangeTime; }

/**
 * Getter
 * @return blockSize
 */
long Manage::getBlockSize() { return blockSize; }

/**
 * Getter
 * @return errorNumber
 */
int Manage::getErrorNumber() { return errorNumber; }

/**
 * Getter
 * @return children
 */
vector <Manage> Manage::getChildren() { return children; }

;