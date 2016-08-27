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
#include "Block.h"

using namespace std;


class Directory :Block {
public:
    Directory();
    FileAttributes DirectoryEntries[128];
};


#endif //SISO2_DIRECTORY_H
