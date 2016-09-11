//
// Created by alejandrofrech on 08-22-16.
//

#include <cstring>
#include "BitMap.h"


int BitMap::GetNextFreeSpace() {
    for(int i=0;i<Size;i++){
        if(Buffer[i]!=0) {
            unsigned int auxBit=128;
            for(int n=1;n<=8;n++){
                    // pos=(numero de bits por palabra) x (palabras con valor 0) + (posición del primer bit en 1).
                    int tmp=Buffer[i] & auxBit;
                    if(tmp>0) {
                        SetFreeToOcuppied(Buffer[i], n);
                        return (8 * i) + n;
                    }else {
                        auxBit /= 2;
                    }
                }
        }
    }
    return -1;
}

void BitMap::InitMap(int size) {
    Size=(size/1024/4)/8;
    if(Size>4092)
        Size=4092;

    for(int i=0;i<Size;i++) {
        if (i == 0)
            Buffer[i] = 31;
        else
            Buffer[i] = 255;
    }
}

unsigned char BitMap::SetOccupiedToFree(unsigned char value, int bitPos) {
    int CharPositionInMap=GetCharPosition(value);
    unsigned char tmpChar=Buffer[CharPositionInMap];
    Buffer[CharPositionInMap]=(tmpChar |= 1 << bitPos);
    return Buffer[CharPositionInMap];
}

unsigned char BitMap::SetFreeToOcuppied(unsigned char value, int bitPos){
    int CharPositionInMap=GetCharPosition(value);
    unsigned char tmpChar=Buffer[CharPositionInMap];
    Buffer[CharPositionInMap]=(tmpChar &= ~(1<<bitPos));
    return Buffer[CharPositionInMap];
}

int BitMap::GetCharPosition(unsigned char value) {
    for(int i=0;i<Size;i++){
        if(Buffer[i]==value){
            return i;
        }
    }
    return -1;
}

BitMap::BitMap() {
    Size=0;
}

unsigned char BitMap::Get(int pos) {
    return Buffer[pos];
}

void BitMap::FreeBlock(int positionBlock) {
    auto tmpchar = Get(positionBlock/8);
    auto bitpos = positionBlock%8;
    SetOccupiedToFree(tmpchar,bitpos);
}

