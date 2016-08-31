//
// Created by alejandrofrech on 08-30-16.
//

#include "FileManager.h"


void FileManager::CreateFile(string name, int size) {
    ofstream file;
    file.open(name,ios::binary |ios::out);
    file.seekp(size - 1);
    file.write(" ", 1);
    file.close();
}


void FileManager::Read(string name,char *buffer, int size,int pos) {
    fstream file;
    file.open(name,ios::binary |ios::out|ios::in);
    file.seekg(pos);
    file.read(buffer,size);
    file.close();
}

void FileManager::Write(string name,char *buffer, int size,int pos) {
    fstream file;
    file.open(name,ios::binary |ios::out|ios::in);
    file.seekg(pos);
    file.write(buffer,size);
    file.close();
}