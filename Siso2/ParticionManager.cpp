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
    auto ParticionSize=0;
    if(sizeFilter=="GB")
        ParticionSize=size*1024*1024*1024;
    else
        ParticionSize=size*1024*1024;
    bitMap = new BitMap();
    bitMap->InitMap(ParticionSize);
    CreateFile(partitionName,ParticionSize);
    //WriteSize(partitionName,ParticionSize);
    //WriteBitMap(partitionName,bitMap);
}


void ParticionManager::LoadParticion(string name) {
    ParticionSize=ReadSize(name);
    cout<<ParticionSize<<endl;
    auto bitmap=ReadBitMap(name);
    cout<<bitmap->Get(0)<<endl;
    cout<<bitmap->Get(1)<<endl;
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

BitMap *ParticionManager::ReadBitMap(string name) {
    BitMap* bitmap;
    Read(name,reinterpret_cast<char*>(bitmap), sizeof(BitMap),4096);
    return bitmap;
}


Block *ParticionManager::ReadBlock(string name, int position) {
    Block* block;
    Read(name,reinterpret_cast<char*>(block), sizeof(Block),position);
    return block;
}


void ParticionManager::CreateFile(string name, int size) {
    ofstream file;
    file.open(name+".bd",ios::binary |ios::out);
    file.seekp(size - 1);
    file.write(" ", 1);
    file.close();
}


void ParticionManager::Read(string name,char *buffer, int size,int pos) {
    fstream file;
    file.open(name+".bd",ios::binary |ios::out|ios::in);
    file.seekg(pos);
    file.read(buffer,size);
    file.close();
}

void ParticionManager::Write(string name,char *buffer, int size,int pos) {
    fstream file;
    file.open(name+".bd",ios::binary |ios::out|ios::in);
    file.seekg(pos);
    file.write(buffer,size);
    file.close();
}