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
 * make a copy of a file from a source to a destination named as parameters to the command,
 * and the dump method from above should work nicely for this on its own
 * @param argc
 * @param argv
 * @return 0
 */
int main (int argc, char* argv[])
{
    if (argc < 3) {
        printf("ERROR: You need at least 3 argument.\n");
        exit(0);
    }
    // source
    ofstream fileStreamIn (argv[2]);
    Manage destination (argv[1]);
    destination.Dump(fileStreamIn);
    return 0;
};