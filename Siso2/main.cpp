#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "BitMap.h"

using namespace std;



vector<string> Split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}


int CreateParticion(){
    cout << "Ingresar Nombre de la Particion\n" << endl;
    string partitionName="";
    cin>>partitionName;
    cout << "Ingresar Tamano de la Particion GB o MB\n" << endl;
    string particion="";
    string sizeFilter="";
    cin>>particion;
    cin>>sizeFilter;
    int particionSize=stoi(particion);
    int bytesSize=0;
    ofstream file;
    if(sizeFilter=="GB"){
        bytesSize=particionSize*1024*1024*1024;
        file.open(partitionName+".bd",std::ofstream::out |std::ofstream::app);

    }else{
        bytesSize=particionSize*1024*1024;
        file.open(partitionName+".bd",std::ofstream::out |std::ofstream::app );
    }


    file.close();
    return bytesSize;

}
int main() {
    BitMap *bitMap = new BitMap();
    bitMap->InitMap();
    int maxSize = CreateParticion();
    return 0;
}



























