//
// Created by alejandrofrech on 08-24-16.
//

#include <cstring>
#include "ParticionManager.h"

ParticionManager::ParticionManager() {
    fileManager= new FileManager();
}

void ParticionManager::CreateParticion(char * name,char* partitionSize) {
    ifstream f(name);
    if(f.good()){
        cout<<"La Particion Ya Existe"<<endl;
        return;
    }
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
    ifstream f(name);
    if(f.good()){
        auto tmpPartition=new ParticionManager;
        tmpPartition->particionName=string(name);
        tmpPartition->ParticionSize=ReadSize(tmpPartition->particionName);
        cout<<tmpPartition->ParticionSize<<endl;
        tmpPartition->bitMap=new BitMap(ReadBitMap(tmpPartition->particionName));
        cout<<"Successfully Loaded BitMap\n";
        tmpPartition->directory= new Directory(ReadDirectory(tmpPartition->particionName));
        cout<<"Successfully Loaded Directory\n";
        return tmpPartition;
    }else{
        cout<<"Particion No Existe"<<endl;
        return NULL;
    }

}

void ParticionManager::CreateEmptyFile(char * name) {
    if(!directory->EntryExists(name)) {
        FileAttributes fileattr;
        strcpy(fileattr.FileName, string(name).c_str());
        fileattr.FileSize = 0.0;
        fileattr.Date = time(0);
        fileattr.FirstBlockPointer = -1;
        directory->Add(fileattr);
        WriteDirectory(particionName, directory);
    }else{
        cout<<"El Archivo Ya Existe!!"<<endl;
    }

}

void ParticionManager::RenameFile(char *newName, char *name) {
    directory->RenameFile(name,newName);
    WriteDirectory(particionName,directory);
}

void ParticionManager::DeleteFile(char *name) {
    if(directory->EntryExists(name)) {
        directory->DeleteEntry(name);
        WriteDirectory(particionName, directory);
    }else{
        cout<<"Archivo No Existe!!"<<endl;
    }
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

void ParticionManager::Delete(char *name) {
    fileManager->DeleteFile(name);
}

void ParticionManager::ImportFile(string filePath) {
    FileAttributes fileattr;
    int size=fileManager->GetFileSize(filePath);
    strcpy(fileattr.FileName,string(fileManager->GetFileNameFromPath(filePath)).c_str());
    fileattr.FileSize=size;
    fileattr.Date=time(0);
    int firstblockpointer=bitMap->GetNextFreeSpace();
    fileattr.FirstBlockPointer=firstblockpointer;

    fstream file;
    file.open(filePath,ios::binary |ios::out|ios::in);
    int offset=0;
    file.seekg(offset);
    bool firstIteration=true;
    while(size>4088){
        Block* block= new Block();
        int blockpos;
        if(firstIteration){
            blockpos=firstblockpointer;
            firstIteration=false;
        }else
            blockpos=bitMap->GetNextFreeSpace();
        block->positon=blockpos;
        block->nextBlock=blockpos+1;
        fileManager->Read(filePath,block->Buffer,4088,offset);
        WriteBlock(particionName,block,blockpos*4096);
        size-=4088;
        offset+=4088;
        file.seekg(offset);
     }
    if(size!=0){
        Block* block= new Block();
        int blockpos;
        if(firstIteration){
            blockpos=firstblockpointer;
            firstIteration=false;
        }else
            blockpos=bitMap->GetNextFreeSpace();
        block->positon=blockpos;
        block->nextBlock=-1;
        fileManager->Read(filePath,block->Buffer,size,offset);
        WriteBlock(particionName,block,blockpos*4096);
        offset+=size;
        file.seekg(offset);
    }
    directory->Add(fileattr);
    WriteDirectory(particionName,directory);
    WriteBitMap(particionName,bitMap);
}

void ParticionManager::ExportFile(char* name,char * path) {


    auto fileEntry=directory->GetFileEntry(name);
    if(fileEntry.FirstBlockPointer==-1)
        return;
    int offset=0;
    double size=fileEntry.FileSize;
    string p=string(path)+"/"+string(fileEntry.FileName);
    ofstream file(p.c_str(),ios::binary |ios::out);
    file.seekp(offset);
    auto block=ReadBlock(particionName,fileEntry.FirstBlockPointer*4096);
    while(size>4088){
        file.write(block.Buffer, sizeof(block.Buffer));
        offset+=4088;
        size-=4088;
        block=ReadBlock(particionName,block.nextBlock*4096);
        file.seekp(offset);
    }
    if(size!=0){
        file.write(block.Buffer,size);
        offset+=size;
    }
    file.close();
}

void ParticionManager::Import(char * path,char *file) {
    string filepath=string(path)+"/"+string(file);
    ImportFile(filepath);
}

void ParticionManager::Export(char *fileName,char * path) {
    ExportFile(fileName,path);
}







