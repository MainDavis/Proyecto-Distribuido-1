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

                for(unsigned int i=0; i<listaServer->size(); i++){
                    sendMSG(clientID,listaServer->at(i)->c_str(), strlen(listaServer->at(i)->c_str())+1);
                }
                    
             }
                break;
            
            case READFILE:{

                char* fileName=nullptr;
				unsigned long fileSize=0;
				char* datosLeidos=nullptr;
				//recibir datos
				recvMSG(clientID,(void**)&fileName,&dataLen);
        
                ops->readFile(fileName, datosLeidos, fileSize);
                cout << "2\n";
                //devolver resultado
				sendMSG(clientID,(void*)datosLeidos,fileSize);
                cout << "3\n";
				//borrar memoria
				delete fileName;
				delete datosLeidos;

             }
                break;
            
            case WRITEFILE:{

                char* fileName=nullptr;
				unsigned long fileSize=0;
				char* datosEscritos=nullptr;

                //RECIBIR NOMBRE FICHERO 
				recvMSG(clientID, (void**)&fileName, &dataLen);
                cout << string(fileName) << "\n";
                //RECIBIR DATOS FICHERO 
				recvMSG(clientID, (void**)&datosEscritos, &dataLen);
                cout << string(datosEscritos) <<"\n";
                
                fileSize = dataLen;

                cout << string(fileName)<<"\n" ;
                cout << "1\n";
                ops->writeFile(fileName, datosEscritos, fileSize);
                cout << "1\n";
				//borrar memoria
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