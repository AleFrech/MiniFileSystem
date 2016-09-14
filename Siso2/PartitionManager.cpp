//
// Created by alejandrofrech on 08-24-16.
//

#include <cstring>
#include "PartitionManager.h"

PartitionManager::PartitionManager() {
    fileManager= new FileManager();
}

void PartitionManager::CreatePartition(char *name, char *partitionSize) {
    ifstream f(name);
    if(f.good()){
        cout<<"La Particion Ya Existe"<<endl;
        return;
    }
    PartitionName=string(name);
    int size=stoi(strtok(partitionSize," "));
    int ParticionSize=0;
    char * filterSize=strtok(NULL," ");
    if(filterSize=="GB")
        ParticionSize=size*1024*1024*1024;
    else
        ParticionSize=size*1024*1024;
    fileManager->CreateFile(PartitionName,ParticionSize);
    WriteSize(PartitionName,ParticionSize);
    bitMap = new BitMap();
    bitMap->InitMap(ParticionSize);
    WriteBitMap(PartitionName,bitMap);
    directory = new Directory();
    WriteDirectory(PartitionName,directory);
}


PartitionManager* PartitionManager::LoadPartition(char *name) {
    ifstream f(name);
    if(f.good()){
        auto tmpPartition=new PartitionManager;
        tmpPartition->PartitionName=string(name);
        tmpPartition->PartitionSize=ReadSize(tmpPartition->PartitionName);
        cout<<tmpPartition->PartitionSize<<endl;
        tmpPartition->bitMap=new BitMap(ReadBitMap(tmpPartition->PartitionName));
        cout<<"Successfully Loaded BitMap\n";
        tmpPartition->directory= new Directory(ReadDirectory(tmpPartition->PartitionName));
        cout<<"Successfully Loaded Directory\n";
        return tmpPartition;
    }else{
        cout<<"Particion No Existe"<<endl;
        return NULL;
    }

}

void PartitionManager::CreateEmptyFile(char * name) {
    if(PartitionName==""){
        cout<<"Porfavor Montar Una Particion!!!"<<endl;
        return;
    }
    if(!directory->EntryExists(name)) {
        FileAttributes fileattr;
        strcpy(fileattr.FileName, string(name).c_str());
        fileattr.FileSize = 0.0;
        fileattr.Date = time(0);
        fileattr.FirstBlockPointer = -1;
        directory->Add(fileattr);
        WriteDirectory(PartitionName, directory);
    }else{
        cout<<"El Archivo Ya Existe!!"<<endl;
    }

}

void PartitionManager::RenameFile(char *newName, char *name) {
    if(PartitionName==""){
        cout<<"Porfavor Montar Una Particion!!!"<<endl;
        return;
    }
    directory->RenameFile(name,newName);
    WriteDirectory(PartitionName,directory);
}


void PartitionManager::WriteDirectory(string partitionName, Directory *directory) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( directory ),sizeof(Directory),4096*2);
}

void PartitionManager::WriteBlock(string partitionName, Block *block, int position) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( block ),sizeof(Block),position);
}

void PartitionManager::WriteSize(string partitionName,int size) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( &size ),sizeof(size),0);
}

void PartitionManager::WriteBitMap(string partitionName, BitMap *bitmap) {
    fileManager->Write(partitionName,reinterpret_cast<char*>( bitmap ),sizeof(BitMap),4096);
}

int PartitionManager::ReadSize(string name) {
    int size;
    fileManager->Read(name,reinterpret_cast<char*>( &size), sizeof(size),0);
    return size;
}

Directory PartitionManager::ReadDirectory(string name) {
    Directory directory;
    fileManager->Read(name,reinterpret_cast<char*>(&directory), sizeof(directory),4096*2);
    return directory;
}

BitMap PartitionManager::ReadBitMap(string name) {
    BitMap bitmap;
    fileManager->Read(name,reinterpret_cast<char*>(&bitmap), sizeof(BitMap),4096);
    return bitmap;
}

Block PartitionManager::ReadBlock(string name, int position) {
    Block block;
    fileManager->Read(name,reinterpret_cast<char*>(&block), sizeof(Block),position);
    return block;
}

void PartitionManager::ListFiles() {
    if(PartitionName==""){
        cout<<"Porfavor Montar Una Particion!!!"<<endl;
        return;
    }
    directory->ListFiles();
}

void PartitionManager::Delete(char *name) {
    fileManager->DeleteFile(name);
}

void PartitionManager::DeleteFile(char *name) {
    if(PartitionName==""){
        cout<<"Porfavor Montar Una Particion!!!"<<endl;
        return;
    }

    if(directory->EntryExists(name)) {
        auto entry=directory->GetFileEntry(name);
        if(entry.FirstBlockPointer!=-1)
            FreeBitMapEntryBlocks(entry);
        directory->DeleteEntry(name);
        WriteDirectory(PartitionName, directory);
        cout<<"Archivo Borrado Exitosamente!!"<<endl;
    }else{
        cout<<"Archivo No Existe!!"<<endl;
    }
}

void PartitionManager::FreeBitMapEntryBlocks(FileAttributes entry) {
    auto block=ReadBlock(PartitionName,entry.FirstBlockPointer*4096);
    while(block.nextBlock!=-1){
        bitMap->FreeBlock(block.Position);
        block=ReadBlock(PartitionName,block.nextBlock*4096);
    }
    bitMap->FreeBlock(block.Position);
    WriteBitMap(PartitionName,bitMap);
}

void PartitionManager::ImportFile(string filePath) {
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
        block->Position=blockpos;
        block->nextBlock=blockpos+1;
        fileManager->Read(filePath,block->Buffer,4088,offset);
        WriteBlock(PartitionName,block,blockpos*4096);
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
        block->Position=blockpos;
        block->nextBlock=-1;
        fileManager->Read(filePath,block->Buffer,size,offset);
        WriteBlock(PartitionName,block,blockpos*4096);
        offset+=size;
        file.seekg(offset);
    }
    directory->Add(fileattr);
    WriteDirectory(PartitionName,directory);
    WriteBitMap(PartitionName,bitMap);
}

void PartitionManager::ExportFile(char* name,char * path) {


    auto fileEntry=directory->GetFileEntry(name);
    if(fileEntry.FirstBlockPointer==-1)
        return;
    int offset=0;
    double size=fileEntry.FileSize;
    string p=string(path)+"/"+string(fileEntry.FileName);
    ofstream file(p.c_str(),ios::binary |ios::out);
    file.seekp(offset);
    auto block=ReadBlock(PartitionName,fileEntry.FirstBlockPointer*4096);
    while(size>4088){
        file.write(block.Buffer, sizeof(block.Buffer));
        offset+=4088;
        size-=4088;
        block=ReadBlock(PartitionName,block.nextBlock*4096);
        file.seekp(offset);
    }
    if(size!=0){
        file.write(block.Buffer,size);
        offset+=size;
    }
    file.close();
}

void PartitionManager::Import(char * path,char *file) {
    if(PartitionName==""){
        cout<<"Porfavor Montar Una Particion!!!"<<endl;
        return;
    }
    string filepath=string(path)+"/"+string(file);
    ImportFile(filepath);
}

void PartitionManager::Export(char *fileName,char * path) {
    if(PartitionName==""){
        cout<<"Porfavor Montar Una Particion!!!"<<endl;
        return;
    }
    ExportFile(fileName,path);
}








