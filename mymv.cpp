//
// Created by John Chen on 2019-09-24.
//

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
 * move and rename files around
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
    char* newName = argv[2];
    Manage* manage_old = new Manage(argv[1]);
    // calling Rename() function
    manage_old->Rename(newName);
    return 0;
}

