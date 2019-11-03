//
// Created by John Chen on 2019-09-23.
//
#ifndef ASN1_MANAGE_H
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
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>


class Manage
{
private:
    const char* fileName;
    unsigned long fileType;
    long long fileSize;
    uid_t userID;
    std::string userName;
    gid_t groupID;
    std::string groupName;
    mode_t permissions;
    char* accessTime;
    char* modificationTime;
    char* statusChangeTime;
    long blockSize;
    int errorNumber;
    std::vector <Manage> children;

public:
    /*
     * Operation Functions
     */
    Manage(const char* fName);
    ~Manage();
    int Dump(std::ostream &fileStream);
    int Rename(const char* newFileName);
    int Remove();
    int Compare(const char* fName);
    int Expand();

    /*
     * Getter methods
     */
    const char* getFileName();
    void setFileName(const char* name);
    std::string getFileType();
    long long getFileSize();
    uid_t getUserID();
    std::string getUserName();
    gid_t getGroupID();
    std::string getGroupName();
    char* getPermission();
    char* getAccessTime();
    char* getModificationTime();
    char* getStatusChangeTime();
    long getBlockSize();
    int getErrorNumber();
    std::vector <Manage> getChildren();
};

#endif
