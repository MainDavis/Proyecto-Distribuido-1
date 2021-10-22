#include "filemanager_imp.h"
#include "filemanager.h"

#define LISTFILES	    'L'
#define READFILE 	 	'R'
#define WRITEFILE 	    'M'
#define FREEFICH 	    'F'


#define OP_EXIT			'E'
#define OP_OK			'O'

filemanager_imp::filemanager_imp(int clientID){
	ops=new FileManager(this->path);
	//inicializar estados, extra... 
	salir=false;
	this->clientID=clientID;

}

filemanager_imp::~filemanager_imp(){
    cout << "1\n";
    if(listaServer != nullptr)
        ops->freeListedFiles(listaServer);
	delete ops;
	closeConnection(clientID);
	//cierre estados, etc...
}


void filemanager_imp::exec(){

      while (!salir){

        char* msg=NULL;
		int dataLen=0;
		char tipo_op=-1;

		recvMSG(clientID,(void**)&msg,&dataLen);

		if(dataLen!=1){	

			std::cout<<"Error, tipo operacion no valido\n";

		}else{
            
            tipo_op=msg[0];
			delete msg;
            
            switch (tipo_op){
                
            case LISTFILES:{
                
                listaServer = ops->listFiles();
                int len = listaServer->size();

                sendMSG(clientID,(void*)&len,sizeof(int));

                for(unsigned int i=0; i<listaServer->size(); i++)
                    sendMSG(clientID,listaServer->at(i)->c_str(), strlen(listaServer->at(i)->c_str())+1);

             }
                break;
            
            case READFILE:{ //DOWNLOAD

                char* fileName=nullptr;
				unsigned long fileSize=0;
				char* datosLeidos=nullptr;
				//recibir datos
				recvMSG(clientID,(void**)&fileName,&dataLen);

                ops->readFile(fileName, datosLeidos, fileSize);
                
                //devolver resultado
				sendMSG(clientID,(void*)datosLeidos,fileSize);
                
				//borrar memoria
				delete fileName;
				delete datosLeidos;

             }
                break;
            
            case WRITEFILE:{ //UPLOAD

                char* fileName=nullptr;
				unsigned long fileSize=0;
				char* datosEscritos=nullptr;

                //RECIBIR NOMBRE FICHERO 
				recvMSG(clientID, (void**)&fileName, &dataLen);

                //RECIBIR DATOS FICHERO 
				recvMSG(clientID, (void**)&datosEscritos, &dataLen);
                
                fileSize = dataLen;

                ops->writeFile(fileName, datosEscritos, fileSize);

				//borrar memoria
                ops->freeListedFiles(listaServer);
				delete fileName;
				delete datosEscritos;
         
             }
                break;

            case OP_EXIT: {
                    salir=true;
                    char opOK=OP_OK;
                    sendMSG(clientID,(void*)&opOK,sizeof(char));
                 }
  
                 break;
            default:
            	std::cout<<"Error, tipo operacion no valido\n";            
                break;
            }

        }
    }
}