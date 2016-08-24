//
// Created by alejandrofrech on 08-22-16.
//

#include "BitMap.h"


int BitMap::GetNextFreeSpace() {
    for(int i=0;i<MapSize;i++){
        if(Map->at(i)!=0) {
            for(int n=8;n>=0;n--){
                if(Map->at(i) & 1<<n){
                    return n;
                }
            }
        }
    }
    return -1;
}

void BitMap::InitMap() {
    for(int i=0;i<MapSize;i++){
        if(i==0)
            Map->push_back(63);
        else
            Map->push_back(255);
    }
}

unsigned char BitMap::SetOccupiedToFree(unsigned char value, int pos) {
    int CharPositionInMap=GetCharPosition(value);

    unsigned char tmpChar=Map->at(CharPositionInMap);
    Map->at(CharPositionInMap)=(tmpChar |= 1 << pos);
    return Map->at(CharPositionInMap);
}

unsigned char BitMap::SetFreeToOcuppied(unsigned char value, int pos){
    int CharPositionInMap=GetCharPosition(value);

    unsigned char tmpChar=Map->at(CharPositionInMap);
    Map->at(CharPositionInMap)=(tmpChar &= ~(1<<pos));
    return Map->at(CharPositionInMap);
}

int BitMap::GetCharPosition(unsigned char value) {
    for(int i=0;i<MapSize;i++){
        if(Map->at(i)==value){
            return i;
        }
    }
    return -1;
}

BitMap::BitMap() {
    Map= new vector<unsigned char>;
}
