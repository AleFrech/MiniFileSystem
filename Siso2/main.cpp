#include <iostream>
#include <cstring>
#include <tuple>
#include "PartitionManager.h"
using namespace std;

std::tuple<char*, char*,char*> GetBothParameters(char* buffer){
    char*p1=strtok(buffer," ");
    char*p2=strtok(NULL," ");
    char*p3=strtok(NULL," ");
    return  std::make_tuple(p1,p2,p3);
}

int main() {
    PartitionManager *partition = new PartitionManager();
    while (1) {
        char buffer[100];
        cout<<("cmd:>");
        cin.getline(buffer,sizeof(buffer));
        auto t=GetBothParameters(buffer);
        char*command=get<0>(t);
        if(strcmp(command,string("create_block").c_str())==0){
            partition->CreatePartition(get<1>(t), get<2>(t));
        }else if(strcmp(command,string("mount").c_str())==0){
            auto x= partition->LoadPartition(get<1>(t));
            if(x!=NULL)
                partition=x;
        }else if(strcmp(command,string("umount").c_str())==0) {
            partition = new PartitionManager();
        }else if(strcmp(command,string("empty").c_str())==0) {
            partition->CreateEmptyFile(get<1>(t));
        }else if(strcmp(command,string("ls").c_str())==0) {
            partition->ListFiles();
        }else if(strcmp(command,string("rename").c_str())==0){
            partition->RenameFile(get<2>(t),get<1>(t));
        }else if(strcmp(command,string("copy_from_fs").c_str())==0){
            partition->Import(get<1>(t),get<2>(t));
        }else if(strcmp(command,string("delete").c_str())==0) {
            partition->DeleteFile(get<1>(t));
        }else if(strcmp(command,string("delete_block").c_str())==0) {
            partition->Delete(get<1>(t));
        }else if(strcmp(command,string("copy_to_fs").c_str())==0) {
            partition->Export(get<1>(t),get<2>(t));
        }else{
            cout<<"Command not found\n";
        }
    }
}