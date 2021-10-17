#include "multmatrix_stub.h"

#define LEER_MATRIX	            'L'
#define ESCRIBIR_MATRIX 	 	'R'
#define MULT_MATRIX 	        'M'
#define CREATE_IDENTITY  	    'C'
#define CREATE_RANDOM  	        'A'

#define OP_EXIT			'E'
#define OP_OK			'O'

multmatrix_stub::multmatrix_stub(){

    char* ip=NULL;
    ip=new char[strlen(IP_SERVER)+1];
    memcpy(ip,IP_SERVER,strlen(IP_SERVER)+1);

    std::cout<<"INICIANDO CLIENTE\n";

    serverID=initClient(ip,PORT_SERVER);

    if(serverID==-1)
        std::cout<<"ERROR CLIENTE Fichero: "<< __FILE__ <<" Línea: "<< __LINE__ <<" Conexión no válida\n";

    delete ip;

}
/////
/////
multmatrix_stub::~multmatrix_stub(){

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
/////
/////
matrix_t* multmatrix_stub::readMatrix(const char* file){
    
    matrix_t* result = new matrix_t;
    char msg = LEER_MATRIX;
    int dataLen = 0;
    int *exito = nullptr, *buff = nullptr;
    
    //Enviamos la operación al server 
    sendMSG(serverID, (void*)&msg, sizeof(char));
    //Enviamos el nombre del fichero
    sendMSG(serverID, (void**)file, strlen(file)+1);

    //Recibimos si ha tenido exito
    recvMSG(serverID, (void**)&exito, &dataLen);
    if(*exito == 1){

        //Recibimos las columnas
        recvMSG(serverID, (void**)&buff, &dataLen);
        memcpy(&result->cols, buff, sizeof(int));

        //Recibimos las filas
        recvMSG(serverID, (void**)&buff, &dataLen);
        memcpy(&result->rows, buff, sizeof(int));

        //Recibimos los datos
        recvMSG(serverID, (void**)&buff, &dataLen);
        result->data = buff;
        
        return result;
    }else{
        std::cout<< "ERROR: Fichero " << std::string(file) <<" no existe\n";
        return NULL;
    }
    
}
/////
/////
matrix_t* multmatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){
    
    matrix_t* result = new matrix_t;
    char msg = MULT_MATRIX;
    int dataLen = 0;
    int *buff = nullptr;

    //Enviamos la operación al server
    sendMSG(serverID, (void*)&msg, sizeof(char));

    //Enviamos los datos de la primera matriz
    //Enviamos las columnas
    sendMSG(serverID,(void*)&m1->cols,sizeof(int));
    //Enviamos las filas
    sendMSG(serverID,(void*)&m1->rows,sizeof(int));
    //Enviamos los datos
    sendMSG(serverID,(void*)m1->data, sizeof(int)*m1->cols*m1->rows);

    //Enviamos los datos de la primera matriz
    //Enviamos las columnas
    sendMSG(serverID,(void*)&m2->cols,sizeof(int));
    //Enviamos las filas
    sendMSG(serverID,(void*)&m2->rows,sizeof(int));
    //Enviamos los datos
    sendMSG(serverID,(void*)m2->data, sizeof(int)*m2->cols*m2->rows);

    //Miramos si se ha podido hacer la operacion
    recvMSG(serverID, (void**)&buff, &dataLen);

    if(*buff == 1){
        //Recibimos los datos de la matriz resultado
        recvMSG(serverID, (void**)&buff, &dataLen);
        memcpy(&result->cols, buff, sizeof(int));
        //Recibimos las filas
        recvMSG(serverID, (void**)&buff, &dataLen);
        memcpy(&result->rows, buff, sizeof(int));
        //Recibimos los datos
        recvMSG(serverID, (void**)&buff, &dataLen);
        result->data = buff;

        //delete buff;
        return result;

    }else{
        //delete buff;
        return NULL;
    }
        
}
/////
/////
void multmatrix_stub::writeMatrix(matrix_t* m, const char *fileName){
    char msg = ESCRIBIR_MATRIX;
    int dataLen = 0;
    int* buff = nullptr;

    //Enviamos la operación al server 
    sendMSG(serverID, (void*)&msg, sizeof(char));

    //Enviamos el nombre del fichero
    sendMSG(serverID, (void**)fileName, strlen(fileName)+1);
    //Enviamos las columnas
    sendMSG(serverID,(void*)&m->cols,sizeof(int));
    //Enviamos las filas
    sendMSG(serverID,(void*)&m->rows,sizeof(int));
    //Enviamos los datos
    sendMSG(serverID,(void*)m->data, sizeof(int)*m->cols*m->rows);

}
/////
/////
matrix_t* multmatrix_stub::createIdentity(int rows, int cols){
    matrix_t* result = new matrix_t;
    char msg = CREATE_IDENTITY;
    int dataLen = 0;
    int* data = nullptr;

    //Enviamos la operación al server 
    sendMSG(serverID, (void*)&msg, sizeof(char));

    //Enviamos las filas y columnas
    data = new int[2];
    data[0] = rows;
    data[1] = cols;

    sendMSG(serverID, (void*)data, sizeof(int)*2);

    //Ensamblamos la matriz
    result->cols = cols;
    result->rows = rows;

    data = new int[rows*cols];

    recvMSG(serverID, (void**)&data, &dataLen);

    result->data = data;

    //delete data;

    return result;
}
/////
/////
matrix_t* multmatrix_stub::createRandMatrix(int rows, int cols){

    matrix_t* result = new matrix_t;
    char msg = CREATE_RANDOM;
    int dataLen = 0;
    int* data = nullptr;

    //Enviamos la operación al server 
    sendMSG(serverID, (void*)&msg, sizeof(char));

    //Enviamos las filas y columnas
    data = new int[2];
    data[0] = rows;
    data[1] = cols;

    sendMSG(serverID, (void*)data, sizeof(int)*2);

    //Ensamblamos la matriz
    result->cols = cols;
    result->rows = rows;

    data = new int[rows*cols];

    recvMSG(serverID, (void**)&data, &dataLen);

    result->data = data;

    //delete data;

    return result;
}