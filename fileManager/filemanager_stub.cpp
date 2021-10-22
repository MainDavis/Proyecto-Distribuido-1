#include "filemanager_stub.h"

#define LISTFILES	    'L'
#define READFILE 	 	'R'
#define WRITEFILE 	    'M'

#define OP_EXIT			'E'
#define OP_OK			'O'

filemanager_stub::filemanager_stub(){

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

std::vector<std::string*>* filemanager_stub::listFiles(){

    char msg = 'L';
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int dataLen = 0;
    int* len=0;
    string* fileName = nullptr;
    vector<string*>* vFileName = nullptr;
 
    //Recibo el numero de ficheros que hay
    recvMSG(serverID,(void**)&len,&dataLen);

    //Recibo los nombres de los ficheros
    for (unsigned int i = 0; i < *len; i++){
        recvMSG(serverID,(void**)&fileName, &dataLen);
        cout << fileName << "\t";
        vFileName->push_back(fileName);
    }
    cout << "\n";

    return vFileName;
}

void filemanager_stub::readFile(char* fileName){ //DOWNLOAD

    /* char msg = READFILE;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int dataLen = 0;
    char* data = nullptr;
    
    ops = new FileManager(this->path);

    //Envio el nombre del fichero a descargar
    sendMSG(serverID, (void**)fileName, strlen(fileName)+1);

    //Recibo el fichero
    recvMSG(serverID, (void**)&data, &dataLen);
    
    ops->writeFile(fileName, data, dataLen); */

}

void filemanager_stub::writeFile(char* fileName){ //UPLOAD

    /* char msg = WRITEFILE;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    unsigned long fileSize = 0;
    char* datosLeidos = nullptr;

    //Envio el nombre del fichero
    sendMSG(serverID, (void**)fileName, strlen(fileName)+1);

    ops = new FileManager(this->path);

    //Leo los datos del archivo
    ops->readFile(fileName, datosLeidos, fileSize);
    
    //Envio los datos del fichero
    sendMSG(serverID, (void**)datosLeidos, fileSize);

    delete ops;
    delete datosLeidos; */

}