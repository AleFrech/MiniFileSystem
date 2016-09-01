//
// Created by alejandrofrech on 08-30-16.
//

#ifndef SISO2_FILEMANAGER_H
#define SISO2_FILEMANAGER_H

#include "BitMap.h"

class FileManager {
public:
    void CreateFile(string name, int size);
    void Read(string name,char *buffer, int size,int pos);
    void Write(string name,char *buffer, int size,int pos);

};


#endif //SISO2_FILEMANAGER_H