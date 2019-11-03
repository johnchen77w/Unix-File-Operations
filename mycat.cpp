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
 * display the contents of all of the files given as parameters to the command to the terminal
 * @param argc
 * @param argv
 * @return 0
 */
int main (int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        const char* fileName = argv[i];
        Manage catManage(fileName);
        catManage.Dump(cout);
    }
    return 0;
}