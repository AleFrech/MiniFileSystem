//
// Created by alejandrofrech on 08-23-16.
//

#include "Directory.h"

Directory::Directory() {
    occupied=0;
}

void Directory::Add(FileAttributes entry) {
   DirectoryEntries[occupied]=entry;
    occupied++;
}

void Directory::ListFiles() {
    for(int i=0;i<occupied;i++){
        cout<<"Name: ";
        cout<<DirectoryEntries[i].FileName;
        cout<<" Size: ";
        cout<<DirectoryEntries[i].FileSize;
        cout<<" Date: ";
        cout<< ctime(&DirectoryEntries[i].Date)<<endl;
    }
}
