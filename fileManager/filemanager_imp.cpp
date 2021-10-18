#include "filemanager_imp.h"

#define LISTFILES	    'L'
#define READFILE 	 	'R'
#define WRITEFILE 	    'M'

#define OP_EXIT			'E'
#define OP_OK			'O'

multmatrix_imp::multmatrix_imp(int clientID){

	ops=new FileManager();
	//inicializar estados, extra... 
	salir=false;
	this->clientID=clientID;

}
multmatrix_imp::~multmatrix_imp(){

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


                /* code */


             }
                break;
            
            case READFILE:{


                
                /* code */
             }
                break;
            
            case WRITEFILE:{


                
                /* code */
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