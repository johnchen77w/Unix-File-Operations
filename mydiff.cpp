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
 * compares two files named as parameters to this command with one another
 * and reports if they are the same or different.
 * @param argc
 * @param argv
 * @return 0
 */
int main (int argc, char* argv[])
{
    Manage diffManage (argv[1]);
    // Compare() handles everything
    diffManage.Compare(argv[2]);
    return 0;
}