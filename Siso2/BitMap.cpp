//
// Created by alejandrofrech on 08-22-16.
//

#include <cstring>
#include "BitMap.h"


int BitMap::GetNextFreeSpace() {
    for(int i=0;i<Size;i++){
        if(Buffer[i]!=0) {
            for(int n=8;n>=0;n--){
                if(Buffer[i] & 1<<n){
                    return n;
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

    for(int i=0;i<Size;i++){
        if(i==0)
            Buffer[i]=31;
        else
            Buffer[i]=255;
    }
}

unsigned char BitMap::SetOccupiedToFree(unsigned char value, int pos) {
    int CharPositionInMap=GetCharPosition(value);

    unsigned char tmpChar=Buffer[CharPositionInMap];
    Buffer[CharPositionInMap]=(tmpChar |= 1 << pos);
    return Buffer[CharPositionInMap];
}

unsigned char BitMap::SetFreeToOcuppied(unsigned char value, int pos){
    int CharPositionInMap=GetCharPosition(value);

    unsigned char tmpChar=Buffer[CharPositionInMap];
    Buffer[CharPositionInMap]=(tmpChar &= ~(1<<pos));
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

