//
// Created by alejandrofrech on 08-24-16.
//

#include <cstring>
#include "ParticionManager.h"

ParticionManager::ParticionManager() {
    fileManager= new FileManager();
}

void ParticionManager::CreateParticion(char * name,char* partitionSize) {
    particionName=string(name);
    int size=stoi(strtok(partitionSize," "));
    int ParticionSize=0;
    char * filterSize=strtok(NULL," ");
    if(filterSize=="GB")
        ParticionSize=size*1024*1024*1024;
    else
        ParticionSize=size*1024*1024;
    fileManager->CreateFile(particionName,ParticionSize);
    WriteSize(particionName,ParticionSize);
    bitMap = new BitMap();
    bitMap->InitMap(ParticionSize);
    WriteBitMap(particionName,bitMap);
    directory = new Directory();
    WriteDirectory(particionName,directory);
}


ParticionManager* ParticionManager::LoadParticion(char * name) {
    auto tmpPartition=new ParticionManager;
    tmpPartition->particionName=string(name);
    tmpPartition->ParticionSize=ReadSize(tmpPartition->particionName);
    cout<<tmpPartition->ParticionSize<<endl;
    tmpPartition->bitMap=new BitMap(ReadBitMap(tmpPartition->particionName));
    if(tmpPartition->bitMap->Get(0)==31){
        cout<<"Successfully Loaded BitMap\n";
    }
    tmpPartition->directory= new Directory(ReadDirectory(tmpPartition->particionName));
        cout<<"Successfully Loaded Directory\n";
    return tmpPartition;
}

void ParticionManager::CreateEmptyFile(char * name) {
    FileAttributes fileattr;
    strcpy(fileattr.FileName,string(name).c_str());
    fileattr.FileSize=0.0;
    fileattr.Date=time(0);
    fileattr.FirstBlockPointer=0;
    directory->Add(fileattr);
    WriteDirectory(particionName,directory);
}

void ParticionManager::RenameFile(char *name, char *newName) {
    directory->RenameFile(name,newName);
    WriteDirectory(particionName,directory);
}

void ParticionManager::DeleteFile(char *name) {
    directory->DeleteEntry(name);
    WriteDirectory(particionName,directory);
}


void ParticionManager::WriteDirectory(string partitionName, Directory *directory) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( directory ),sizeof(Directory),4096*2);
}

void ParticionManager::WriteBlock(string partitionName, Block *block, int position) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( block ),sizeof(Block),position);
}

void ParticionManager::WriteSize(string partitionName,int size) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( &size ),sizeof(size),0);
}

void ParticionManager::WriteBitMap(string partitionName, BitMap *bitmap) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( bitmap ),sizeof(BitMap),4096);
}

int ParticionManager::ReadSize(string name) {
    int size;
    fileManager->Read(name,reinterpret_cast<char*>( &size), sizeof(size),0);
    return size;
}


Directory ParticionManager::ReadDirectory(string name) {
    Directory directory;
    fileManager->Read(name,reinterpret_cast<char*>(&directory), sizeof(directory),4096*2);
    return directory;
}


BitMap ParticionManager::ReadBitMap(string name) {
    BitMap bitmap;
    fileManager->Read(name,reinterpret_cast<char*>(&bitmap), sizeof(BitMap),4096);
    return bitmap;
}


Block ParticionManager::ReadBlock(string name, int position) {
    Block block;
    fileManager->Read(name,reinterpret_cast<char*>(&block), sizeof(Block),position);
    return block;
}

void ParticionManager::ListFiles() {
    directory->ListFiles();
}





