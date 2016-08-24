//
// Created by alejandrofrech on 08-22-16.
//
#ifndef SISO2_BITMAP_H
#define SISO2_BITMAP_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class BitMap {
public:
    vector<unsigned char> *Map;
    BitMap();
    unsigned char SetOccupiedToFree(unsigned char value,int pos);
    unsigned char SetFreeToOcuppied(unsigned char value,int pos);
    int GetNextFreeSpace();
    int GetCharPosition(unsigned char value);
    void InitMap();
private:
    int MapSize=128;
};


#endif //SISO2_BITMAP_H
