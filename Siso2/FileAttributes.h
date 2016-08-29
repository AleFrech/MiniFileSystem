//
// Created by alejandrofrech on 08-23-16.
//

#ifndef SISO2_FILEATTRIBUTES_H
#define SISO2_FILEATTRIBUTES_H


#include <ctime>

class FileAttributes {
public:
    char FileName[12];
    double FileSize;
    time_t Date;
    int FirstBlockPointer;

};


#endif //SISO2_FILEATTRIBUTES_H
