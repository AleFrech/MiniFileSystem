//
// Created by alejandrofrech on 08-24-16.
//

#ifndef SISO2_PARTICIONMANAGER_H
#define SISO2_PARTICIONMANAGER_H


#include "BitMap.h"
#include "Directory.h"
#include "FileManager.h"
#include <string>

class ParticionManager {
private:
    BitMap *bitMap;
    Directory * directory;
    FileManager * fileManager;
public:
    ParticionManager();
    string particionName;
    int ParticionSize;
    void Export(char * fileName,char * destinationPath);
    void CreateParticion(char* name,char* size);
    void RenameFile(char* name,char * newName);
    void DeleteFile(char * name);
    void Delete(char * name);
    ParticionManager* LoadParticion(char * name);
    void CreateEmptyFile(char* name);
    void ListFiles();
    void Import(char *filePath);
private:
    Block  ReadBlock(string name, int position);
    BitMap ReadBitMap(string name);
    Directory  ReadDirectory(string name);
    int ReadSize(string name);
    void WriteDirectory(string partitionName,Directory * directory);
    void WriteBlock(string partitionName,Block * block,int position);
    void WriteSize(string partitionName,int size);
    void WriteBitMap(string partitionName, BitMap *bitmap);
    void ImportFile(string filePath);


};


#endif //SISO2_PARTICIONMANAGER_H
