#include <iostream>
#include "filemanager_stub.h"

int main(int argc,char** argv)
{
    filemanager_stub *fm=new filemanager_stub();
    char* command = new char[25];
    char* filename = new char[25];

    /*
    LS -> listFiles
    READFILE -> Download
    WRITEFILE -> Upload
    */

    do{
        cin >> command;
        if(strcmp(command, "ls") == 0){
            fm->listFiles();
        }else if(strcmp(command, "upload") == 0){
            cin >> filename;
            fm->writeFile(filename);
        }else if(strcmp(command, "download") == 0){
            cin >> filename;
            fm->readFile(filename);
        }else{
            cout << command << ": orden no encontrada\n";
        }
    

    }while(strcmp(command, "exit") == 0);

    delete command;
    delete filename;

    return 0;
}