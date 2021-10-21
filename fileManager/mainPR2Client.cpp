#include <iostream>
#include "filemanager_stub.h"

int main(int argc,char** argv)
{
    filemanager_stub *fm=new filemanager_stub("./dirprueba/");
    char* command = nullptr, *filename = nullptr;

    /*
    LS -> listFiles
    READFILE -> Download
    WRITEFILE -> Upload
    */


    do{
        cin >> command;

        if(command == "ls"){
            fm->listFiles();
        }else if(command == "upload"){
            cin >> filename;
            fm->writeFile(filename);
        }else if(command == "download"){
            cin >> filename;
            fm->readFile(filename);
        }else{
            cout << command << ": orden no encontrada\n";
        }
    

    }while(command!="exit");

    delete command;
    delete filename;

    /* vector<string*>* vfiles=fm->listFiles(); //LS
    cout<<"Lista de ficheros en el directorio de prueba:\n";
    
    for(unsigned int i=0;i<vfiles->size();++i)
        cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;

    cout<<"Leyendo el primer fichero del directorio de prueba:\n";

    char* data=nullptr;
    unsigned long int fileLen=0;
    fm->readFile(&(*(vfiles->at(0)))[0],data,fileLen);
    cout<<"Escribiendo el primer fichero del directorio de prueba:\n";
    fm->writeFile(&(*(vfiles->at(0)))[0],data,fileLen); //Download
    cout<<"Liberando lista de ficheros:\n";
    fm->freeListedFiles(vfiles);
    cout<<"Liberando datos de fichero leído:\n";

    delete[] data; */
    return 0;
}