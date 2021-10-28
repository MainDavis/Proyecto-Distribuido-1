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

vector<string*>* filemanager_stub::listFiles(){

    char msg = 'L';
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int dataLen = 0;
    int* len=0;
    char* fileName = nullptr;
    vector<string*>* vFileName = new vector<string*>;
 
    //Recibo el numero de ficheros que hay
    recvMSG(serverID,(void**)&len,&dataLen);

    //Recibo los nombres de los ficheros
    for (unsigned int i = 0; i < *len; i++){
        recvMSG(serverID,(void**)&fileName, &dataLen);
        vFileName->push_back(new string(fileName));
    }

    delete len;
    delete fileName;

    return vFileName;
}

void filemanager_stub::readFile(char* fileName){ //DOWNLOAD

    char msg = READFILE;
    sendMSG(serverID, (void*)&msg, sizeof(char));

    int dataLen = 0;
    char* data = nullptr;

    //Envio el nombre del fichero a descargar
    sendMSG(serverID, (void**)fileName, strlen(fileName)+1);

    //Recibo el fichero
    recvMSG(serverID, (void**)&data, &dataLen);
    
    string path=this->path+"/"+string(fileName);
    FILE* f=fopen(path.c_str(),"w");
    fwrite(data,dataLen,1,f);
    fclose(f);

}

void filemanager_stub::writeFile(char* fileName, vector<string*>* vListFiles){ //UPLOAD

    //Leo el fichero
    unsigned long fileSize = 0;
    char* datosLeidos = nullptr;
    string path=this->path+"/"+string(fileName);
    FILE* f=fopen(path.c_str(),"r");

    //Si el fichero existe continuo
    if(f != NULL){
        fseek(f, 0L, SEEK_END);
        fileSize= ftell(f);
        fseek(f, 0L, SEEK_SET);
        datosLeidos=new char[fileSize];
        fread(datosLeidos,fileSize,1,f);
        fclose(f);

        char msg = WRITEFILE;
        sendMSG(serverID, (void*)&msg, sizeof(char));

        //Envio el nombre del fichero
        sendMSG(serverID, (void**)fileName, strlen(fileName)+1);

        //Envio los datos del fichero
        sendMSG(serverID, (void**)datosLeidos, fileSize);
    
        //Añado el nombre del fichero al vector
        vListFiles->push_back(new string(fileName));
        
    }else{
        cout << "ERROR: No existe el fichero\n";
    }
    
    delete datosLeidos;
}