#include "multmatrix_imp.h"


#define ESTRUCTURA_MATRIX 		'E'
#define LEER_MATRIX	            'L'
#define ESCRIBIR_MATRIX 	 	'R'
#define MULT_MATRIX 	        'M'
#define CREATE_IDENTITY  	    'C'

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

    while (!salir)
    {
        char* msg=NULL;
		int dataLen=0;
		char tipo_op=-1;

		recvMSG(clientID,(void**)&msg,&dataLen);
		if(dataLen!=1)
		{	
			std::cout<<"Error, tipo operacion no valido\n";
		}else
		{
			tipo_op=msg[0];
			delete msg;

            switch (tipo_op)
            {

            case LEER_MATRIX:
                {
                    char* fichNombre_leer=nullptr;
                    int* fichSize=0;
                    char* datosLeidos=nullptr;

                    //RECIBIR LOS DATOS DE LA MATRIZ EN EL FICHERO
                    recvMSG(clientID,(void**)&fichNombre_leer,&dataLen);

                    //LEER LOS DATOS
                    datosLeidos=ops->readMatrix(fichNombre_leer);
                    //ENVIAR LOS DATOS DE VUELTA EN UNA MATRIX_T
                    sendMSG(clientID,(void*)&fichSize,sizeof(int));
                    sendMSG(clientID,(void*)&datosLeidos,fichSize);


                    //LIBERAR MEMORIA!!!!!!!!
<<<<<<< Updated upstream
=======
                    delete fichNombre_leer;
                    delete datosLeidos;
>>>>>>> Stashed changes

                }
                break;

            case ESCRIBIR_MATRIX:
                {
                    char* fichNombre_escribir=nullptr;
                    int* fichSize=0;
<<<<<<< Updated upstream
                    char* datosLeidos=nullptr;

                    //RECIBIR MATRIZ ALMACENADA EN MATRIX_T


                    //ESCRIBIR LA MATRIX DE MATRIX_T EN EL FICHERO
=======
                    matrix_t* m = new matrix_t;
                    char* datosEscritos = nullptr

                    //RECIBIR MATRIZ ALMACENADA EN MATRIX_T
                    recvMSG(clientID,(void**)&fichNombre_escribir,&dataLen);

					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(matrix_t->rows,msg,sizeof(int));            //ROWS
					delete msg;

					recvMSG(clientID,(void**)&msg,&dataLen);
					memcpy(&matrix_t->cols,msg,sizeof(int));            //COLS
					delete msg;

                    recvMSG(clientID,(void**)&m->data,&dataLen)         //DATOS


                    //ESCRIBIR LA MATRIX DE MATRIX_T EN EL FICHERO
                    ops->writeMatrix(,fichNombre_escribir);


>>>>>>> Stashed changes

                }
                break;

            case MULT_MATRIX:
                {


                }
                break;

            case CREATE_IDENTITY:
                {


                }
                break;
            
            case OP_EXIT:
                {
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

