#include <iostream>
#include <cstring>
#include <tuple>
#include "ParticionManager.h"
using namespace std;

std::tuple<char*, char*,char*> GetBothParameters(char* buffer){
    return  std::make_tuple(strtok(buffer," "),strtok(NULL," "),strtok(NULL," "));
}

int main() {
    ParticionManager *currentParticion = new ParticionManager();
    while (1) {
        char buffer[100];
        cout<<("cmd:>");
        cin.getline(buffer,sizeof(buffer));
        auto t=GetBothParameters(buffer);
        char*command=get<0>(t);
        if(strcmp(command,string("create_block").c_str())==0){
            currentParticion->CreateParticion(get<1>(t),get<2>(t));
        }else if(strcmp(command,string("mount").c_str())==0){
            auto x= currentParticion->LoadParticion(get<1>(t));
            if(x!=NULL)
                currentParticion=x;
        }else if(strcmp(command,string("umount").c_str())==0) {
            currentParticion = new ParticionManager();
        }else if(strcmp(command,string("empty").c_str())==0) {
            currentParticion->CreateEmptyFile(get<1>(t));
        }else if(strcmp(command,string("ls").c_str())==0) {
            currentParticion->ListFiles();
        }else if(strcmp(command,string("rename").c_str())==0){
            currentParticion->RenameFile(get<2>(t),get<1>(t));
        }else if(strcmp(command,string("copy_from_fs").c_str())==0){
            currentParticion->Import(get<1>(t),get<2>(t));
        }else if(strcmp(command,string("delete").c_str())==0) {
            currentParticion->DeleteFile(get<1>(t));
        }else if(strcmp(command,string("delete_block").c_str())==0) {
            currentParticion->Delete(get<1>(t));
        }else if(strcmp(command,string("copy_to_fs").c_str())==0) {
            currentParticion->Export(get<1>(t),get<2>(t));
        }else{
            cout<<"Command not found\n";
        }
    }
}