//
// Created by John Chen on 2019-09-24.
//

#define ASN1_MANAGE_H
#include <iostream>
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
#include "Manage.h"

using namespace std;

/**
 * outputs all of the information on the file named as a parameter to this command.
 * @param argc
 * @param argv
 * @return 0
 */
int main (int argc, char* argv[])
{
    Manage manage (argv[1]);
    cout << "------------S-T-A-T------------\n\n";
    cout << "File Name: " << manage.getFileName() << endl;
    cout << "File Type: " << manage.getFileType() << endl;
    cout << "File Size: " << manage.getFileSize() << endl;
    cout << "User ID: " << manage.getUserID() << endl;
    cout << "User Name: " << manage.getUserName() << endl;
    cout << "Group ID: " << manage.getGroupID() << endl;
    cout << "Group Name: " << manage.getGroupName() << endl;
    cout << "Permission: " << manage.getPermission() << endl;
    cout << "Access Time: " << manage.getAccessTime();
    cout << "Modification Time: " << manage.getModificationTime();
    cout << "Status Change Time: " << manage.getStatusChangeTime();
    return 0;
}