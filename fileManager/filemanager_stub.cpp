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
    cout << "1\n";
    char msg=OP_EXIT;
    sendMSG(serverID,(void*)&msg,sizeof(char));
    cout << "1\n";
    //recibir resultado
    char* buff=nullptr;
    int dataLen=0;
    char state=0;

    cout << "1\n";

    recvMSG(serverID, (void**)&buff, &dataLen);

    memcpy(&state,buff,sizeof(char));
cout << "1\n";

    delete buff;
cout << "1\n";

    if(state!=OP_OK)
        std::cout<<"ERROR cerrando conexion\n";

}

void filemanager_stub::listFiles(){

    char msg = 'L';
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int dataLen = 0;
    int* len=0;
    char* fileNames = nullptr;
 
    //Recibo el numero de ficheros que hay
    recvMSG(serverID,(void**)&len,&dataLen);

    //Recibo los nombres de los ficheros
    for (unsigned int i = 0; i < *len; i++){
        recvMSG(serverID,(void**)&fileNames, &dataLen);
        cout << fileNames << "\t";
    }
    cout << "\n";

    delete[] len;
    delete[] fileNames;
}

void filemanager_stub::readFile(char* fileName){ //DOWNLOAD

    char msg = READFILE;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int dataLen = 0;
    char* data = nullptr;
    
    ops = new FileManager(this->path);

    //Envio el nombre del fichero a descargar
    sendMSG(serverID, (void**)fileName, strlen(fileName)+1);

    //Recibo el fichero
    recvMSG(serverID, (void**)&data, &dataLen);
    
    ops->writeFile(fileName, data, dataLen);

    delete ops;
    delete[] data;

}

void filemanager_stub::writeFile(char* fileName){ //UPLOAD

    char msg = WRITEFILE;
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
    delete datosLeidos;

}