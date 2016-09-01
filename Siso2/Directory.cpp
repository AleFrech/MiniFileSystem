//
// Created by alejandrofrech on 08-23-16.
//

#include <cstring>
#include "Directory.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotAssignable"
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

Directory::Directory() {
 occupied=0;
}

void Directory::RenameFile(char *name, char *newName) {
    for(int i=0;i<occupied;i++){
        if(strcmp(DirectoryEntries[i].FileName,name)==0){
            strcpy(DirectoryEntries[i].FileName,string(newName).c_str());
        }
    }
}

void Directory::DeleteEntry(char *name) {
    for(int i=0;i<occupied;i++){
        if(strcmp(DirectoryEntries[i].FileName,name)==0){
            DirectoryEntries[i]=FileAttributes();
            occupied--;
        }
    }

}

#pragma clang diagnostic pop