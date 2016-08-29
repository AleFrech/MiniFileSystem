#include <iostream>
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

        char buffer[30];
        cout<<("cmd:>");
        cin>>buffer;
        char command[30];
        int offset = splitBufferCommand(buffer,command);
        if(strcmp("Create",command)){
            currentParticion->CreateParticion();
        }else if(strcmp("Load",command)) {
            currentParticion = currentParticion->LoadParticion();
        }else if(strcmp("CreateEmpty",command)) {
            currentParticion->CreateEmptyFile();
        }else if(strcmp("ls",command)) {
            currentParticion->ListFiles();
        }else{
            cout<<"Command not found\n";
        }
    }
}


