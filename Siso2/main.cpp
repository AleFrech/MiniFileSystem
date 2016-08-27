#include <iostream>
#include "ParticionManager.h"

using namespace std;



int main() {
    ParticionManager *currentParticion = new ParticionManager();
    while(true) {
        string x;
        cin >> x;
        if (x == "Create") {
            currentParticion->CreateParticion();
        }else if(x== "Load"){
            string name;
            cout<<"Ingrese nombre de la Particion a cargar"<<endl;
            cin>>name;
            currentParticion->LoadParticion(name);
        }else{
            break;
        }
    }
    return 0;
}
