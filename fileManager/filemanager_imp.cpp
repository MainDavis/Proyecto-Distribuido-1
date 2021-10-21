#include "filemanager_imp.h"
#include "filemanager.h"

#define LISTFILES	    'L'
#define READFILE 	 	'R'
#define WRITEFILE 	    'M'
#define FREEFICH 	    'F'


#define OP_EXIT			'E'
#define OP_OK			'O'

filemanager_imp::filemanager_imp(int clientID){

	ops=new FileManager("");
	//inicializar estados, extra... 
	salir=false;
	this->clientID=clientID;

}
filemanager_imp::~filemanager_imp(){

	delete ops;
	closeConnection(clientID);
	//cierre estados, etc...
}


void filemanager_imp::exec(){

      while (!salir){

        char* msg=NULL;
		int dataLen=0;
		char tipo_op=-1;
        vector<string*> *listaServer = nullptr;

		recvMSG(clientID,(void**)&msg,&dataLen);

		if(dataLen!=1){	

			std::cout<<"Error, tipo operacion no valido\n";

		}else{
            
            tipo_op=msg[0];
			delete msg;
            
            switch (tipo_op){
                
            case LISTFILES:{

                listaServer = ops->listFiles();
                int tamanio = listaServer->size();

                sendMSG(clientID,(void*)&tamanio,sizeof(int));

                for(unsigned int i=0; i<listaServer->size(); i++){
                    sendMSG(clientID,listaServer->at(i)->c_str(), strlen(listaServer->at(i)->c_str())+1);
                }

             }
                break;
            
            case READFILE:{

                char* fileName=nullptr;
				int fileSize=0;
				char* datosLeidos=nullptr;
				//recibir datos
				recvMSG(clientID,(void**)&fileName,&dataLen);

                ops->readFile(fileName,(void**)datosLeidos,&fileSize);

                //devolver resultado
				sendMSG(clientID,(void*)&fileSize,sizeof(int));
				sendMSG(clientID,(void*)datosLeidos,fileSize);
				//borrar memoria
				delete fileName;
				delete datosLeidos;

             }
                break;
            
            case WRITEFILE:{

                char* fileName=nullptr;
				int fileSize=0;
				char* datosEscritos=nullptr;

                //RECIBIR FICHERO 
				recvMSG(clientID,(void**)&fileName,&dataLen);

                ops->writeFile(fileName,(void**)datosEscritos,&fileSize);

				//borrar memoria
				delete fileName;
				delete datosEscritos;
         
             }
                break;

            case FREEFICH :{


                ops->freeListedFiles(listaServer);

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