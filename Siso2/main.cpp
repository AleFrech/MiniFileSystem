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
        if(strcmp((char *) "Create", command)){
            char *name= strtok((buffer+offset)," ");
            char *size = strtok(NULL," ");
            currentParticion->CreateParticion(name,size);
        }else if(strcmp((char *) "Load", command)) {
            currentParticion = currentParticion->LoadParticion(buffer+offset);
        }else if(strcmp((char *) "Unmount", command)) {
            currentParticion = NULL;
        }else if(strcmp((char *) "CreateEmpty", command)) {
            currentParticion->CreateEmptyFile(buffer+offset);
        }else if(strcmp((char *) "ls", command)) {
            currentParticion->ListFiles();
        }else{
            cout<<"Command not found\n";
        }
    }
}


