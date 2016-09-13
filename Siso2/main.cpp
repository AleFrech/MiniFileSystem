#include <iostream>
#include <cstring>
#include "ParticionManager.h"

using namespace std;

int strcmp(char *str1,char*str2){
    int i;
    for(i=0; i <30; i++){
        if(str1[i]!='\0' && str2[i]!='\0'){
            if(str1[i] != str2[i]){
                return 0;
            }
        }else{
            if(str1[i]!=str2[i])
                return 0;
            return 1;
        }
    }
}



int splitBufferCommand(char* buffer,char * command){
    int offset=0;
    while(offset<30){
        if(buffer[offset]==' ' || buffer[offset]=='\n'){
            command[offset] = '\0';
            offset++;
            break;
        }else{
            command[offset]=buffer[offset];
            offset++;
        }
    }
    return offset;
}

int main() {
    ParticionManager *currentParticion = new ParticionManager();
    while (1) {

        char buffer[100];
        cout<<("cmd:>");
        cin.getline(buffer,sizeof(buffer));
        char command[30];
        int offset = splitBufferCommand(buffer,command);
        if(strcmp((char *) "create_block", command)){
            char *name= strtok((buffer+offset)," ");
            char *size = strtok(NULL," ");
            currentParticion->CreateParticion(name,size);
        }else if(strcmp((char *) "mount", command)) {
            auto x= currentParticion->LoadParticion(buffer+offset);
            if(x!=NULL)
                currentParticion=x;
        }else if(strcmp((char *) "umount", command)) {
            currentParticion = new ParticionManager();
        }else if(strcmp((char *) "empty", command)) {
            currentParticion->CreateEmptyFile(buffer+offset);
        }else if(strcmp((char *) "ls", command)) {
            currentParticion->ListFiles();
        }else if(strcmp((char *) "rename", command)){
            char *name= strtok((buffer+offset)," ");
            char *newName = strtok(NULL," ");
            currentParticion->RenameFile(newName,name);
        }else if(strcmp((char *) "copy_from_fs", command)){
            char *path= strtok((buffer+offset)," ");
            char *file = strtok(NULL," ");
            currentParticion->Import(path,file);
        }else if(strcmp((char *) "delete", command)) {
            currentParticion->DeleteFile(buffer+offset);
        }else if(strcmp((char *) "delete_block", command)) {
            currentParticion->Delete(buffer+offset);
        }else if(strcmp((char *) "copy_to_fs", command)) {
            char *name= strtok((buffer+offset)," ");
            char *path = strtok(NULL," ");
            currentParticion->Export(name,path);
        }else{
            cout<<"Command not found\n";
        }
    }
}


