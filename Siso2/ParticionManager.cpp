//
// Created by alejandrofrech on 08-24-16.
//

#include <cstring>
#include "ParticionManager.h"
#include<string>

ParticionManager::ParticionManager() {
}

void ParticionManager::CreateParticion() {

    cout << "Ingresar Nombre de la Particion\n" << endl;
    cin>>particionName;
    cout << "Ingresar Tamano de la Particion GB o MB\n" << endl;
    string particion="";
    string sizeFilter="";
    cin>>particion;
    cin>>sizeFilter;

    int size=stoi(particion);
    int ParticionSize=0;
    if(sizeFilter=="GB")
        ParticionSize=size*1024*1024*1024;
    else
        ParticionSize=size*1024*1024;
    CreateFile(particionName,ParticionSize);
    WriteSize(particionName,ParticionSize);
    bitMap = new BitMap();
    bitMap->InitMap(ParticionSize);
    WriteBitMap(particionName,bitMap);
    directory = new Directory();
    WriteDirectory(particionName,directory);
}


ParticionManager* ParticionManager::LoadParticion() {
    auto tmpPartition=new ParticionManager;
    cout<<"Ingrese nombre de la Particion a cargar"<<endl;
    cin>>tmpPartition->particionName;
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

void ParticionManager::CreateEmptyFile() {
    string Filename;
    cout<<"Ingrese nombre del archivo a crear"<<endl;
    cin>> Filename;
    FileAttributes fileattr;
    fileattr.Date=1994;
    strcpy(fileattr.FileName,string(Filename).c_str());
    fileattr.FileSize=0.0;
    fileattr.Date=time(0);
    fileattr.FirstBlockPointer=0;
    directory->Add(fileattr);
    WriteDirectory(particionName,directory);
}


void ParticionManager::WriteDirectory(string partitionName, Directory *directory) {
    Write(partitionName,reinterpret_cast<char*>( directory ),sizeof(Directory),4096*2);
}

void ParticionManager::WriteBlock(string partitionName, Block *block, int position) {
    Write(partitionName,reinterpret_cast<char*>( block ),sizeof(Block),position);
}

void ParticionManager::WriteSize(string partitionName,int size) {
    Write(partitionName,reinterpret_cast<char*>( &size ),sizeof(size),0);
}

void ParticionManager::WriteBitMap(string partitionName, BitMap *bitmap) {
    Write(partitionName,reinterpret_cast<char*>( bitmap ),sizeof(BitMap),4096);
}

int ParticionManager::ReadSize(string name) {
    int size;
    Read(name,reinterpret_cast<char*>( &size), sizeof(size),0);
    return size;
}


Directory ParticionManager::ReadDirectory(string name) {
    Directory directory;
    Read(name,reinterpret_cast<char*>(&directory), sizeof(directory),4096*2);
    return directory;
}


BitMap ParticionManager::ReadBitMap(string name) {
    BitMap bitmap;
    Read(name,reinterpret_cast<char*>(&bitmap), sizeof(BitMap),4096);
    return bitmap;
}


Block ParticionManager::ReadBlock(string name, int position) {
    Block block;
    Read(name,reinterpret_cast<char*>(&block), sizeof(Block),position);
    return block;
}

void ParticionManager::CreateFile(string name, int size) {
    ofstream file;
    file.open(name,ios::binary |ios::out);
    file.seekp(size - 1);
    file.write(" ", 1);
    file.close();
}


void ParticionManager::Read(string name,char *buffer, int size,int pos) {
    fstream file;
    file.open(name,ios::binary |ios::out|ios::in);
    file.seekg(pos);
    file.read(buffer,size);
    file.close();
}

void ParticionManager::Write(string name,char *buffer, int size,int pos) {
    fstream file;
    file.open(name,ios::binary |ios::out|ios::in);
    file.seekg(pos);
    file.write(buffer,size);
    file.close();
}

void ParticionManager::ListFiles() {
    directory->ListFiles();
}



