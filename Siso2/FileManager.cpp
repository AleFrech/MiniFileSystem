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

void FileManager::DeleteFile(string name) {
    ifstream f(name.c_str());
    if(f.good()){
        remove(name.c_str());
        cout<<"Particion borrada exitosamente"<<endl;
    }else{
        cout<<"Particion No Existe"<<endl;
    }
}

string FileManager::GetFileNameFromPath(string path) {
        char sep = '/';
#ifdef _WIN32
        sep = '\\';
#endif
        size_t i = path.rfind(sep, path.length());
        if (i != string::npos) {
            return(path.substr(i+1, path.length() - i));
        }
        return("");
}

int FileManager::GetFileSize(string name) {
    ifstream file;
    file.open(name,ios::binary |ios::out|ios::in);
    std::streampos fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    return (int)fsize;
}
