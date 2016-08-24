//
// Created by alejandrofrech on 08-23-16.
//

#ifndef SISO2_DIRECTORY_H
#define SISO2_DIRECTORY_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "FileAttributes.h"
using namespace std;


class Directory {
public:
    Directory();
    vector<FileAttributes>*DirectoryEntries;
private:
    int DirectorySize=4096;
};


#endif //SISO2_DIRECTORY_H
