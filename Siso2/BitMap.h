//
// Created by alejandrofrech on 08-22-16.
//
#ifndef SISO2_BITMAP_H
#define SISO2_BITMAP_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include "Block.h"

using namespace std;
class BitMap{
public:
    int Size;
    unsigned char Buffer[4092];
    BitMap();
    unsigned char Get(int pos);
    int GetNextFreeSpace();
    void FreeBlock(int positionBlock);
    int GetCharPosition(unsigned char value);
    void InitMap(int size);
private:
    unsigned char SetOccupiedToFree(unsigned char value,int bitPos);
    unsigned char SetFreeToOccupied(int pos, int bitPos);

};


#endif //SISO2_BITMAP_H
