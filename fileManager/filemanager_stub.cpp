#include "filemanager_stub.h"

#define LISTFILES	    'L'
#define READFILE 	 	'R'
#define WRITEFILE 	    'M'

#define OP_EXIT			'E'
#define OP_OK			'O'

filemanager_stub::filemanager_stub(string path){

    FileManager* op = new FileManager(path);

    char* ip=NULL;
    ip=new char[strlen(IP_SERVER)+1];
    memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);

    std::cout<<"INICIANDO CLIENTE\n";

    serverID=initClient(ip,PORT_SERVER);

    if(serverID==-1)
        std::cout<<"ERROR CLIENTE Fichero: "<< __FILE__ <<" Línea: "<< __LINE__ <<" Conexión no válida\n";

    delete ip;

}

filemanager_stub::~filemanager_stub(){

    char msg=OP_EXIT;
    sendMSG(serverID,(void*)&msg,sizeof(char));
    //recibir resultado
    char* buff=nullptr;
    int dataLen=0;
    char state=0;
    recvMSG(serverID, (void**)&buff, &dataLen);
    memcpy(&state,buff,sizeof(char));
    delete buff;

    if(state!=OP_OK)
        std::cout<<"ERROR cerrando conexion\n";

}

vector<string*>* filemanager_stub::listFiles(){
    int tamanio=0;
    int DataLen=0;
    vector<string*>* listaServer = nullptr;

    recvMSG(serverID,(void**)&tamanio,&DataLen);

    for (unsigned int i = 0; i < tamanio; i++)
        recvMSG(serverID,(void**)listaServer->at(i)->c_str(), &DataLen);    

    return NULL;
}

void filemanager_stub::readFile(char* fileName){



}

void filemanager_stub::writeFile(char* fileName){

    int 

}

void filemanager_stub::freeListedFiles(vector<string*>* fileList){

    
}