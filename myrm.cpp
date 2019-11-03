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
 * removes the given files listed as parameters to this command.
 * @param argc
 * @param argv
 * @return 0
 */
int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("ERROR: You need at least one argument.\n");
        exit(0);
    }
    // handle multiple file marameters, equivalent to "rm file1 file2 file3 ..."
    for (int i = 1; i < argc; ++i)
    {
        Manage manage (argv[i]);
        manage.Remove();
    }
    return 0;
}