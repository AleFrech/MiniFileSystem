//
// Created by alejandrofrech on 08-24-16.
//

#ifndef SISO2_PARTICIONMANAGER_H
#define SISO2_PARTICIONMANAGER_H


#include "BitMap.h"
#include "Directory.h"
#include <string>

class ParticionManager {
private:
    BitMap *bitMap;
    Directory * directory;
public:
    ParticionManager();
    string particionName;
    int ParticionSize;
    void CreateParticion();
    ParticionManager* LoadParticion();
    void CreateFile(string name, int size);
    void CreateEmptyFile();
    void ListFiles();
private:
    Block  ReadBlock(string name, int position);
    BitMap ReadBitMap(string name);
    Directory  ReadDirectory(string name);
    int ReadSize(string name);
    void WriteDirectory(string partitionName,Directory * directory);
    void WriteBlock(string partitionName,Block * block,int position);
    void WriteSize(string partitionName,int size);
    void WriteBitMap(string partitionName, BitMap *bitmap);
    void Read(string name,char *buffer, int size,int pos);
    void Write(string name,char *buffer, int size,int pos);

};


#endif //SISO2_PARTICIONMANAGER_H
