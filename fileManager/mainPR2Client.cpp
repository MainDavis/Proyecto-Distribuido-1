#include <iostream>
#include "filemanager_stub.h"

int main(int argc,char** argv)
{
    filemanager_stub *fm=new filemanager_stub();
    char* command = new char[25];
    char* filename = new char[25];
    vector<string*>* vListFiles =  fm->listFiles();

    /*
    LS -> listFiles
    READFILE -> Download
    WRITEFILE -> Upload
    */

    do{
        cin >> command;
        if(strcmp(command, "ls") == 0){
            vListFiles = fm->listFiles();
            for(string* i : *vListFiles)
                cout << *i << "\t";
            cout << "\n";

        }else if(strcmp(command, "upload") == 0){

            cin >> filename;

            //Si el fichero existe
            for(string* i : *vListFiles){
                if(strcmp(i->c_str(), filename) == 0){
                    cout << "Existe el fichero: " << *vListFiles->back() << "\n";    
                    //fm->writeFile(filename);
                }else if(strcmp(i->c_str(), *vListFiles->back()->c_str() ) == 0){

                }
            }

            cout << "No existe el fichero\n";

        }else if(strcmp(command, "download") == 0){
            cin >> filename;
            fm->readFile(filename);
        }else if(strcmp(command, "exit") != 0){
            cout << command << ": orden no encontrada\n";
        }

    }while(strcmp(command, "exit") != 0);

    delete command;
    delete filename;
    delete fm;

    return 0;
}