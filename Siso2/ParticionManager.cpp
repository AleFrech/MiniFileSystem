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
    string partitionName="";
    cin>>partitionName;
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
    CreateFile(partitionName,ParticionSize);
    WriteSize(partitionName,ParticionSize);
    bitMap = new BitMap();
    bitMap->InitMap(ParticionSize);
    WriteBitMap(partitionName,bitMap);
    directory = new Directory();
    FileAttributes fileattr;
    fileattr.Date=1994;
    strcpy(fileattr.FileName,string("paco.txt").c_str());
    fileattr.FileSize=14;
    fileattr.FirstBlockPointer=NULL;
    directory->DirectoryEntries[0]= fileattr;
    WriteDirectory(partitionName,directory);
}


ParticionManager* ParticionManager::LoadParticion() {
    string name;
    cout<<"Ingrese nombre de la Particion a cargar"<<endl;
    cin>>name;
    auto tmpPartition=new ParticionManager;
    tmpPartition->ParticionSize=ReadSize(name);
    cout<<tmpPartition->ParticionSize<<endl;
    tmpPartition->bitMap=new BitMap(ReadBitMap(name));
    if(tmpPartition->bitMap->Get(0)==31){
        cout<<"Successfully Loaded BitMap\n";
    }
    tmpPartition->directory= new Directory(ReadDirectory(name));
    cout<<tmpPartition->directory->DirectoryEntries[0].FileName<<endl;
    cout<<tmpPartition->directory->DirectoryEntries[0].FileSize<<endl;
    cout<<tmpPartition->directory->DirectoryEntries[0].Date<<endl;
    if(tmpPartition->directory->DirectoryEntries[0].FirstBlockPointer==NULL)
        cout<<"solo falta el pointer papa"<<endl;
    return tmpPartition;
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


