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
            fm->writeFile(filename,vListFiles);

        }else if(strcmp(command, "download") == 0){
            
            cin >> filename;

            //Miro si existe el fichero
            bool existe = false;

            for(int i=0; i<vListFiles->size() && !existe; i++)
                if( strcmp(vListFiles->at(i)->c_str(), filename) == 0)
                    existe = true;
                
            if(existe){
                fm->readFile(filename);
            }else{
                cout << "ERROR: No existe el fichero\n";
            }

        }else if(strcmp(command, "exit") != 0){
            cout << command << ": orden no encontrada\n";
        }

    }while(strcmp(command, "exit") != 0);

    //ops->freeListedFiles(vListFiles);
    for(vector<string*>::iterator i=vListFiles->begin();i!= vListFiles->end();++i)
    {
        delete *i;
    }
    delete vListFiles;

    delete command;
    delete filename;
    delete fm;

    return 0;
}