#include "multmatrix_imp.h"

#define LEER_MATRIX	            'L'
#define ESCRIBIR_MATRIX 	 	'R'
#define MULT_MATRIX 	        'M'
#define CREATE_IDENTITY  	    'C'
#define CREATE_RANDOM           'A'

#define OP_EXIT			'E'
#define OP_OK			'O'

multmatrix_imp::multmatrix_imp(int clientID){

	ops=new multMatrix();
	//inicializar estados, extra... 
	salir=false;
	this->clientID=clientID;

}
multmatrix_imp::~multmatrix_imp(){

	delete ops;
	closeConnection(clientID);
	//cierre estados, etc...
}

void multmatrix_imp::exec(){

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

                case LEER_MATRIX: {

                    char* fichNombre_leer=nullptr;
                    char* buff = nullptr;
                    int dataLen=0;
                    matrix_t* datosLeidos=nullptr;
                    //RECIBIR LOS DATOS DE LA MATRIZ EN EL FICHERO
                    recvMSG(clientID,(void**)&fichNombre_leer,&dataLen);
                    //LEER LOS DATOS
                    datosLeidos=ops->readMatrix(fichNombre_leer);
                    
                    if(datosLeidos != NULL){
                        //Notifico al cliente que le fichero no existe
                        int msg = 1;
                        sendMSG(clientID,(void*)&msg,sizeof(int));
                        //ENVIAR LOS DATOS DE VUELTA EN UNA MATRIX_T
                        //Enviamos las columnas
                        sendMSG(clientID,(void*)&datosLeidos->cols,sizeof(int));
                        //Enviamos las filas
                        sendMSG(clientID,(void*)&datosLeidos->rows,sizeof(int));
                        //Enviamos los datos
                        sendMSG(clientID,(void*)datosLeidos->data, sizeof(int)*datosLeidos->cols*datosLeidos->rows);
                    }else{
                        //Notifico al cliente que le fichero no existe
                        int msg = 0;
                        sendMSG(clientID,(void*)&msg,sizeof(int));
                    }
                    
                    //LIBERAR MEMORIA!!!!!!!!
                    delete fichNombre_leer;
                    delete datosLeidos;

                }
                    break;

                case ESCRIBIR_MATRIX: {

                    char* fichNombre_escribir=nullptr;
                    int fichSize=0;
                    matrix_t* m = new matrix_t;

                    //RECIBIR MATRIZ ALMACENADA EN MATRIX_T
                    recvMSG(clientID,(void**)&fichNombre_escribir,&dataLen);

					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&m->rows,msg,sizeof(int));         //ROWS
					delete msg;

					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&m->cols,msg,sizeof(int));            //COLS
					delete msg;

                    recvMSG(clientID,(void**)&m->data,&dataLen);         //DATOS

                    //ESCRIBIR LA MATRIX DE MATRIX_T EN EL FICHERO
                    ops->writeMatrix(m ,fichNombre_escribir);

                    delete fichNombre_escribir;
                    delete m;

                    }
                    break;

                case MULT_MATRIX: {

                    matrix_t* m1 = new matrix_t;
                    matrix_t* m2 = new matrix_t;
                    matrix_t* result = new matrix_t;

                    //Matriz 1
					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&m1->rows,msg,sizeof(int));         //ROWS
					delete msg;

					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&m1->cols,msg,sizeof(int));            //COLS
					delete msg;

                    recvMSG(clientID,(void**)&m1->data,&dataLen);         //DATOS

                    //Matriz 2
                    recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&m2->rows,msg,sizeof(int));         //ROWS
					delete msg;

					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&m2->cols,msg,sizeof(int));            //COLS
					delete msg;

                    recvMSG(clientID,(void**)&m1->data,&dataLen);         //DATOS

                    result = ops->multMatrices(m1, m2);

                    }
                    break;

                case CREATE_IDENTITY: {


                    }
                    break;
                
                case CREATE_RANDOM: {
                    matrix_t* result = new matrix_t;
                    int dataLen = 0;
                    int *data = nullptr;

                    recvMSG(clientID, (void**)&data, &dataLen);

                    result = ops->createRandMatrix(data[0], data[1]);

                    sendMSG(clientID,(void*)result->data, sizeof(int)*data[0]*data[1]);
                    
                    delete data;
                    delete result;

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

