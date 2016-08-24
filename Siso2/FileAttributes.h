//
// Created by alejandrofrech on 08-23-16.
//

#ifndef SISO2_FILEATTRIBUTES_H
#define SISO2_FILEATTRIBUTES_H


class FileAttributes {
public:
    char FileName[8];
    double FileSize;
    double Date;
    int* FirstBlockPointer;

};


#endif //SISO2_FILEATTRIBUTES_H
