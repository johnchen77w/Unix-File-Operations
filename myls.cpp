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
#include <string.h>
#include <unistd.h>
#include <vector>
#include "Manage.h"

using namespace std;

/**
 * list the contents of the directory and for other types of files
 * *not fully working*
 * @param argc
 * @param argv
 * @return 0
 */
int main (int argc, char* argv[])
{
    /*
     *
     */
    cerr <<"ass";
    char strArr[100];
    // basic scenario, equivilant to "ls", should list all contents of the directory
    if (argc == 1) {
        string crtDir = getcwd(strArr, sizeof(strArr));
        Manage dirManage(".");
        dirManage.Expand();
        std::vector <Manage> children = dirManage.getChildren();
        for (int i = 0; i < children.size(); ++i) {
            cout << children[i].getFileName() << endl;
        }
    }
    // scenario where multiple paramaters are used, equivilent to "ls -l" or "ls dirName"
    else if (argc == 2){
        if (strncmp(argv[2], "-l", 3))
        {

        } else
        {
            Manage mls (argv[2]);
            string type = argv[2];
            if (type.compare(mls.getFileType()))
            {
                cout << mls.getFileName() << endl;
            } else
            {
                mls.Expand();
                std::vector <Manage> children = mls.getChildren();
                for (int i = 0; i < children.size(); ++i) {
                    cout << children[i].getFileName() << endl;
                }
            }
        }
    }
    return 0;
}