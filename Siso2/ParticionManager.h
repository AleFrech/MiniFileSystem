//
// Created by alejandrofrech on 08-24-16.
//

#ifndef SISO2_PARTICIONMANAGER_H
#define SISO2_PARTICIONMANAGER_H


#include "BitMap.h"
#include <string>

class ParticionManager {
private:
    BitMap *bitMap;
public:
    ParticionManager();
    int ParticionSize;
    void CreateParticion();
    void LoadParticion(string name);
private:
    void CreateFile(string name, int size);
    Block * ReadBlock(string name, int position);
    BitMap* ReadBitMap(string name);
    int ReadSize(string name);
    void WriteBlock(string partitionName,Block * block,int position);
    void WriteSize(string partitionName,int size);
    void WriteBitMap(string partitionName, BitMap *bitmap);
    void Read(string name,char *buffer, int size,int pos);
    void Write(string name,char *buffer, int size,int pos);

};


#endif //SISO2_PARTICIONMANAGER_H
